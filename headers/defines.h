#pragma once

//#pragma warning( disable:4251 )
//#pragma warning( disable:4275 )
// 'function': was declared deprecated
// бестолковое MS-обновление 'устаревших' функций
// ...ломает слишком дохуя кода, причем бессмысленно(c)
#pragma warning( disable : 4996 )
//#define D_SCL_SECURE_NO_WARNINGS
// Тупорылая VS допускает exception specification, но как всегда нихера не поддерживает
// З.Ы. актуально и для VS2015
#pragma warning( disable : 4290 )

#ifdef INTERFACE
#undef INTERFACE
#endif
#define INTERFACE

#ifdef ABSTRACT
#undef ABSTRACT
#endif
#define ABSTRACT

#ifdef OVERRIDE
#undef OVERRIDE
#endif
#define OVERRIDE

#ifndef WM_MOUSEWHEEL
#	define WM_MOUSEWHEEL 0x020A
#endif

#define __TRY__ try{
#define __CATCH__ } catch( std::exception exc ) {\
std::string _what    ( exc.what() );     /* Bad argument exception in */\
std::string _function( __FUNCTION__ ); /* MCore::Setup */ \
std::string _file    ( __FILE__ );     /* File: MCore.cpp */ \
std::string _line    ( std::to_string( __LINE__ ) );     /* Line: 144 */ \
std::string _nl      ( "\n" ); \
std::string _full( _what + _nl + _function + _nl + _file + _nl + _line ); \
throw std::exception( _full.c_str() );\
}

#define stringify( val ) #val"\0"

/******** Т И П Ы ********/
typedef unsigned __int8  uint8;
typedef unsigned __int16 uint16;
typedef unsigned __int32 uint32;
typedef unsigned __int64 uint64;
typedef unsigned   long  ulong;
typedef unsigned   short ushort;

typedef signed   __int8  int8;
typedef signed   __int16 int16;
typedef signed   __int32 int32;
typedef signed   __int64 int64;

template<typename T> void __delete (T e){ if(e != 0){ delete    e; } e = 0; }
template<typename T> void __deletea(T e){ if(e != 0){ delete[]  e; } e = 0; }
template<typename T> void __release(T e){ if(e != 0){ e->release(); } e = 0; }
template<typename T> void __Release(T e){ if(e != 0){ e->Release(); } e = 0; }
template<typename T> void __destroy(T e){ if(e != 0){ e->destroy(); } e = 0; }

#include <defines-classes.h>
#include <defines-meshes.h>
#include <defines-input.h>

namespace endless
{
    class _CFG
    {
    public:

        std::string appname              = "SOME NAME";
        std::string datapath             = "../data/";
        float       window_w             = 1920.f;
        float       window_h             = 1020.f;
        bool        window_borderless    = true;
        bool        window_fullscreen    = false;
        bool        render_vsync         = false;
	    long        render_msaa          = 1; // 0-none; 1-16 more powerfull MSAA
	    long        render_msaa_quality  = 1; // can't be more than can your device
	    float       render_znear         = 0.001f;
        float       render_zfar          = 10000.f;
        float       render_fov           = 45.f;
        float       render_cam_rot_speed = 20.f;
        long        snd_max_channels     = 100;
		float       snd_doppler_scale    = 1.f;
		float       snd_distance_factor  = 1.f;
		float       snd_rolloff_scale    = 1.f;
        XMFLOAT3    phy_gravity          = { 0.f, -98.1f, 0.f };
	    float       phy_timestep         = 120.f;

    }; // class _CFG

    static _CFG CFG;
    
} // namespace endless
