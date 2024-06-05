#include <wtypes.h>
#include <memory>
#include <atomic>
#include "../ImGui/imgui.h"
namespace Raven {

	class GameData
	{
	public:

		//player
		
		bool noRecoil = false;
		bool rapid_fire = false;
		bool unlimited_ammo = false;
		bool no_recoil = false;
		bool godmode = false;
		

		//aimbot
		

		//Zombie ESP
		bool debugentlistwindow;
		bool debugzombieentconsole;
		//










		explicit GameData();
		~GameData() noexcept = default;
		GameData(GameData const&) = delete;
		GameData(GameData&&) = delete;
		GameData& operator=(GameData const&) = delete;
		GameData& operator=(GameData&&) = delete;
	};



	class GameVariables
	{
	public:

		
		int g_GamePid{};
		HANDLE g_GameHandle{};
		HWND g_GameWindow{};
		int g_GameWidth;
		int g_GameHeight;
		LPCSTR g_GameTitle;
		LPCSTR g_ClassName;
		LPCSTR g_GamePath;

		bool espwindow{};
		bool g_Running = true;
		bool m_ShowMenu{};
		bool m_ShowHud{};
		bool m_ShowDemo{};



		//Menu Options
		int boxheight = 90;
		int boxwidth = 20;
		float boxtextsize = 1.1f;
		//ImVec4 boxcolour = ImVec4(81.0f, 0.0f, 194.0f, 1.0f);
		ImVec4 boxtextcolour = ImVec4(0.0f, 227.0f, 169.0f, 1.0f);
		ImVec4 friendlyBoxcolour = ImVec4(0.0f, 255.0f, 0.0f, 1.0f);
		ImVec4 enemyBoxcolour = ImVec4(255.0f, 0.0f, 0.0f, 1.0f);

		ImVec4 friendlysnaplinecolour = ImVec4(0.0f, 230.0f, 65.0f, 1.0f);
		ImVec4 enemysnaplinecolour = ImVec4(255.0f, 0.0f, 0.0f, 1.0f);

		

		



		explicit GameVariables();
		~GameVariables() noexcept = default;
		GameVariables(GameVariables const&) = delete;
		GameVariables(GameVariables&&) = delete;
		GameVariables& operator=(GameVariables const&) = delete;
		GameVariables& operator=(GameVariables&&) = delete;

		void Init();
	};
	
	//Window Bools
	//inline std::atomic_bool debugzombieentlist;
	//inline std::atomic_bool debugentlistwindow;

	//ESP
	inline std::atomic_bool g_espwindow{};
	inline std::atomic_bool g_espbox{};
	inline std::atomic_bool g_snaplines{};

	inline std::atomic_bool p_team{};
	inline std::atomic_bool p_enemy{};

	inline std::atomic_bool p_name{};
	inline std::atomic_bool g_health{};
	inline std::atomic_bool g_distance{};
	inline std::atomic_bool p_kills{};

	//Aimbot
	inline std::atomic_bool g_aimbot{};


	//Zombie 
	inline std::atomic_bool z_health{}; 
	inline std::atomic_bool z_freeze{};



	inline std::atomic_bool g_ShowMainMenu = true;
	inline std::unique_ptr<GameData> g_GameData;
	inline std::unique_ptr<GameVariables> g_GameVariables;
}
//Being a little cunt
