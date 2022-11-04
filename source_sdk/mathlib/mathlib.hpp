
#ifndef CSGO_CHEAT_MATHLIB_HPP
#define CSGO_CHEAT_MATHLIB_HPP

#include <numbers>
#include "source_sdk/mathlib/vector.hpp"

constexpr float Q_PI = std::numbers::pi_v<float>;

constexpr float RAD2DEG(float rad)
{
	return rad * (180.0f / Q_PI);
}

constexpr float DEG2RAD(float deg)
{
	return deg * (Q_PI / 180.0f);
}

struct cplane_t
{
	Vector normal;
	float dist;
	char type;                        // for fast side tests
	char signbits;                // signx + (signy<<1) + (signz<<1)
	char pad[2];
};

struct matrix3x4_t
{
	float *operator[](int i)
	{
		return m[i];
	}

	Vector GetOrigin()
	{
		return {m[0][3], m[1][3], m[2][3]};
	};

	float m[3][4];
};

/*
struct matrix3x4a_t : matrix3x4_t
{

} ALIGN(16);
*/

typedef matrix3x4_t matrix3x4a_t ALIGN(16);

void AngleMatrix(QAngle angles, matrix3x4_t &matrix);
void AngleMatrix(QAngle angles, Vector position, matrix3x4_t &matrix);
void QuaternionMatrix(Quaternion q, matrix3x4_t &matrix);
void QuaternionMatrix(Quaternion q, Vector pos, matrix3x4_t &matrix);
Quaternion AngleQuaternion(RadianEuler angles);
RadianEuler QuaternionAngles(Quaternion q);
Vector VectorITransform(Vector in1, matrix3x4_t in2);
Vector VectorIRotate(Vector in1, matrix3x4_t in2);
Vector VectorTransform(Vector in1, matrix3x4_t in2);
void ConcatTransforms(matrix3x4_t &m0, matrix3x4_t &m1, matrix3x4_t &out);
float InvSqrt(float x);

#endif //CSGO_CHEAT_MATHLIB_HPP
