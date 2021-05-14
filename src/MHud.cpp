
namespace endless
{
    std::stringstream logn_buffer;

    void MHud::LogConsoleN( const char* str )
    {
        if( is_ready )
        {
            if( logn_buffer.str().size() > 0 )
            {
                root.call_function( "UIAPI.LogN", logn_buffer.str().c_str() );

                logn_buffer.str("");
                logn_buffer.clear();
            }
            else
            {
                root.call_function( "UIAPI.LogN", str );
            }
        }
        else
        {
            logn_buffer << str << "<br>";
        }

    } // LogConsoleN

    void MHud::LogConsoleW( const char* str )
    {
        if( is_ready )
            root.call_function( "UIAPI.LogW", str );

    } // LogConsoleW

    void MHud::LogConsoleE( const char* str )
    {
        if( is_ready )
            root.call_function( "UIAPI.LogE", str );

    } // LogConsoleE

    void MHud::Frame()
    {
        __TRY__
        
        fps.Update();

        root.call_function( "UIAPI.SetFPS", fps.GetFPS().c_str() );

        if( fore_layer )
            SciterRenderOnDirectXWindow( MWINDOW->GetHandle(), fore_layer, TRUE );
        else
            SciterRenderOnDirectXWindow( MWINDOW->GetHandle(), NULL, FALSE );

        __CATCH__

    } // Frame

    void MHud::CursorClip( bool clip )
    {
        if( clip )
        {
            RECT _rect;
            
            ::GetWindowRect( MCore::GetMWindow()->GetHandle(), &_rect );
            ::ClipCursor(&_rect);
        }
        else
        {
            ::ClipCursor(0);
        }

    } // CursorClip

    void MHud::CursorVis( bool vis )
    {
        if( vis )
        {
            while( ShowCursor(true) < 0 );
        }
        else
        {
            while( ShowCursor(false) >= 0 );
        }

    } // CursorVis

    void MHud::CursorPos( int x, int y )
    {
        ::SetCursorPos( x, y );

    } // CursorPos

    void MHud::Setup()
    {
        __TRY__

        LOGN("%s init:\n", __FUNCTION__);

        HWND hWnd = MCore::GetMWindow()->GetHandle();
        
        BOOL r = SciterCreateOnDirectXWindow( hWnd, MCore::GetMRendererDriver()->GetSwapChain() );
        if( !r )
        {
            LOGE( "%s: SciterCreateOnDirectXWindow FAILED\n", __FUNCTION__ );
        }

        SciterSetOption( hWnd, SCITER_SET_DEBUG_MODE, TRUE );

        SciterSetCallback( hWnd, SciterCallback, NULL );

        sciter::attach_dom_event_handler( hWnd, &hudapi );

        std::string  path_html_main  = MUtils::GetCurDir() + "/" + CFG.datapath + "ui/Main.html";
        std::wstring wpath_html_main = std::wstring(L"file://") + fs::canonical( path_html_main ).c_str();
        r = SciterLoadFile( hWnd, wpath_html_main.c_str() );
        if( !r )
        {
            LOGE( "%s: loading Main.html FAILED\n", __FUNCTION__ );
        }

        root       = sciter::dom::element::root_element( hWnd );
        fore_layer = root.find_first( "#hud-main" );

        is_ready = true;

        LOGN( "%s ready.\n\n", __FUNCTION__ );
        LOGN( "<pre>    Sciter version: %u.%u</pre>\n", SciterVersion(true), SciterVersion(false) );

        char buff[] = stringify( 123 );
        LOGW( "Testing '%s'\n", buff );

        __CATCH__

    } // Setup

    UINT SC_CALLBACK MHud::SciterCallback( LPSCITER_CALLBACK_NOTIFICATION pns, LPVOID callbackParam )
    {
        switch( pns->code )
        {
        case SC_LOAD_DATA:
            return MHud::Ref()->DoLoadData((LPSCN_LOAD_DATA)pns);

        case SC_ATTACH_BEHAVIOR:
            return MHud::Ref()->DoAttachBehavior((LPSCN_ATTACH_BEHAVIOR)pns);
        }
        return 0;

    } // SciterCallback

    UINT MHud::DoLoadData( LPSCN_LOAD_DATA pnmld )
    {
        return LOAD_OK;

    } // DoLoadData

    UINT MHud::DoAttachBehavior( LPSCN_ATTACH_BEHAVIOR lpab )
    {
        sciter::event_handler* pb = sciter::behavior_factory::create( lpab->behaviorName, lpab->element );

        if( pb )
        {
            lpab->elementTag  = pb;
            lpab->elementProc = sciter::event_handler::element_proc;
            return TRUE;
        }

        return FALSE;

    } // DoAttachBehavior

    MHud::MHud()
    {
        cur_default = LoadCursor( NULL, IDC_ARROW );
    }

    MHud::MHud(MHud&)
    {}

    MHud::~MHud()
    {}

    template<> MHud* Singleton<MHud>::_instance = 0;

    void MHud::FPS::Update()
    {
        fps_frames++;

        if( fps_timer_begin < 0.f )
        {
            fps_timer_begin = (float)::GetCurrentTime();
            return;
        }

        if( ::GetCurrentTime() - fps_timer_begin > 1000.001f )
        {
            fps_buffer      = MUtils::string_format( "% 4d", fps_frames );
            fps_frames      = 0;
            fps_timer_begin = -1.f;
        }

    } // Update

} // namespace endless
