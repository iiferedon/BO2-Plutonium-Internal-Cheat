#include <wtypes.h>
#include <memory>
#include "../ImGui/imgui.h"
namespace Raven {
	class Menu
	{
	public:
		

		
		Menu()  noexcept = default;
		~Menu() noexcept = default;
		Menu(Menu const&) = delete;
		Menu(Menu&&) = delete;
		Menu& operator=(Menu const&) = delete;
		Menu& operator=(Menu&&) = delete;

		void Draw();
		void MainMenu();
		void Esp();
		void HUD(bool* p_open);
		void Loops();
		void DrawOtherWindows();
		void DebugEntWindow();
	private:
		bool m_StyleInit{};
		
		
	};
	inline std::unique_ptr<Menu> g_Menu;
}