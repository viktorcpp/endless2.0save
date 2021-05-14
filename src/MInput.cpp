
namespace endless
{
    void MInput::OnKey( KEY_CODE key, KEY_STATE state ){ keys[key] = state; }

    void MInput::ResetUpKeys()
    {
        for( int x = 0; x < sizeof(keys)/4; x++ )
        {
            if( keys[x] == KEY_STATE::UP )
                keys[x] = KEY_STATE::NONE;
        }

    } // ResetUpKeys

    void MInput::ResetMouse()
    {
        mousedata.wheel   = 0;
        mousedata.delta.x = 0;
        mousedata.delta.y = 0;

    } // ResetMouse

    void MInput::Setup()
    {
        __TRY__

        LOGN( "%s init:\n", __FUNCTION__ );

        ZeroMemory( keys, sizeof(keys) );

        RAWINPUTDEVICE Rid[1];
        Rid[0].usUsagePage = 0x01;
        Rid[0].usUsage     = 0x02;
        Rid[0].dwFlags     = 0;//RIDEV_NOLEGACY;
        Rid[0].hwndTarget  = MWINDOW->GetHandle();

        if( RegisterRawInputDevices( Rid, 1, sizeof(Rid[0]) ) == FALSE )
        {
            std::string buffer;
            LOGE( "ERROR: registration failed. Call GetLastError for the cause of the error.\n%s\n", MUtils::TranslateLastError(buffer).c_str() );
        }

        LOGN( "%s ready\n\n", __FUNCTION__ );

        __CATCH__

    } // Setup

    void MInput::ReadM( LPARAM lParam )
    {
        UINT      _data_size = 0;
        LPBYTE    _data      = nullptr;
        RAWINPUT* _data_raw  = nullptr;

        GetRawInputData( (HRAWINPUT)lParam, RID_INPUT, NULL, &_data_size, sizeof(RAWINPUTHEADER) );

        _data = new BYTE[_data_size];

        if( GetRawInputData( (HRAWINPUT)lParam, RID_INPUT, _data, &_data_size, sizeof(RAWINPUTHEADER) ) != _data_size )
        {
            LOGE( "GetRawInputData does not return correct size !\n" );
            return;
        }

        _data_raw = (RAWINPUT*)_data;

        switch( _data_raw->header.dwType )
        {
        case RIM_TYPEMOUSE:
            
            {
                mousedata.wheel = 0;

                mousedata.delta.x = _data_raw->data.mouse.lLastX;
                mousedata.delta.y = _data_raw->data.mouse.lLastY;
                
                POINT cp;
                GetCursorPos(&cp);
                ScreenToClient( MCore::GetMWindow()->GetHandle(), &cp );
                mousedata.position.x = cp.x;
                mousedata.position.y = cp.y;
            
                if( mousedata.buttons[MOUSE_BTNS::MB_L] == MOUSE_STATE::MUP ) mousedata.buttons[MOUSE_BTNS::MB_L] = MOUSE_STATE::MNONE;
                if( mousedata.buttons[MOUSE_BTNS::MB_R] == MOUSE_STATE::MUP ) mousedata.buttons[MOUSE_BTNS::MB_R] = MOUSE_STATE::MNONE;
                if( mousedata.buttons[MOUSE_BTNS::MB_M] == MOUSE_STATE::MUP ) mousedata.buttons[MOUSE_BTNS::MB_M] = MOUSE_STATE::MNONE;
                
                if( _data_raw->data.mouse.usButtonFlags )
                switch( _data_raw->data.mouse.usButtonFlags )
                {
                case RI_MOUSE_LEFT_BUTTON_DOWN:   mousedata.buttons[MOUSE_BTNS::MB_L] = MOUSE_STATE::MDOWN; break;
                case RI_MOUSE_LEFT_BUTTON_UP:     mousedata.buttons[MOUSE_BTNS::MB_L] = MOUSE_STATE::MUP;   break;
                case RI_MOUSE_RIGHT_BUTTON_DOWN:  mousedata.buttons[MOUSE_BTNS::MB_R] = MOUSE_STATE::MDOWN; break;
                case RI_MOUSE_RIGHT_BUTTON_UP:    mousedata.buttons[MOUSE_BTNS::MB_R] = MOUSE_STATE::MUP;   break;
                case RI_MOUSE_MIDDLE_BUTTON_DOWN: mousedata.buttons[MOUSE_BTNS::MB_M] = MOUSE_STATE::MDOWN; break;
                case RI_MOUSE_MIDDLE_BUTTON_UP:   mousedata.buttons[MOUSE_BTNS::MB_M] = MOUSE_STATE::MUP;   break;
                case RI_MOUSE_WHEEL: mousedata.wheel = _data_raw->data.mouse.usButtonData; break;
                }

            } // case RIM_TYPEMOUSE
            break;

        case RIM_TYPEKEYBOARD:
            break;

        case RIM_TYPEHID:
            break;

        } // switch

        __deletea(_data);

    } // ReadM

