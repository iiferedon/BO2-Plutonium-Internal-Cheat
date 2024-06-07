#include "pch.h"
#include "include/DirectX11.h"
#include "include/entrypoint.h"

#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#include "Include/Console.h"
#include <thread>
#include "Include/Variables.h"
#include "Include/Menu.h"
#include "Include/ESP.h"
#include "Include/Aimbot.h"
#include "Ioctl.h"
using namespace Raven;

	bool ShowMenu = false;
	bool ImGui_Initialised = false;

	namespace Process {
		DWORD ID;
		HANDLE Handle;
		HWND Hwnd;
		HMODULE Module;
		WNDPROC WndProc;
		int WindowWidth;
		int WindowHeight;
		LPCSTR Title;
		LPCSTR ClassName;
		LPCSTR Path;
	}

	namespace DirectX11Interface {
		ID3D11Device* Device;
		ID3D11DeviceContext* DeviceContext;
		ID3D11RenderTargetView* RenderTargetView;
	}

	extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT APIENTRY WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		if (g_ShowMainMenu) {
			ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam);
			return true;
		}
		
		
		return CallWindowProc(Process::WndProc, hwnd, uMsg, wParam, lParam);
	}

	HRESULT APIENTRY MJPresent(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
		static bool ImGui_Initialised = false;

		if (!ImGui_Initialised) {
			if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), (void**)&DirectX11Interface::Device))) {
				ImGui::CreateContext();
				ImGuiIO& io = ImGui::GetIO();
				io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
				io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

				DirectX11Interface::Device->GetImmediateContext(&DirectX11Interface::DeviceContext);

				DXGI_SWAP_CHAIN_DESC Desc;
				pSwapChain->GetDesc(&Desc);
				WindowHwnd = Desc.OutputWindow;

				ID3D11Texture2D* BackBuffer;
				pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
				DirectX11Interface::Device->CreateRenderTargetView(BackBuffer, NULL, &DirectX11Interface::RenderTargetView);
				BackBuffer->Release();

				ImGui_ImplWin32_Init(WindowHwnd);
				ImGui_ImplDX11_Init(DirectX11Interface::Device, DirectX11Interface::DeviceContext);
				ImGui_ImplDX11_CreateDeviceObjects();
				ImGui::GetIO().ImeWindowHandle = Process::Hwnd;
				Process::WndProc = (WNDPROC)SetWindowLongPtr(Process::Hwnd, GWLP_WNDPROC, (__int3264)(LONG_PTR)WndProc);
				ImGui_Initialised = true;
			}
		}

		
		if (GetAsyncKeyState(VK_INSERT) & 1) g_ShowMainMenu = !g_ShowMainMenu;

		
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		
		ImGui::GetIO().MouseDrawCursor = g_ShowMainMenu;

		
		g_Menu->MainMenu();
		g_Renderer->Esp();
		//g_AimbotInstance->Aimbot();

		
		ImGui::EndFrame();
		ImGui::Render();

		
		DirectX11Interface::DeviceContext->OMSetRenderTargets(1, &DirectX11Interface::RenderTargetView, NULL);
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		return oIDXGISwapChainPresent(pSwapChain, SyncInterval, Flags);
	}

	void APIENTRY MJDrawIndexed(ID3D11DeviceContext* pContext, UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation) {

	}


	void ClientBGThread()
	{
		while (true) {
			g_Menu->Loops();
			Sleep(1);
			std::this_thread::yield();
		}
	}

	DWORD WINAPI MainThread(LPVOID lpParameter) {
		bool WindowFocus = false;
		while (WindowFocus == false) {
			DWORD ForegroundWindowProcessID;
			GetWindowThreadProcessId(GetForegroundWindow(), &ForegroundWindowProcessID);
			if (GetCurrentProcessId() == ForegroundWindowProcessID) {

				Process::ID = GetCurrentProcessId();
				Process::Handle = GetCurrentProcess();
				Process::Hwnd = GetForegroundWindow();

				RECT TempRect;
				GetWindowRect(Process::Hwnd, &TempRect);
				Process::WindowWidth = TempRect.right - TempRect.left;
				Process::WindowHeight = TempRect.bottom - TempRect.top;

				char TempTitle[MAX_PATH];
				GetWindowText(Process::Hwnd, TempTitle, sizeof(TempTitle));
				Process::Title = TempTitle;

				char TempClassName[MAX_PATH];
				GetClassName(Process::Hwnd, TempClassName, sizeof(TempClassName));
				Process::ClassName = TempClassName;

				char TempPath[MAX_PATH];
				GetModuleFileNameEx(Process::Handle, NULL, TempPath, sizeof(TempPath));
				Process::Path = TempPath;

				WindowFocus = true;
			}
		}
		bool InitHook = false;
		while (InitHook == false) {
			if (DirectX11::Init() == true) {
				CreateHook(8, (void**)&oIDXGISwapChainPresent, MJPresent);
				CreateHook(12, (void**)&oID3D11DrawIndexed, MJDrawIndexed);
				InitHook = true;
			}
		}

		g_Console = std::make_unique<Console>();

		g_Console->InitializeConsole("Fatality");
		g_Console->printdbg(R"(
    ______      __        ___ __           ___________ __  _______ 
   / ____/___ _/ /_____ _/ (_) /___  __   /_  __/ ___//  |/  / __ \
  / /_  / __ `/ __/ __ `/ / / __/ / / /    / / / __ \/ /|_/ / /_/ /
 / __/ / /_/ / /_/ /_/ / / / /_/ /_/ /    / / / /_/ / /  / / ____/ 
/_/    \__,_/\__/\__,_/_/_/\__/\__, /    /_/  \____/_/  /_/_/      
                              /____/                               
)", g_Console->color.teal);
		g_GameData = std::make_unique<GameData>();
		g_GameVariables = std::make_unique<GameVariables>();
		g_Menu = std::make_unique<Menu>();
		if (DirectX11::Init() == true) 
		{
			g_Console->printdbg("Hooking...\n", g_Console->color.pink);
		}
		if (g_GameData && g_GameVariables != NULL)
		{
			g_Console->printdbg("...\n", g_Console->color.pink);
		}
		
		g_Console->printdbg("Cheat Enabled\n", g_Console->color.green);
		g_Console->printdbg("#Press Insert to open\n", g_Console->color.green);
		

		return 0;
	}



	BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved) {
		switch (dwReason) {
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls(hModule);
			if (ChecktDirectXVersion(DirectXVersion.D3D11) == true) {
				Process::Module = hModule;
				CreateThread(0, 0, MainThread, 0, 0, 0);
			}
			break;
		case DLL_PROCESS_DETACH:
			FreeLibraryAndExitThread(hModule, TRUE);
			DisableAll();
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		default:
			break;
		}
		return TRUE;
	}






