#pragma once

#include <MHudAPI.h>

namespace endless
{
    class MHud : public Singleton<MHud>
    {
    public:

        void LogConsoleN( const char* str );
        void LogConsoleW( const char* str );
        void LogConsoleE( const char* str );

        void Frame() throw(std::exception);
        void Setup() throw(std::exception);
        void CursorClip( bool clip );
        void CursorVis ( bool vis );
        void CursorPos ( int x, int y );

        UINT DoLoadData( LPSCN_LOAD_DATA pnmld );
        UINT DoAttachBehavior( LPSCN_ATTACH_BEHAVIOR lpab );

        MHud();
        virtual ~MHud();

    private:

        class FPS
        {
        public:
            void Update();
            std::string GetFPS(){ return fps_buffer; }

        private:
            float       fps_timer_begin = -1.f;
            long        fps_frames      = 0;
            std::string fps_buffer      = "";

        }; // class FPS

        HCURSOR              cur_default = nullptr;
        bool                 is_ready    = NULL;
        MHudAPI              hudapi;
        sciter::dom::element fore_layer;
        sciter::dom::element root;
        FPS                  fps;

        static UINT SC_CALLBACK SciterCallback( LPSCITER_CALLBACK_NOTIFICATION pns, LPVOID callbackParam );

        MHud(MHud&);

        friend class MHudConsole;
        friend class MHudMenuExit;

    }; // class MHud

} // namespace endless
