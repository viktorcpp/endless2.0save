#pragma once

namespace endless
{
    class MHudAPI : public sciter::event_handler
    {
    public:

        sciter::value HUDAPI_CursorClip( sciter::value clip );
        sciter::value HUDAPI_CursorVis ( sciter::value vis );
        sciter::value HUDAPI_CursorPos ( sciter::value x, sciter::value y );
        sciter::value HUDAPI_OnBtnExit();
        sciter::value HUDAPI_DisplayResList();
        sciter::value HUDAPI_PauseOnHUD( sciter::value pause );

        BEGIN_FUNCTION_MAP
            FUNCTION_1( "HUDAPI_CursorClip",     HUDAPI_CursorClip );
            FUNCTION_1( "HUDAPI_CursorVis",      HUDAPI_CursorVis );
            FUNCTION_2( "HUDAPI_CursorPos",      HUDAPI_CursorPos );
            FUNCTION_0( "HUDAPI_OnBtnExit",      HUDAPI_OnBtnExit );
            FUNCTION_0( "HUDAPI_DisplayResList", HUDAPI_DisplayResList );
            FUNCTION_1( "HUDAPI_PauseOnHUD",     HUDAPI_PauseOnHUD );
        END_FUNCTION_MAP

    }; // class MHudAPI

} // namespace endless
