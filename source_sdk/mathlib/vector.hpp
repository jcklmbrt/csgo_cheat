
#ifndef CSGO_CHEAT_VECTOR_HPP
#define CSGO_CHEAT_VECTOR_HPP

//#define ALIGN(bits) __declspec(align(bits))
#define ALIGN(bits) __attribute__((aligned(bits)));//<--- freetard version

struct Vector
{
	Vector() = default;

	constexpr Vector(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z)
	{}

	//operators
	Vector operator+(Vector other)
	{
		return {x + other.x, y + other.y, z + other.z};
	}

	Vector operator-(Vector other)
	{
		return {x - other.x, y - other.y, z - other.z};
	}

	Vector operator/(float other)
	{
		return {x / other, y / other, z / other};
	}

	Vector operator*(float other)
	{
		return {x * other, y * other, z * other};
	}

	Vector operator+=(Vector other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}

	Vector operator-=(Vector other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}

	Vector operator+=(float other)
	{
		x += other;
		y += other;
		z += other;
		return *this;
	}

	Vector operator-=(float other)
	{
		x -= other;
		y -= other;
		z -= other;
		return *this;
	}

	Vector operator/=(float other)
	{
		x /= other;
		y /= other;
		z /= other;
		return *this;
	}

	Vector operator*=(float other)
	{
		x *= other;
		y *= other;
		z *= other;
		return *this;
	}

	float &operator[](int i)
	{
		return reinterpret_cast<float *>(this)[i];
	}

	//dot product
	float Dot(Vector other)
	{
		return x * other.x + y * other.y + z * other.z;
	}

	float Dot(float *other)
	{
		return x * other[0] + y * other[1] + z * other[2];
	}

	float  Length();
	float  Length2D();
	float  LengthSqr();
	Vector Normalized();
	//Vector Transform(matrix3x4_t m);

	float x, y, z;
};

struct VectorAligned : Vector
{
	VectorAligned() = default;

	VectorAligned(Vector vec)
		: Vector(vec), w(0.0f)
	{}

	VectorAligned(float _x, float _y, float _z, float _w)
		: Vector(_x, _y, _z), w(_w)
	{};

	VectorAligned &operator=(Vector vec)
	{
		*this = VectorAligned(vec);
		return *this;
	}

	float w;

} ALIGN(16);

typedef VectorAligned Quaternion;
typedef Vector QAngle, RadianEuler;

QAngle VectorAngles(Vector vec);
QAngle VectorAngles(Vector &forward, Vector &pseudoup);
Vector AngleVectors(QAngle angle);
void AngleVectors(QAngle angle, Vector &forward, Vector &right, Vector &up);

#endif//CSGO_CHEAT_VECTOR_HPP
