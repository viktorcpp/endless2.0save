
namespace endless
{
    void MCore::Run()
    {
        __TRY__

        MCore::TIMER_GLOB->RemTimeRun();

        HWND _hWnd = MWINDOW->GetHandle();
        BOOL _ret  = false;
        MSG  _msg;

        ZeroMemory( &_msg, sizeof(_msg) );

        while( _msg.message != WM_QUIT )
        {
            if( MWINDOW->IsActive() )
            {
                if( PeekMessage( &_msg, NULL, NULL, NULL, PM_REMOVE ) )
                {
                    TranslateMessage(&_msg);
                    DispatchMessage(&_msg);
                }

                MCore::TIMER_GLOB->RemTimeFrameBegin();

                MCore::INPUT   ->ReadKb();
                MCore::PHYSICS ->Update();
                MCore::WORLD   ->Update();
                MCore::RENDERER->Update();
                MCore::SOUND   ->Update();

                MCore::INPUT->ResetMouse();
                MCore::TIMER_GLOB->RemTimeFrameEnd();
            }
            else
            {
                if( GetMessage( &_msg, NULL, 0, 0 ) )
                {
                    TranslateMessage(&_msg);
                    DispatchMessage(&_msg);
                }
            }

        } // while

        //UnregisterClass( CFG.appname.c_str(), GetModuleHandle(NULL) );

        __CATCH__

    } // Run

    void MCore::Exit()
    {
        is_destroyed = true;
        PostQuitMessage(0);

    } // Exit

    void MCore::Pause(bool ispaused)
    {
        MCore::TIMER_GLOB->RemTimeFrameBegin();

        is_paused = ispaused;

    } // Pause

    void MCore::PauseOnHUD( bool ispaused )
    {
        MCore::TIMER_GLOB->RemTimeFrameBegin();

        is_paused_hud = ispaused;

    } // PauseOnHUD

    LRESULT CALLBACK MCore::MsgPump(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        RECT _rect;
        GetWindowRect(hWnd, &_rect);

        MCore::INPUT->ResetUpKeys();

        //SCITER +
        if( message != WM_CREATE )
        {
            BOOL handled = FALSE;
            LRESULT lr = SciterProcND( hWnd, message, wParam, lParam, &handled );
            //if( handled )
            //    return lr;
        }
        //SCITER -
        
        switch(message)
        {
        case WM_INPUT:
            MCore::INPUT->ReadM( lParam );
            break;

        case WM_SETCURSOR:
            {
                SetCursor( LoadCursor(NULL, IDC_ARROW) );
                return TRUE;
            }
            break;

        case WM_MOUSEWHEEL:
            break;

        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
            ::SetCapture(hWnd);
            ::SetForegroundWindow(hWnd);
            break;

        case WM_CHAR:
            break;

        case WM_CREATE:
            SetForegroundWindow(hWnd);
            break;

        case WM_ACTIVATE:
            MCore::WINDOW->Activate( !wParam == WA_INACTIVE );
            SetForegroundWindow(hWnd);
            break;

        case WM_DESTROY: case WM_CLOSE: case WM_QUIT:
            {
                MCore::WINDOW->Activate(false);
                ::ClipCursor(0);
                exit(0);
            }
            break;

        default:
            break;

        } // switch

        return DefWindowProc(hWnd, message, wParam, lParam);

    } // MsgPump

