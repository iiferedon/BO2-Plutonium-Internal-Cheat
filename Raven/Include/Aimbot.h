namespace Raven {

	class AimbotInstance
	{
	public:




		void Aimbot();
		explicit AimbotInstance();
		~AimbotInstance() noexcept = default;
		AimbotInstance(AimbotInstance const&) = delete;
		AimbotInstance(AimbotInstance&&) = delete;
		AimbotInstance& operator=(AimbotInstance const&) = delete;
		AimbotInstance& operator=(AimbotInstance&&) = delete;




	};

	//Window Bools
	//inline std::atomic_bool debugzombieentlist;
	//inline std::atomic_bool debugentlistwindow;

	inline std::unique_ptr<AimbotInstance> g_AimbotInstance;
}