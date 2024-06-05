#include "../Include/ESP.h"
#include "../ImGui/imgui.h"
#include "../Include/Variables.h"
#include "../Include/Offsets.h"
#include "../Include/Math.h"
#include "../ImGui/imgui_impl_dx11.h"
#include "../Include/Console.h"
#include <io.h>
#include "../Fonts.h"
namespace Raven
{

	_fastcall Renderer::Renderer()
	{
		return;
	}



	void Renderer::Esp()
	{
		if (g_espwindow)
		{
			//Bank_Gothic_Pro_Light = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(bank_gothic_pro_light_otf_compressed_data_base85, flBank_Gothic_Pro_Light = 14.0f);
			bool windowopen = true;
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
			ImGui::Begin("Renderer", &windowopen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoBringToFrontOnFocus);
			ImGui::SetWindowPos(ImVec2(0, 0));
			ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y));

			Offsets::gentity_t* self = GetGentity(0);
			float* viewMatrix = reinterpret_cast<float*>(VIEW_MATRIX);
			for (int i = 1; i < 24; i++)
			{
				Offsets::gentity_t* ent = GetGentity(i);

				if (ent->Health > 0 && Math::VecDistance(self->Position, ent->Position) > 0)
				{
					Vector3 entpos(ent->Position[0], ent->Position[1], ent->Position[2]);
					Vector3 screen;



					//float* zoom =  reinterpret_cast<float*>(OFFSET_ZOOM);
					float distance = Math::VecDistance(self->Position, ent->Position);
					int distanceint = static_cast<int>(distance);

					float maxHealth = 100.0f;   // Maximum health value

					//float healthBarHeight = g_GameVariables->boxheight * (ent->Health / maxHealth);
					int ownteam = self->TeamInfo->Team;
					int entteam = ent->TeamInfo->Team;
					float x1, x2, y1, y2;

					//Box Vars Local
					std::string enthealth = std::to_string(ent->Health) + "hp";
					std::string distancefromplayer = std::to_string(distanceint / 10);
					std::string playername = ent->PlayerInfo->Name;
					std::string playerkills = "K:" + std::to_string(ent->PlayerInfo->Kills);


					
					if (Math::WorldToScreen(entpos, screen, viewMatrix)) {
						float ADS = 1 + self->PlayerInfo->ADS;
						if (ADS < 2)
						{
							x1 = screen.x - ((g_GameVariables->boxwidth / (distance * (0.0025f))));
							y1 = screen.y - ((g_GameVariables->boxheight / (distance * (0.0025f))));
							x2 = screen.x + ((g_GameVariables->boxwidth / (distance * (0.0025f))));
							y2 = screen.y;
						}
						else
						{
							x1 = screen.x - ((g_GameVariables->boxwidth / (distance * (0.0025f))) * (1.5) * ADS);
							y1 = screen.y - ((g_GameVariables->boxheight / (distance * (0.0025f))) * (1.7) * ADS);
							x2 = screen.x + ((g_GameVariables->boxwidth / (distance * (0.0025f))) * (1.5) * ADS);
							y2 = screen.y;
						}

						if (g_espbox)
						{
							if (p_team)
							{
								if (ownteam == entteam)
								{
									ImGui::GetWindowDrawList()->AddRect(ImVec2(x1, y1), ImVec2(x2, y2), ImColor(g_GameVariables->friendlyBoxcolour));

									if (p_name)
									{
										ImVec2 textSize = ImGui::CalcTextSize(playername.c_str());
										ImVec2 textPosition(x1 + (g_GameVariables->boxwidth - textSize.x) / 2, y2 - textSize.y); // Center the text horizontally and position it at the bottom of the box

										ImGui::GetWindowDrawList()->AddText(textPosition, ImColor(g_GameVariables->boxtextcolour), playername.c_str());
									}
								}
							}

							if (p_enemy)
							{
								if (ownteam != entteam)
								{
									ImGui::GetWindowDrawList()->AddRect(ImVec2(x1, y1), ImVec2(x2, y2), ImColor(g_GameVariables->enemyBoxcolour));

									
								}
							}
						}

							if (g_snaplines)
							{

								if (p_team)
								{

									if (ownteam == entteam)
									{


										ImGuiIO& io = ImGui::GetIO();
										ImGui::GetWindowDrawList()->AddLine(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y), ImVec2(screen.x, screen.y + 3), ImColor(g_GameVariables->friendlysnaplinecolour), 1.f);
									}

								}

								if (p_enemy)
								{
									if (ownteam != entteam)
									{
										ImGuiIO& io = ImGui::GetIO();
										ImGui::GetWindowDrawList()->AddLine(ImVec2(io.DisplaySize.x / 2, io.DisplaySize.y), ImVec2(screen.x, screen.y + 3), ImColor(g_GameVariables->enemysnaplinecolour), 1.f);
									}
								}




							}


							if (p_team)
							{

								if (ownteam == entteam)
								{


									std::string displayString;

									if (g_distance)
									{
										displayString += "[" + distancefromplayer + "]" + " ";
									}
									if (p_name)
									{
										displayString += playername + " ";
									}

									if (g_health)
									{
										displayString += enthealth + " ";
									}

									if (p_kills)
									{
										displayString += "(" + playerkills + ")";
									}
									ImVec2 textSize = ImGui::CalcTextSize(displayString.c_str());
									ImVec2 textPosition(x1 + (g_GameVariables->boxwidth - textSize.x) / 2, y2 - textSize.y);
									ImGui::GetWindowDrawList()->AddText(textPosition, ImColor(g_GameVariables->boxtextcolour), displayString.c_str());

								}
								
							}
							if (p_enemy)
							{
								if (ownteam != entteam)
								{
									
									std::string displayString;

									// Inside the if statements, append the specific variable strings to the displayString
									if (g_distance)
									{
										displayString += "["+ distancefromplayer +"]" + " ";
									}
									if (p_name)
									{
										displayString += playername + " ";
									}

									if (g_health)
									{
										displayString += enthealth + " ";
									}

									if (p_kills)
									{
										displayString += "(" +playerkills+")";
									}
									ImVec2 textSize = ImGui::CalcTextSize(displayString.c_str());
									ImVec2 textPosition(x1 + (g_GameVariables->boxwidth - textSize.x) / 2, y2 - textSize.y);
									ImGui::GetWindowDrawList()->AddText(textPosition, ImColor(g_GameVariables->boxtextcolour), displayString.c_str());
								}
							}

							


					}

				}

			}
					
			ImGui::End();
			ImGui::PopStyleColor();
		}
			
		
	}
		
}

