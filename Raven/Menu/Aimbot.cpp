#include "../Include/ESP.h"
#include "../ImGui/imgui.h"
#include "../Include/Variables.h"
#include "../Include/Offsets.h"
#include "../Include/Math.h"
#include "../Include/Aimbot.h"
#include "../Include/Console.h"
#include "../Include/Vectors.h"
#include <thread>
namespace Raven
{
	Vector3 vector2ToVector3(const vector2& v2)
	{
		return Vector3(v2.X, v2.Y, 0.0f);
	}

	AimbotInstance::AimbotInstance()
	{
		return;
	}



	const Vector3 CalculateAngle(
		const Vector3& localPosition,
		const Vector3& enemyPosition,
		const Vector3& viewAngles) noexcept
	{
		return ((enemyPosition - localPosition).ToAngle() - viewAngles);
	};

	bool isaimboton = false;
	void AimbotInstance::Aimbot()
	{

		Offsets::gentity_t* self = GetGentity(0);
		auto bestFov = 5.f;
		auto bestAngle = Vector3{ };
		Vector3 viewangles = vector2ToVector3(self->PlayerInfo->Angle);
		if (g_aimbot)
		{
				if (self->Health != 0)
				{
					if (GetKeyState(VK_RBUTTON) & 0x8000)
					{
						std::this_thread::sleep_for(std::chrono::milliseconds(1));
						//g_Console->printdbg("RMOUSE Pressed\n", g_Console->color.blue);


						//g_Console->printdbg("RMOUSE Pressed\n", g_Console->color.blue);

						for (int i = 1; i < 24; i++)
						{
							Offsets::gentity_t* ent = GetGentity(i);
							int ownteam = self->TeamInfo->Team;
							int entteam = ent->TeamInfo->Team;

							if (ent->Health > 0 && Math::VecDistance(self->Position, ent->Position) > 0)
							{
								if (ownteam != entteam)
								{
									const auto angle = CalculateAngle(
										self->Position,
										ent->Position,
										viewangles

									);
									g_Console->printdbg("Angle Calculated! \n", g_Console->color.green);
									const auto fov = std::hypot(angle.x, angle.y);
									if (fov < bestFov)
									{
										bestFov = fov;
										viewangles = angle;
									}
									g_Console->printdbg("View Angles Calculated! \n", g_Console->color.green);
									if (!bestAngle.IsZero())
									{
										g_Console->printdbg("Best Angle FOUND!\n", g_Console->color.green);
										viewangles = (viewangles + bestAngle / 3.f);
										//myangles = self->Angles + bestAngle / 3.0f
									}
								}
							}
						}
					}
					
				}

			}
			/*
					if (g_aimbot)
					{
						bool windowopen = true;
						ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
						ImGui::Begin("Aimbot", &windowopen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);
						ImGui::SetWindowPos(ImVec2(0, 0));
						ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));


						//std::this_thread::sleep_for(std::chrono::milliseconds(50));

						Offsets::gentity_t* self = GetGentity(0);
						float* viewMatrix = reinterpret_cast<float*>(VIEW_MATRIX);
						for (int i = 1; i < 24; i++)
						{
							Offsets::gentity_t* ent = GetGentity(i);

							if (ent->Health > 0 && Math::VecDistance(self->Position, ent->Position) > 0 && ent->ClientNum < 100)
							{
								Vector3 entpos(ent->Position[0], ent->Position[1], ent->Position[2]);
								Vector3 screen;



								float* zoom = reinterpret_cast<float*>(OFFSET_ZOOM);
								float distance = Math::VecDistance(self->Position, ent->Position);
								int distanceint = static_cast<int>(distance);


								bool ADS = ((GetKeyState(VK_RBUTTON) & 0x100) != 0);
								float lowestDist = FLT_MAX;
								uint16_t lowestID = UINT16_MAX;

								if (distance < lowestDist) { // Check if it's the closest zombie
									lowestDist = distance;
									lowestID = i;
								}
								Offsets::gentity_t* local = GetGentity(0);
									if (ADS && lowestID != UINT16_MAX) { // If you're ADSed and closest isn't self
										Offsets::gentity_t* closest = GetGentity(i);
										Vector3 screen, pos(closest->Position[0], closest->Position[1], closest->Position[2]);

										float distance = Math::VecDistance(local->Position, closest->Position);
										bool onscreen = Math::WorldToScreen(pos, screen, viewMatrix);

										if (g_aimbot || onscreen) // if its unreal or if the ent is actually onscreen
											if (!SetCursorPos(screen.x, screen.y - (60 / (distance * (0.0025f))))) // 0.0018f / zoom% or 0.0018f * zoom%

											g_Console->printdbg("Failed to SetCursorPos()", g_Console->color.blue);
									}



							}
						}
					}*/
		}
	}
