#include "Vectors.h"


namespace Math
{
	float VecDistance(vec3 Self, vec3 Zombie);
	bool WorldToScreen(Vector3 pos, Vector3& screen, float matrix[16]);
	ImVec4 calculateHealthColor(int entityHealth);
	template <typename T>
	T lerp(T a, T b, float t)
	{
		return a * (1.f - t) + b * t;
	}

	
}