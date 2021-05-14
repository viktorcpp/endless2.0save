
namespace endless
{
    sciter::value MHudAPI::HUDAPI_CursorClip( sciter::value clip )
    {
        if( MCore::GetMHud() )
        {
            MCore::GetMHud()->CursorClip( clip.get<bool>() );
        }

        return sciter::value();

    } // HUDAPI_CursorClip

    sciter::value MHudAPI::HUDAPI_CursorVis( sciter::value vis )
    {
        if( MCore::GetMHud() )
        {
            MCore::GetMHud()->CursorVis( vis.get<bool>() );
        }

        return sciter::value();

    } // HUDAPI_CursorVis

    sciter::value MHudAPI::HUDAPI_CursorPos( sciter::value x, sciter::value y )
    {
        if( MCore::GetMHud() )
        {
            MCore::GetMHud()->CursorPos( x.get<int>(), y.get<int>() );
        }

        return sciter::value();

    } // HUDAPI_CursorPos

    sciter::value MHudAPI::HUDAPI_OnBtnExit()
    {
        if( MCore::Ref() )
        {
            MCore::Ref()->Exit();
        }

        return sciter::value();

    } // HUDAPI_OnBtnExit

    sciter::value MHudAPI::HUDAPI_DisplayResList()
    {
        if( MRendererDriver::Ref() )
        {
            std::string out  = "[";
            auto& ret = MRendererDriver::Ref()->GetResolutionsList();
            std::unordered_map<std::string, MRendererDriver::DisplayResolution>::iterator it;
            for( it= ret.begin(); it != ret.end(); ++it )
            {
                out += MUtils::string_format( "{ \"str\":\"%s\", \"w\":\"%d\", \"h\":\"%d\" },", it->first.c_str(), it->second.w, it->second.h );
            }
            out += "]";

            return sciter::value( std::wstring( out.begin(), out.end() ) );
        }

        return sciter::value();
    }

    sciter::value MHudAPI::HUDAPI_PauseOnHUD( sciter::value pause )
    {
        MCore::Ref()->PauseOnHUD( pause.get<bool>() );

        return sciter::value();

    } // HUDAPI_PauseOnHUD

} // namespace endless