    void MInput::ReadKb()
    {
        UpdateKb(KEY_CODE::KEY_A);
		UpdateKb(KEY_CODE::KEY_B);
		UpdateKb(KEY_CODE::KEY_C);
		UpdateKb(KEY_CODE::KEY_D);
		UpdateKb(KEY_CODE::KEY_E);
		UpdateKb(KEY_CODE::KEY_F);
		UpdateKb(KEY_CODE::KEY_G);
		UpdateKb(KEY_CODE::KEY_H);
		UpdateKb(KEY_CODE::KEY_I);
		UpdateKb(KEY_CODE::KEY_J);
		UpdateKb(KEY_CODE::KEY_K);
		UpdateKb(KEY_CODE::KEY_L);
		UpdateKb(KEY_CODE::KEY_M);
		UpdateKb(KEY_CODE::KEY_N);
		UpdateKb(KEY_CODE::KEY_O);
		UpdateKb(KEY_CODE::KEY_P);
		UpdateKb(KEY_CODE::KEY_Q);
		UpdateKb(KEY_CODE::KEY_R);
		UpdateKb(KEY_CODE::KEY_S);
		UpdateKb(KEY_CODE::KEY_T);
		UpdateKb(KEY_CODE::KEY_U);
		UpdateKb(KEY_CODE::KEY_V);
		UpdateKb(KEY_CODE::KEY_W);
		UpdateKb(KEY_CODE::KEY_X);
		UpdateKb(KEY_CODE::KEY_Y);
		UpdateKb(KEY_CODE::KEY_Z);

        UpdateKb(KEY_CODE::KEY_ESCAPE);
		UpdateKb(KEY_CODE::KEY_TAB);
		UpdateKb(KEY_CODE::KEY_CAPS);
		UpdateKb(KEY_CODE::KEY_LSHIFT);
		UpdateKb(KEY_CODE::KEY_RSHIFT);
		UpdateKb(KEY_CODE::KEY_LCONTROL);
		UpdateKb(KEY_CODE::KEY_RCONTROL);
		UpdateKb(KEY_CODE::KEY_MENU);
		UpdateKb(KEY_CODE::KEY_LMENU);
		UpdateKb(KEY_CODE::KEY_RMENU);
		UpdateKb(KEY_CODE::KEY_SPACE);
		UpdateKb(KEY_CODE::KEY_ENTER);
		UpdateKb(KEY_CODE::KEY_BACKSPACE);

        UpdateKb(KEY_CODE::KEY_ARROW_LEFT);
		UpdateKb(KEY_CODE::KEY_ARROW_UP);
		UpdateKb(KEY_CODE::KEY_ARROW_RIGHT);
		UpdateKb(KEY_CODE::KEY_ARROW_DOWN);

		UpdateKb(KEY_CODE::KEY_PAGE_UP);
		UpdateKb(KEY_CODE::KEY_PAGE_DOWN);
		UpdateKb(KEY_CODE::KEY_END);
		UpdateKb(KEY_CODE::KEY_HOME);
		UpdateKb(KEY_CODE::KEY_INSERT);
		UpdateKb(KEY_CODE::KEY_DELETE);

		UpdateKb(KEY_CODE::KEY_PRINT);
		UpdateKb(KEY_CODE::KEY_SCROLL_LOCK);
		UpdateKb(KEY_CODE::KEY_PAUSE);

        UpdateKb(KEY_CODE::KEY_F1 );
		UpdateKb(KEY_CODE::KEY_F2 );
		UpdateKb(KEY_CODE::KEY_F3 );
		UpdateKb(KEY_CODE::KEY_F4 );
		UpdateKb(KEY_CODE::KEY_F5 );
		UpdateKb(KEY_CODE::KEY_F6 );
		UpdateKb(KEY_CODE::KEY_F7 );
		UpdateKb(KEY_CODE::KEY_F8 );
		UpdateKb(KEY_CODE::KEY_F9 );
		UpdateKb(KEY_CODE::KEY_F10);
		UpdateKb(KEY_CODE::KEY_F11);
		UpdateKb(KEY_CODE::KEY_F12);

		UpdateKb(KEY_CODE::KEY_0);
		UpdateKb(KEY_CODE::KEY_1);
		UpdateKb(KEY_CODE::KEY_2);
		UpdateKb(KEY_CODE::KEY_3);
		UpdateKb(KEY_CODE::KEY_4);
		UpdateKb(KEY_CODE::KEY_5);
		UpdateKb(KEY_CODE::KEY_6);
		UpdateKb(KEY_CODE::KEY_7);
		UpdateKb(KEY_CODE::KEY_8);
		UpdateKb(KEY_CODE::KEY_9);

        UpdateKb(KEY_CODE::KEY_TILDE);

    } // ReadKb

    void MInput::UpdateKb( int key )
	{
		if( GetAsyncKeyState(key) & 0x8000 )
			keys[key] = KEY_STATE::DOWN;
		else
			if( keys[key] == KEY_STATE::DOWN )
				keys[key] = KEY_STATE::UP;
			else
				keys[key] = KEY_STATE::NONE;

	} // UpdateKb

    MInput::MInput():
        keys(),
        mousedata()
    {
        ZeroMemory( keys, sizeof(keys) );
        ZeroMemory( &mousedata, sizeof(mousedata) );
    }

    MInput::MInput(MInput&)
    {}

    MInput::~MInput()
    {}

    template<> MInput* Singleton<MInput>::_instance = 0;

} // namespace endless
