#include <xmmintrin.h>
#include <valarray>
#include "source_sdk/mathlib/mathlib.hpp"

float Vector::Length2D()
{
	return x * x + y * y;
}

float Vector::LengthSqr()
{
	return x * x + y * y + z * z;
}

float Vector::Length()
{
	return std::sqrt(LengthSqr());
}

Vector VectorTransform(Vector vec, matrix3x4_t m) {
	return {
		vec.Dot(m[0]) + m[0][3],
		vec.Dot(m[1]) + m[1][3],
		vec.Dot(m[2]) + m[2][3]
	};
}

QAngle VectorAngles(Vector vec)
{
	return {
		RAD2DEG(atan2f(-vec.z, hypotf(vec.x, vec.y))),
		RAD2DEG(atan2f(vec.y, vec.x)),
		0.0f
	};
}

void AngleMatrix(QAngle angles, matrix3x4a_t &matrix)
{
	float sr, sp, sy, cr, cp, cy;

	sp = sin(DEG2RAD(angles.x));
	sy = sin(DEG2RAD(angles.y));
	sr = sin(DEG2RAD(angles.z));
	cp = cos(DEG2RAD(angles.x));
	cy = cos(DEG2RAD(angles.y));
	cr = cos(DEG2RAD(angles.z));

	matrix[0][0] = cp * cy;
	matrix[1][0] = cp * sy;
	matrix[2][0] = -sp;

	float crcy = cr * cy;
	float crsy = cr * sy;
	float srcy = sr * cy;
	float srsy = sr * sy;

	matrix[0][1] = sp * srcy - crsy;
	matrix[1][1] = sp * srsy + crcy;
	matrix[2][1] = sr * cp;

	matrix[0][2] = (sp * crcy + srsy);
	matrix[1][2] = (sp * crsy - srcy);
	matrix[2][2] = cr * cp;

	matrix[0][3] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][3] = 0.0f;
}

void AngleMatrix(QAngle angles, Vector position, matrix3x4a_t &matrix)
{
	AngleMatrix(angles, matrix);

	matrix[0][3] = position.x;
	matrix[1][3] = position.y;
	matrix[2][3] = position.z;
}

void QuaternionMatrix(Quaternion q, Vector pos, matrix3x4a_t &matrix)
{
	QuaternionMatrix(q, matrix);

	matrix[0][3] = pos.x;
	matrix[1][3] = pos.y;
	matrix[2][3] = pos.z;
}


void QuaternionMatrix(Quaternion q, matrix3x4a_t &matrix)
{
	// Original code
	// This should produce the same code as below with optimization, but looking at the assmebly,
	// it doesn't.  There are 7 extra multiplies in the release build of this, go figure.
#if 1
	matrix[0][0] = 1.0 - 2.0 * q.y * q.y - 2.0 * q.z * q.z;
	matrix[1][0] = 2.0 * q.x * q.y + 2.0 * q.w * q.z;
	matrix[2][0] = 2.0 * q.x * q.z - 2.0 * q.w * q.y;

	matrix[0][1] = 2.0f * q.x * q.y - 2.0f * q.w * q.z;
	matrix[1][1] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z;
	matrix[2][1] = 2.0f * q.y * q.z + 2.0f * q.w * q.x;

	matrix[0][2] = 2.0f * q.x * q.z + 2.0f * q.w * q.y;
	matrix[1][2] = 2.0f * q.y * q.z - 2.0f * q.w * q.x;
	matrix[2][2] = 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y;

	matrix[0][3] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][3] = 0.0f;
#else
	float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;

	// precalculate common multiplitcations
	x2 = q.x + q.x;
	y2 = q.y + q.y;
	z2 = q.z + q.z;
	xx = q.x * x2;
	xy = q.x * y2;
	xz = q.x * z2;
	yy = q.y * y2;
	yz = q.y * z2;
	zz = q.z * z2;
	wx = q.w * x2;
	wy = q.w * y2;
	wz = q.w * z2;

	matrix[0][0] = 1.0 - (yy + zz);
	matrix[0][1] = xy - wz;
	matrix[0][2] = xz + wy;
	matrix[0][3] = 0.0f;

	matrix[1][0] = xy + wz;
	matrix[1][1] = 1.0 - (xx + zz);
	matrix[1][2] = yz - wx;
	matrix[1][3] = 0.0f;

	matrix[2][0] = xz - wy;
	matrix[2][1] = yz + wx;
	matrix[2][2] = 1.0 - (xx + yy);
	matrix[2][3] = 0.0f;
#endif
}


void ConcatTransforms(matrix3x4a_t &m0, matrix3x4a_t &m1, matrix3x4a_t &out)
{
	for(int i = 0; i < 3; i++)
	{
		// Normally, you can't just multiply 2 3x4 matrices together, so translation is done separately
		out[i][3] = m1[0][3] * m0[i][0] + m1[1][3] * m0[i][1] + m1[2][3] * m0[i][2] + m0[i][3]; // translation

		for(int j = 0; j < 3; j++) // rotation/scale
			out[i][j] = m0[i][0] * m1[0][j] + m0[i][1] * m1[1][j] + m0[i][2] * m1[2][j];
	}
}

float InvSqrt(float x)
{
	__m128 rroot = _mm_rsqrt_ss(_mm_load_ss(&x));
	auto flRoot = *(reinterpret_cast<float *>(&rroot));

	// Single iteration NewtonRaphson reciprocal square root:
	// 0.5 * rsqrtps * (3 - x * rsqrtps(x) * rsqrtps(x))
	// Very low error, and fine to use in place of 1.f / sqrtf(x).
	return (0.5f * flRoot) * (3.f - (x * flRoot) * flRoot);
}