#pragma once

namespace endless
{

#define MINPUT MInput::Ref()

    class MInput : public Singleton<MInput>
    {
    public:

        enum MOUSE_BTNS : int
        {
            MB_L = 0,
            MB_R,
            MB_M
        };

        enum MOUSE_STATE : int
        {
            MNONE = 0,
            MDOWN = 1,
            MUP   = 2
        };

        enum KEY_STATE : int
	    {
		    NONE = 0,
		    DOWN = 1,
		    UP   = 2
	    };

        struct MouseData
        {
            struct _position
            {
                int x = 0;
                int y = 0;

            } position;

            struct _delta
            {
                int x = INT_MIN;
                int y = INT_MIN;

            } delta;

            MOUSE_STATE buttons[3];
            ushort wheel = 0;

        }; // struct MouseData

        KEY_STATE   GetKeyState( KEY_CODE key ){ return (KEY_STATE)keys[key]; }
        bool        GetKeyUp   ( KEY_CODE key ){ return (KEY_STATE)keys[key] == KEY_STATE::UP; }
        bool        GetKeyDown ( KEY_CODE key ){ return (KEY_STATE)keys[key] == KEY_STATE::DOWN; }

        MOUSE_STATE GetMouseState( MOUSE_BTNS mb ){ return mousedata.buttons[mb]; }
        bool        GetMouseUp   ( MOUSE_BTNS mb ){ return mousedata.buttons[mb] == MOUSE_STATE::MUP;   }
        bool        GetMouseDown ( MOUSE_BTNS mb ){ return mousedata.buttons[mb] == MOUSE_STATE::MDOWN; }
        ushort      GetMouseWheel(){ return mousedata.wheel; }

        long GetMousePosX()  { return mousedata.position.x; }
	    long GetMousePosY()  { return mousedata.position.y; }
        long GetMouseDeltaX(){ return mousedata.delta.x; }
	    long GetMouseDeltaY(){ return mousedata.delta.y; }

        void OnKey( KEY_CODE key, KEY_STATE state );

        MInput();
        virtual ~MInput();

    private:

        KEY_STATE keys[512] = {KEY_STATE::NONE};
        MouseData mousedata = {};
        
        void ReadM( LPARAM lParam );
        void ReadKb();
        
        void ResetUpKeys();
        void ResetMouse();

        void Setup();
        void UpdateKb(int key);

        MInput(MInput&);

        friend class MCore;

    }; // class MInput

} // namespace endless