    void MCore::Setup()
    {
        __TRY__

            LOGN( "%s: init:\n\n", __FUNCTION__ );

            MCore::RESPROVIDER    = new MResProvider();
            MCore::MRESLOADER     = new MResLoader();
            MCore::WINDOW         = new MWindow();
            MCore::PHYSICS        = new MPhysics();
            MCore::RENDERERDRIVER = new MRendererDriver();
            MCore::RENDERER       = new MRenderer();
            MCore::SOUND          = new MSound();
            MCore::HUD            = new MHud();
            MCore::INPUT          = new MInput();
            MCore::ASSETSDB       = new MAssetsDB();
            MCore::RESMANAGER     = new MResManager();

            MCore::SCRIPTS        ->Setup();
            MCore::SOUND          ->Setup();
            MCore::RESPROVIDER    ->Setup();
            MCore::MRESLOADER     ->Setup();
            MCore::TIMER_GLOB     ->Setup();
            MCore::WINDOW         ->Setup();
            MCore::RENDERERDRIVER ->Setup();
            MCore::RENDERER       ->Setup();
            MCore::HUD            ->Setup();
            MCore::PHYSICS        ->Setup();
            MCore::INPUT          ->Setup();
            MCore::ASSETSDB       ->Setup();
            MCore::RESMANAGER     ->Setup();

            MCore::WORLD = new MWorld();
            MCore::WORLD->Setup();

            // TEST
            MTexture* test_tex1 = nullptr;
            test_tex1 = MCore::RESPROVIDER->LoadTexture( "ground_0001" );

            MTexture* test_tex2 = nullptr;
            test_tex2 = MCore::RESPROVIDER->LoadTexture( "oil_barrel_01" );

            MCore::RENDERER->test_mesh   = MCore::RESPROVIDER->LoadMesh( "terrain_placeholder_0001" );
            MCore::RENDERER->test_mesh->SetTexture( test_tex1 );

            MCore::RENDERER->test_mesh2  = MCore::RESPROVIDER->LoadMesh( "oil_barrel_0001" );
            MCore::RENDERER->test_mesh2->SetTexture( test_tex2 );

            MRigidBody* mrb = MCore::RESPROVIDER->LoadRigid( "terrain_placeholder" );
            std::vector<PxActor*> rblist = mrb->Rigid();
            for( long x = 0; x < (long)rblist.size(); ++x )
            {
                MCore::PHYSICS->AddRigid( rblist[x] );
            }

            MRigidBody* mrb2 = MCore::RESPROVIDER->LoadRigid( "hummer_damaged_0001" );
            rblist = mrb2->Rigid();
            for( long x = 0; x < (long)rblist.size(); ++x )
            {
                MCore::PHYSICS->AddRigid( rblist[x] );
            }
            // test

            is_initialized = true;

            LOGN( "%s: ready\n\n", __FUNCTION__ );

        __CATCH__

    } // Setup

    HINSTANCE MCore::Module( HINSTANCE hInstance )
    {
        if( hInstance != nullptr )
            hinstance = hInstance;

        return hinstance;

    } // Module

    MLogger*         MCore::LOGGER         = nullptr;
    MScripts*        MCore::SCRIPTS        = nullptr;
    MTimer*          MCore::TIMER_GLOB     = nullptr;
    MResProvider*    MCore::RESPROVIDER    = nullptr;
    MWindow*         MCore::WINDOW         = nullptr;
    MPhysics*        MCore::PHYSICS        = nullptr;
    MRendererDriver* MCore::RENDERERDRIVER = nullptr;
    MRenderer*       MCore::RENDERER       = nullptr;
    MSound*          MCore::SOUND          = nullptr;
    MHud*            MCore::HUD            = nullptr;
    MInput*          MCore::INPUT          = nullptr;
    MAssetsDB*       MCore::ASSETSDB       = nullptr;
    MResManager*     MCore::RESMANAGER     = nullptr;
    MWorld*          MCore::WORLD          = nullptr;
    MResLoader*      MCore::MRESLOADER     = nullptr;
    std::recursive_mutex MCore::main_thread_mutex = {};

    MCore::MCore():
        is_destroyed(false),
        is_paused(false),
        is_initialized(false)
    {
        MCore::LOGGER     = new MLogger();
        MCore::SCRIPTS    = new MScripts();
        MCore::TIMER_GLOB = new MTimer();

    } // MCore

    MCore::~MCore()
    {
        is_destroyed   = true;
        is_initialized = false;

    } // ~MCore

    template<> MCore* Singleton<MCore>::_instance = 0;

} // namespace endless
