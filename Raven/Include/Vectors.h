
#ifndef VECTORS_H
#define VECTORS_H

#include <cmath>
typedef float vec2[2];
typedef float vec3[3];
const float pi = 3.14159265358979323846;
class vec4 {
public:
	float x;
	float y;
	float z;
	float w;
};


struct vector2
{
	float X;
	float Y;
};

class Vector3 {
public:
	float x, y, z;

	constexpr Vector3(
		const float x = 0.f,
		const float y = 0.f,
		const float z = 0.f) noexcept :
		x(x), y(y), z(z) {}

	Vector3(const vec3& v) : x(v[0]), y(v[1]), z(v[2]) {}
	Vector3(const vec2& v) : x(v[0]), y(v[1]), z(0.0f) {}
	Vector3(const vector2& v2) : x(v2.X), y(v2.Y), z(0.0f) {}
	constexpr const Vector3& operator-(const Vector3& other) const noexcept
	{
		return Vector3{ x - other.x,y - other.y,z - other.z };
	}
	constexpr const Vector3& operator+(const Vector3& other) const noexcept
	{
		return Vector3{ x + other.x,y + other.y,z + other.z };
	}
	constexpr const Vector3& operator/(const float factor) const noexcept
	{
		return Vector3{ x / factor,y / factor,z / factor };
	}
	constexpr const Vector3& operator*(const float factor) const noexcept
	{
		return Vector3{ x * factor,y * factor,z * factor };
	}
	

	
	inline float Dot(const Vector3& vector) {
		return x * vector.x + y * vector.y + z * vector.z;
	}

	inline float Distance(const Vector3& vector) {
		return sqrt(
			(x - vector.x) * (x - vector.x) +
			(y - vector.y) * (y - vector.y) +
			(z - vector.z) * (z - vector.z));
	}

	const Vector3& ToAngle() const noexcept
	{
		return Vector3{
			std::atan2(-z, std::hypot(x,y)) * (180.0f / pi),
			std::atan2(y,x) * (180.0f / pi),
			0.0f };
	};

	const bool IsZero() const noexcept
	{
		return x == 0.f && y == 0.f && z == 0.f;
	};

	static Vector3 CalculateAngle(
		const Vector3& localPosition,
		const Vector3& enemyPosition,
		const Vector3& viewAngles) noexcept
	{
		return ((enemyPosition - localPosition).ToAngle() - viewAngles);
	}
	
};


/*class Vector3 {
public:
	float x;
	float y;
	float z;

	Vector3();
	Vector3(float x, float y, float z);

	Vector3 operator+(const Vector3& vector) const;
	Vector3 operator-(const Vector3& vector) const;
	Vector3 operator-() const;
	Vector3 operator*(float number) const;
	Vector3 operator/(float number) const;

	Vector3& operator+=(const Vector3& vector);
	Vector3& operator-=(const Vector3& vector);
	Vector3& operator*=(float number);
	Vector3& operator/=(float number);

	bool operator==(const Vector3& vector) const;
	bool operator!=(const Vector3& vector) const;

	inline float Dot(const Vector3& vector) {
		return x * vector.x + y * vector.y + z * vector.z;
	}

	inline float Distance(const Vector3& vector) {
		return sqrt(
			(x - vector.x) * (x - vector.x) +
			(y - vector.y) * (y - vector.y) +
			(z - vector.z) * (z - vector.z));
	}

	const Vector3& ToAngle() const noexcept
	{
		return Vector3{
			std::atan2(-z, std::hypot(x,y)) * (180.0f / pi),
			std::atan2(y,x) * (180.0f / pi),
			0.0f };
	};

	const bool IsZero() const noexcept
	{
		return x == 0.f && y == 0.f && z == 0.f;
	};

	static Vector3 CalculateAngle(
		const Vector3& localPosition,
		const Vector3& enemyPosition,
		const Vector3& viewAngles) noexcept
	{
		return ((enemyPosition - localPosition).ToAngle() - viewAngles);
	}
	
};*/





#endif // VECTORS_H