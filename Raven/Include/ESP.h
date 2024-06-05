#include <wtypes.h>
#include <memory>
#include <atomic>
namespace Raven {

	class Renderer
	{
	public:


		
		
		void _fastcall Esp();
		explicit Renderer();
		~Renderer() noexcept = default;
		Renderer(Renderer const&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(Renderer const&) = delete;
		Renderer& operator=(Renderer&&) = delete;
		
	
	};
	
	//Window Bools
	//inline std::atomic_bool debugzombieentlist;
	//inline std::atomic_bool debugentlistwindow;
	
	inline std::unique_ptr<Renderer> g_Renderer;
}