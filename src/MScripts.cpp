
namespace endless
{
    void MScripts::DoString( std::string str )
    {
        DoString( str.c_str() );

    } // DoString

    void MScripts::DoString( const char* str )
    {
        duk_eval_string( context, str );

    } // DoString

    void MScripts::DoString( duk_context* context, std::string str )
    {
        duk_eval_string( context, str.c_str() );

    } // DoString

    void MScripts::DoString( duk_context* context, const char* str )
    {
        duk_eval_string( context, str );

    } // DoString

    void MScripts::DoFile( std::string filename )
    {
        __TRY__
        
        DoFile( filename.c_str() );

        __CATCH__

    } // DoFile

    void MScripts::DoFile( const char* filename )
    {
        __TRY__

        if( !MUtils::FileExists(filename) )
        {
            std::string error = MUtils::string_format( "%s : File <%s> not found", __FUNCTION__, filename );
            throw std::exception( error.c_str() );
        }

        std::stringstream buffered;
        MUtils::FileLoadBuffer( filename, buffered );

        if( buffered.str().size() < 1 )
        {
            std::string error = MUtils::string_format( "%s : File <%s> found but seems empty", __FUNCTION__, filename );
            throw std::exception( error.c_str() );
        }
        
        duk_eval_string( context, buffered.str().c_str() );

        buffered.str("");
        buffered.clear();

        __CATCH__

    } // DoScriptFromFile

    void MScripts::CallFunc( const char* func_name )
    {
        //

    } // CallFunc

    // return Value as String
    // GetC( "CFG.window.width" ).c_str();
    std::string MScripts::GetC( const char* str_script )
    {
        duk_eval_string( context, str_script );

        return std::string( duk_to_string(context, -1) );

    } // GetC

    int MScripts::GetI(const char* name)
    {
        duk_eval_string( context, name );

        return duk_to_int(context, -1);

    } // GetI

    double MScripts::GetD(const char* name)
    {
        duk_eval_string( context, name );

        return (double)duk_to_number(context, -1);

    } // GetD

    float MScripts::GetF(const char* name)
    {
        duk_eval_string( context, name );

        return (float)duk_get_number(context, -1);

    } // GetF

    bool MScripts::GetB(const char* name)
    {
        duk_eval_string( context, name );

        return (long)duk_to_int(context, -1) == 1L;

    } // GetB

    void MScripts::Setup()
    {
        __TRY__

        LOGN("%s init:\n", __FUNCTION__);

        std::string path_js_test  = CFG.datapath + "scripts/!test.js";
        std::string path_js_sound = CFG.datapath + "sound/sound.js";

        context = duk_create_heap( nullptr, nullptr, nullptr, nullptr, duk_fatal_handle );
	    
        duk_eval_string( context, "var CFG={};" );

        DoFile( CFG.datapath + "endless.js" );

        CFG.appname              = GetC( "CFG.AppName" );
        CFG.datapath             = GetC( "CFG.DataPath" );
        CFG.window_w             = GetF( "CFG.Window.iWidth"      );
        CFG.window_h             = GetF( "CFG.Window.iHeight"     );
        CFG.window_borderless    = GetB( "CFG.Window.bBorderless" );
        CFG.window_fullscreen    = GetB( "CFG.Window.bFullscreen" );
        CFG.render_vsync         = GetB( "CFG.Render.bUseVsync"       );
	    CFG.render_msaa          = GetI( "CFG.Render.iMSAA"           );
	    CFG.render_msaa_quality  = GetI( "CFG.Render.iMSAAQuality"    );
	    CFG.render_znear         = GetF( "CFG.Render.fZNear"          );
        CFG.render_zfar          = GetF( "CFG.Render.fZFar"           );
        CFG.render_fov           = GetF( "CFG.Render.fFOV"            );
        CFG.render_cam_rot_speed = GetF( "CFG.Render.fCamRotateSpeed" );
        CFG.snd_max_channels     = GetI( "CFG.Sound.iMaxChannels"           );
	    CFG.snd_doppler_scale    = GetF( "CFG.Sound.Volume.fDopplerScale"   );
	    CFG.snd_distance_factor  = GetF( "CFG.Sound.Volume.fDistanceFactor" );
	    CFG.snd_rolloff_scale    = GetF( "CFG.Sound.Volume.fRolloffScale"   );
        CFG.phy_gravity.x        = GetF( "CFG.Physics.Gravity.x" );
        CFG.phy_gravity.y        = GetF( "CFG.Physics.Gravity.y" );
        CFG.phy_gravity.z        = GetF( "CFG.Physics.Gravity.z" );
	    CFG.phy_timestep         = GetF( "CFG.Physics.fTimestep" );

        cfg_def.appname              = CFG.appname;
        cfg_def.datapath             = CFG.datapath;
        cfg_def.window_w             = CFG.window_w;
        cfg_def.window_h             = CFG.window_h;
        cfg_def.window_h             = CFG.window_h;
        cfg_def.window_fullscreen    = CFG.window_fullscreen;
        cfg_def.render_vsync         = CFG.render_vsync;
	    cfg_def.render_msaa          = CFG.render_msaa;
	    cfg_def.render_msaa_quality  = CFG.render_msaa_quality;
	    cfg_def.render_znear         = CFG.render_znear;
        cfg_def.render_zfar          = CFG.render_zfar;
        cfg_def.render_fov           = CFG.render_fov;
        cfg_def.render_cam_rot_speed = CFG.render_cam_rot_speed;
        cfg_def.snd_max_channels     = CFG.snd_max_channels;
	    cfg_def.snd_doppler_scale    = CFG.snd_doppler_scale;
	    cfg_def.snd_distance_factor  = CFG.snd_distance_factor;
	    cfg_def.snd_rolloff_scale    = CFG.snd_rolloff_scale;
        cfg_def.phy_gravity.x        = CFG.phy_gravity.x;
        cfg_def.phy_gravity.y        = CFG.phy_gravity.y;
        cfg_def.phy_gravity.z        = CFG.phy_gravity.z;
	    cfg_def.phy_timestep         = CFG.phy_timestep;

        DoFile( path_js_test .c_str() );
        DoFile( path_js_sound.c_str() );

        LOGN("%s ready.\n\n", __FUNCTION__);
        
        __CATCH__

    } // Setup

    void MScripts::GetPropString( duk_context* context, const char* prop, std::string& dest )
    {
        duk_get_prop_string(context, -1, prop);
            dest = duk_to_string(context, -1);
        duk_pop(context); // duk_get_prop_string

    } // GetPropString

    void MScripts::GetPropFloat( duk_context* context, const char* prop, float& dest )
    {
        duk_get_prop_string( context, -1, prop );
            dest = (float)duk_to_number(context, -1);
        duk_pop(context);

    } // GetPropFloat

    void MScripts::GetPropLong( duk_context* context, const char* prop, long& dest )
    {
        duk_get_prop_string( context, -1, prop );
            dest = (long)duk_to_int(context, -1);
        duk_pop(context);

    } // GetPropInt

    void MScripts::duk_fatal_handle( void* udata, const char* msg )
    {
        LOGE( "Duktape fatal: %s\n", msg );

    } // duk_fatal_handle

    MScripts::MScripts():
        context(nullptr),
        cfg_def()
    {}

    MScripts::MScripts(MScripts&)
    {}

    MScripts::~MScripts()
    {
        if( context != nullptr )
            duk_destroy_heap( context );

    } // ~MScripts

    template<> MScripts* Singleton<MScripts>::_instance = 0;

} // namespace endless
