#include "../ImGui/imgui.h"
#include "../Include/Variables.h"
#include "../Include/Menu.h"
#include "../Include/Console.h"
#include "../Include/Offsets.h"
#include "../Include/Math.h"
#include "../Include/Vectors.h"
#include "../Ioctl.h"
//#include "../Include/entrypoint.h"
#pragma warning(disable : 26812)

namespace Raven
{
    auto center = [](float avail_width, float element_width, float padding = 0)
    {
        ImGui::SameLine((avail_width / 2) - (element_width / 2) + padding);
    };

    auto center_text = [&](const char* format, float spacing = 15, ImColor color = ImColor(255, 255, 255)) {
        center(ImGui::GetContentRegionAvail().x, ImGui::CalcTextSize(format).x);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + spacing);
        ImGui::TextColored(color.Value, format);
    };







    namespace Styles {
        void InitStyle()
        {
            
            ImGuiStyle* style = &ImGui::GetStyle();

            // Setting up colors
            ImVec4* colors = style->Colors;
            colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);  // Text color
            colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);  // Disabled text color
            colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.0f);  // Window background color
            colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.0f);  // Child window background color
            colors[ImGuiCol_PopupBg] = ImVec4(0.08f, 0.08f, 0.08f, 0.94f);  // Popup background color
            colors[ImGuiCol_Border] = ImVec4(0.39f, 0.16f, 0.67f, 1.0f);  // Window border color
            colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);  // Window border shadow color
            colors[ImGuiCol_FrameBg] = ImVec4(0.40f, 0.40f, 0.40f, 0.60f);  // Frame background color
            colors[ImGuiCol_FrameBgHovered] = ImVec4(0.45f, 0.45f, 0.45f, 0.60f);  // Frame background color when hovered
            colors[ImGuiCol_FrameBgActive] = ImVec4(0.50f, 0.50f, 0.50f, 0.60f);  // Frame background color when active
            colors[ImGuiCol_TitleBg] = ImVec4(0.39f, 0.16f, 0.67f, 1.0f);  // Title bar background color
            colors[ImGuiCol_TitleBgActive] = ImVec4(0.39f, 0.16f, 0.67f, 1.0f);  // Title bar background color when active
            colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.39f, 0.16f, 0.67f, 1.0f);  // Title bar background color when collapsed
            colors[ImGuiCol_MenuBarBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.94f);  // Menu bar background color
            colors[ImGuiCol_ScrollbarBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.94f);  // Scrollbar background color
            colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.40f, 0.40f, 0.40f, 0.60f);  // Scrollbar grab color
            colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.45f, 0.45f, 0.45f, 0.60f);


            colors[ImGuiCol_Tab] = ImVec4(0.20f, 0.20f, 0.20f, 0.80f);
            colors[ImGuiCol_TabHovered] = ImVec4(0.41f, 0.07f, 0.62f, 1.0f);
            colors[ImGuiCol_TabActive] = ImVec4(0.41f, 0.07f, 0.62f, 1.0f);
            colors[ImGuiCol_TabUnfocused] = ImVec4(0.20f, 0.20f, 0.20f, 0.80f);
            colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.80f);

            // Adjusting menu tab positioning
            style->WindowPadding = ImVec2(8.0f, 8.0f);
            style->ItemSpacing = ImVec2(4.0f, 8.0f);
            style->FramePadding = ImVec2(4.0f, 4.0f);
            style->ItemInnerSpacing = ImVec2(4.0f, 4.0f);
            style->IndentSpacing = 24.0f;
            style->ScrollbarSize = 10.0f;

            // Adjusting tab size and spacing
            style->TabRounding = 4.0f;
            style->TabBorderSize = 0.0f;
            style->WindowRounding = 0.0f;
            style->FrameRounding = 4.0f;
            style->IndentSpacing = 24.0f;


        }
    }



    void Menu::Draw()
    {

        //MainMenu();


    }

    



    bool entlistwindow = false;
   


    void Menu::MainMenu()
    {
        
       

        //Styles::InitStyle();
        
        if (g_ShowMainMenu == true)
        {
            ImGui::SetWindowFocus("Fatality");

            float ImGuiWidth = 400.f;
            float ImGuiHeight = 250.f;
            if (ImGui::Begin("Fatality", &g_GameVariables->m_ShowMenu, ImGuiWindowFlags_NoResize))
            {
                Styles::InitStyle();
                ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 5.0f);
                //ImGui::PushStyleColor(ImGuiCol_Border, ImColor(0, 0, 0, 255).Value);
                ImGui::SetWindowSize(ImVec2((float)ImGuiWidth, (float)ImGuiHeight));
                if (ImGui::BeginTabBar("tabs"))
                {
                    if (ImGui::BeginTabItem("Player"))
                    {
                        bool aimbot = g_aimbot.load();
                        ImGui::Checkbox("Aimbot", &aimbot);
                        g_aimbot.store(aimbot);

                        ImGui::EndTabItem();
                    }
    
                    if (ImGui::BeginTabItem("World"))
                    {
                        
                        

                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("ESP"))
                    {
                        //ESP
                        bool espwindow = g_espwindow.load();
                        ImGui::Checkbox("Esp", &espwindow);
                        g_espwindow.store(espwindow);

                        ImGui::SameLine();

                        //BOX
                        bool espbox = g_espbox.load();
                        ImGui::Checkbox("Box", &espbox);
                        g_espbox.store(espbox);

                        
                        
                        ImGui::SameLine();

                        //SNAPLINES
                        bool snaplines = g_snaplines.load();
                        ImGui::Checkbox("Snaplines", &snaplines);
                        g_snaplines.store(snaplines);

                        //NAME
                        bool name = p_name.load();
                        ImGui::Checkbox("Name", &name);
                        p_name.store(name);

                        ImGui::SameLine();

                        //HEALTH
                        bool health = g_health.load();
                        ImGui::Checkbox("Health", &health);
                        g_health.store(health);

                        //KILLS
                        bool kills = p_kills.load();
                        ImGui::Checkbox("Kills", &kills);
                        p_kills.store(kills);

                        ImGui::SameLine();

                        //DISTANCE
                        bool distance = g_distance.load();
                        ImGui::Checkbox("Distance", &distance);
                        g_distance.store(distance);
                        
                        //TEAM
                        bool team = p_team.load();
                        ImGui::Checkbox("Friendly", &team);
                        p_team.store(team);

                        ImGui::SameLine();

                        //ENEMY
                        bool enemy = p_enemy.load();
                        ImGui::Checkbox("Enemy", &enemy);
                        p_enemy.store(enemy);
                        


                      

                        ImGui::Checkbox("Debug EntList", &entlistwindow);


                        ImGui::EndTabItem();
                    }

                    if (ImGui::BeginTabItem("Config"))
                    {
                        
                        ImGui::SliderInt("Box Width", &g_GameVariables->boxwidth, 10, 60);
                        ImGui::SliderInt("Box Height", &g_GameVariables->boxheight, 20, 300);
                        ImGui::SliderFloat("Box Text", &g_GameVariables->boxtextsize, 0.1f, 3.0f);
                        ImGui::ColorEdit3("Team Box", (float*)&g_GameVariables->friendlyBoxcolour);
                        ImGui::ColorEdit3("Enemy Box", (float*)&g_GameVariables->enemyBoxcolour);
                        ImGui::ColorEdit3("Box Text Colour", (float*)&g_GameVariables->boxtextcolour);
                        ImGui::ColorEdit3("Team Snapline", (float*)&g_GameVariables->friendlysnaplinecolour);
                        ImGui::ColorEdit3("Enemy Snapline", (float*)&g_GameVariables->enemysnaplinecolour);
                        

                        ImGui::EndTabItem();
                    }

                    ImGui::EndTabBar();
                }
                ImGui::End();
            }

        }
        
        //ImGui::GetIO().MouseDrawCursor = g_GameData->debugentlistwindow;

        if (entlistwindow)
        {
            if (ImGui::Begin(" Ent List ", &entlistwindow))
            {

                Offsets::gentity_t* self = GetGentity(0);
                std::string viewangles = "MyViewAngles: " + std::to_string(self->Angles.X) + ", " + std::to_string(self->Angles.Y);
                ImGui::Text("%s", viewangles.c_str());
                for (int i = 1; i < 40; i++)
                {
                    Offsets::gentity_t* ent = GetGentity(i);
                    if (ent->Health > 0)
                    {
                        std::string clientNumStr = "Client#: " + std::to_string(ent->ClientNum);
                        std::string typeStr = "Type: " + std::to_string(ent->Type);
                        std::string HealthNumStr = "Health: " + std::to_string(ent->Health);
                        //std::string Distance = "Distance: " + (std::to_string(Math::VecDistance(self->Position, ent->Position)));
                        std::string Coords = "Position: " + (std::to_string(ent->Position[0]) + " " + std::to_string(ent->Position[1]) + " " + std::to_string(ent->Position[2]));
                        std::string IsTeam = "Team: " + (std::to_string(ent->TeamInfo->Team));
                        std::string ADS = "ADS: " + (std::to_string(ent->PlayerInfo->ADS));
                        std::string HeldWeapon = "WeaponR: " + (std::to_string(ent->HeldWeapon));
                        
                        
                        ImGui::Text("%s", clientNumStr.c_str());
                        ImGui::SameLine();
                        ImGui::Text("%s", HealthNumStr.c_str());
                        ImGui::SameLine();
                        ImGui::Text("%s", typeStr.c_str());
                        ImGui::SameLine();
                        ImGui::Text("%s", Coords.c_str());
                        ImGui::SameLine();
                        //ImGui::Text("%s", Distance.c_str());
                        //ImGui::SameLine();
                        ImGui::Text("%s", IsTeam.c_str());
                        ImGui::SameLine();
                        ImGui::Text("%s", ADS.c_str());
                        

                    }

                }

                ImGui::End();
            }
        }




        




       
    }



    void Menu::Loops()
    {


        /*
        if (p_name)
        {
            UINT_PTR address = 0x01066040;
            int value = 4;
            bool result = write_kernel_int(address, value);

        }
        */

        



        /* if (g_GameData->debugzombieentconsole)
         {
             Offsets::gentity_t* self = GetGentity(0);

             for (int i = 0; i < 1024; i++) {
                 Offsets::gentity_t* ent = GetGentity(i);
                 if (ent->Health > 0 && Math::VecDistance(self->Position, ent->Position) > 0 && ent->ClientNum < 100 && (ent->Type == EntityType::ZOMBIE || ent->Type == EntityType::PLAYER)) {


                     g_Console->printdbg("\n\nClient#: \n\n" + ent->ClientNum, g_Console->color.blue);
                     g_Console->printdbg("\n\nX: \n\n" + posX, g_Console->color.green);
                     g_Console->printdbg("\n\nY: \n\n" + posY, g_Console->color.green);
                     g_Console->printdbg("\n\nZ: \n\n" + posZ, g_Console->color.green);
                     g_Console->printdbg("\n\nType: \n\n" + ent->Type, g_Console->color.red);
                     g_Console->printdbg("\n\nHealth: \n\n" + ent->Health, g_Console->color.dark_pink);

                     ConsoleDebug::Value("Client#: ", ent->ClientNum);
                     ConsoleDebug::Value("X: ", ent->Position[0]);
                     ConsoleDebug::Value("Y: ", ent->Position[1]);
                     ConsoleDebug::Value("Z: ", ent->Position[2]);
                     ConsoleDebug::Value("Type: ", ent->Type);
                     ConsoleDebug::Value("Health: ", ent->Health);
                     ConsoleDebug::Value("Distance", Math::VecDistance(self->Position, ent->Position));
                     //ConsoleDebug::Value("Team", ent->TeamInfo->Team);

                     //if (ent->Type == EntityType::PLAYER) {
                     //	std::cout << "PlayerInfo Gravity: " << ent->PlayerInfo->Gravity << std::endl;
                     //	std::cout << "PlayerInfo Weapon2Clip: " << ent->PlayerInfo->Weapon2Clip << std::endl;
                     //	std::cout << "PlayerInfo Headshots: " << ent->PlayerInfo->Headshots << std::endl;
                     //	std::cout << "PlayerInfo Headshots&: " << &ent->PlayerInfo->Headshots << std::endl;
                     //	std::cout << "PlayerInfo Kills: " << ent->PlayerInfo->Kills << std::endl;
                     //	std::cout << "PlayerInfo Kills&: " << &ent->PlayerInfo->Kills << std::endl;
                     //	std::cout << "PlayerInfo Score: " << ent->PlayerInfo->Score << std::endl;
                     //	std::cout << "PlayerInfo Score&: " << &ent->PlayerInfo->Score << std::endl;
                     //	std::cout << "PlayerInfo LethalAmmo: " << ent->PlayerInfo->LethalAmmo << std::endl;
                     //	std::cout << "PlayerInfo LethalAmmo&: " << &ent->PlayerInfo->LethalAmmo << std::endl;
                     //	std::cout << "PlayerInfo Name: " << ent->PlayerInfo->Name << std::endl;
                     //	std::cout << "PlayerInfo Name&: " << &ent->PlayerInfo->Name << std::endl;
                     //	std::cout << "PlayerInfo Weapon1Clip: " << ent->PlayerInfo->Weapon1Clip << std::endl;
                     //}
                     g_Console->printdbg("\n\n#################################\n\n", g_Console->color.red);
                     Sleep(1000);

                 }
             }

    }
        */
    }
}
        






