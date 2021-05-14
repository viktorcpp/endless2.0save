#pragma once

namespace endless
{

#define MCORE MCore::Ref()

    class MCore : public Singleton<MCore>
    {
    public:

        void Pause( bool ispaused = true );
        void PauseOnHUD( bool ispaused = true );

        bool IsPaused(){ return is_paused; }
        bool IsPausedHUD(){ return is_paused_hud; }
        bool IsDestroyed(){ return is_destroyed; }
        
        void Setup() throw(std::exception);
        void Run() throw(std::exception);
        void Exit();

        static LRESULT CALLBACK MsgPump(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

        HINSTANCE Module( HINSTANCE hInstance = nullptr );

        static inline MLogger*              const GetMLogger()        { return MCore::LOGGER; };
        static inline MScripts*             const GetMScripts()       { return MCore::SCRIPTS; };
        static inline MTimer*               const GetMTimer()         { return MCore::TIMER_GLOB; };
        static inline MResProvider*         const GetMResProvider()   { return MCore::RESPROVIDER; };
        static inline MWindow*              const GetMWindow()        { return MCore::WINDOW; };
        static inline MPhysics*             const GetMPhysics()       { return MCore::PHYSICS; };
        static inline MRendererDriver*      const GetMRendererDriver(){ return MCore::RENDERERDRIVER; };
        static inline MRenderer*            const GetMRenderer()      { return MCore::RENDERER; };
        static inline MSound*               const GetMSound()         { return MCore::SOUND; };
        static inline MHud*                 const GetMHud()           { return MCore::HUD; };
        static inline MInput*               const GetMInput()         { return MCore::INPUT; };
        static inline MAssetsDB*            const GetMAssetsDB()      { return MCore::ASSETSDB; };
        static inline MResManager*          const GetMResManager()    { return MCore::RESMANAGER; };
        static inline MWorld*               const GetMWorld()         { return MCore::WORLD; };
        static inline MResLoader*           const GetMResLoader()     { return MCore::MRESLOADER; };
        static inline std::recursive_mutex&       GetMutex()          { return main_thread_mutex; };

        MCore();
        ~MCore();

    private:

        static MLogger*             LOGGER;
        static MScripts*            SCRIPTS;
        static MTimer*              TIMER_GLOB;
        static MResProvider*        RESPROVIDER;
        static MWindow*             WINDOW;
        static MPhysics*            PHYSICS;
        static MRendererDriver*     RENDERERDRIVER;
        static MRenderer*           RENDERER;
        static MSound*              SOUND;
        static MHud*                HUD;
        static MInput*              INPUT;
        static MAssetsDB*           ASSETSDB;
        static MResManager*         RESMANAGER;
        static MWorld*              WORLD;
        static MResLoader*          MRESLOADER;
        static std::recursive_mutex main_thread_mutex;

        bool      is_destroyed   = false;
        bool      is_paused      = false;
        bool      is_paused_hud   = false;
        bool      is_initialized = false;
        HINSTANCE hinstance      = nullptr;

        MCore(MCore&);

    }; // class MCore

} // namespace endless
