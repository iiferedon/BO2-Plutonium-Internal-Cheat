#include "Math.h"
#include "../Include/Vectors.h"
#include <initializer_list>
#include "../Include/Offsets.h"
#include "../ImGui/imgui.h"
#include <cmath>
#include <chrono>
#include "../Include/Math.h"

namespace Math
{

	


	float VecDistance(vec3 Self, vec3 Ent) 
	{
		return (float)sqrt((Self[0] - Ent[0]) * (Self[0] - Ent[0]) + (Self[1] - Ent[1]) * (Self[1] - Ent[1]) + (Self[2] - Ent[2]) * (Self[2] - Ent[2]));
	}


	bool WorldToScreen(Vector3 pos, Vector3& screen, float matrix[16]) 
	{
		
	
		vec4 clipCoords;
		clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
		clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
		clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
		clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

		if (clipCoords.w < 0.1f)
			return false;

		Vector3 NDC;
		NDC.x = clipCoords.x / clipCoords.w;
		NDC.y = clipCoords.y / clipCoords.w;
		NDC.z = clipCoords.z / clipCoords.w;


		float width = ImGui::GetIO().DisplaySize.x;
		float height = ImGui::GetIO().DisplaySize.y;
		
		screen.x = (width / 2 * NDC.x) + (NDC.x + width / 2);
		screen.y = -(height / 2 * NDC.y) + (NDC.y + height / 2);

		return true;
	}


	


	ImVec4 calculateHealthColor(int entityHealth)
	{
		// Calculate the color based on the entity's health
		float healthPercent = static_cast<float>(entityHealth) / 150.f;
		float greenPercent = std::max(0.f, std::min(1.f, (1.f - healthPercent) * 2.f));
		float redPercent = std::max(0.f, std::min(1.f, (healthPercent - 0.5f) * 2.f));
		float bluePercent = std::max(0.f, std::min(1.f, (healthPercent - 0.5f) * 2.f));

		// Lerp between green and orange
		float lerpFactor = std::max(0.f, std::min(1.f, (healthPercent - 0.5f) * 2.f));
		float green = lerp(255.f, 255.f * 0.5f, lerpFactor);
		float red = lerp(255.f, 255.f * 1.0f, lerpFactor);
		float blue = 0.f;

		// Lerp between orange and red
		if (healthPercent <= 0.5f)
		{
			lerpFactor = std::max(0.f, std::min(1.f, healthPercent * 2.f));
			green = lerp(255.f * 0.5f, 255.f * 1.0f, lerpFactor);
			red = lerp(255.f * 1.0f, 255.f * 1.0f, lerpFactor);
			blue = lerp(0.f, 0.f, lerpFactor);
		}

		// Create an ImVec4 color variable and return it
		return ImVec4(green / 255.f, red / 255.f, blue / 255.f, 1.f);
	}
}


