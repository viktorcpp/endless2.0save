
namespace endless
{
    MWindow::MWindow():
        hWnd(nullptr),
        is_centered(false),
        is_active(true)
    {}

    OVERRIDE void MWindow::Setup()
    {
        __TRY__

        WNDCLASSEX wclex = {};
        wclex.cbSize        = sizeof(WNDCLASSEX);
	    wclex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	    wclex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	    wclex.hIcon         = LoadIcon( MCORE->Module(), MAKEINTRESOURCE(IDI_ICON1) );
	    wclex.hIconSm       = LoadIcon( MCORE->Module(), MAKEINTRESOURCE(IDI_ICON1) );
	    wclex.hInstance     = MCORE->Module();
	    wclex.lpfnWndProc   = MCore::MsgPump;
	    wclex.lpszClassName = CFG.appname.c_str();
	    wclex.style         = CS_CLASSDC;
        
        RegisterClassEx(&wclex);

        hWnd = CreateWindow
        (
            CFG.appname.c_str(),
            CFG.appname.c_str(),
            1 ? WS_VISIBLE|WS_POPUP : WS_VISIBLE|WS_OVERLAPPED,
            0,
            0,
            (int)CFG.window_w,
            (int)CFG.window_h,
            GetDesktopWindow(),
            NULL,
            wclex.hInstance,
            (LPVOID) this
        );

        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);

        __CATCH__

    } // Create

    OVERRIDE void MWindow::SetVisible(bool vis)
    {
        ShowWindow( hWnd, vis ? SW_SHOW : SW_HIDE );

    } // SetVisible

    OVERRIDE void MWindow::MoveCenter(int width, int height)
    {
	    RECT rect;
	    GetClientRect(hWnd, &rect);
	    int w = rect.right-rect.left;
	    int h = rect.bottom-rect.top;
	    if(w < width)  width  += width-w;
	    if(h < height) height += height-h;
	    int L = (GetSystemMetrics(SM_CXSCREEN) - width)/2;
	    int T = (GetSystemMetrics(SM_CYSCREEN) - height)/2;
	    MoveWindow(hWnd, L, T, width, height, TRUE);
        is_centered = true;

    } // MoveCenter

    OVERRIDE void MWindow::Resize(int w, int h)
    {
        int L = (GetSystemMetrics(SM_CXSCREEN) - w)/2;
        int T = (GetSystemMetrics(SM_CYSCREEN) - h)/2;

        MoveWindow(hWnd, L, T, w, h, TRUE);

    } // Resize

    OVERRIDE void MWindow::Activate(bool activate)
    {
        is_active = activate;

        if( is_active )
            SetForegroundWindow(hWnd);

    } // Activate

    MWindow::~MWindow()
    {
        DestroyWindow(hWnd);
        UnregisterClass( CFG.appname.c_str(), GetModuleHandle(NULL) );
    }

    template<> MWindow* Singleton<MWindow>::_instance  = 0;
    
} // namespace endless
