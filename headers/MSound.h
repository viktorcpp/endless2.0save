#pragma once

#include <fmod.hpp>
#include <fmod_errors.h>
#ifndef _DEBUG
#pragma comment(lib, "fmodex64_vc.lib")
#else
//#    pragma comment(lib, "fmodexL64_vc.lib")
#    pragma comment(lib, "fmodex64_vc.lib")
#endif

namespace endless
{
    typedef enum _SOUND_FILE_LOAD_TYPE
    {
        FLT_NULL = 0,
        FLT_STREAM,
        FLT_LOAD

    } SOUND_FILE_LOAD_TYPE;

    typedef enum _SOUND_FILE_TYPE
    {
        SFT_NULL = 0,
        SFT_2D,
        SFT_3D

    } SOUND_FILE_TYPE;

    typedef struct _SOUND_FILE
    {
        long                 id         = -1;
        std::string          id_str     = "";
        std::string          path       = "";
        SOUND_FILE_LOAD_TYPE load_type  = SOUND_FILE_LOAD_TYPE::FLT_NULL;
        SOUND_FILE_TYPE      sound_type = SOUND_FILE_TYPE::SFT_NULL;
        FMOD::Sound*         sound      = nullptr; // for sound controller only

    } SOUND_FILE;

    class MSound : public Singleton<MSound>
    {
    public:

        void PlayUI( const char* id );

        void Setup() throw(std::exception);

        void Update();

        MSound();
        virtual ~MSound();

    private:

        FMOD_RESULT                                 hr          = FMOD_OK;
        FMOD::System*                               fmod_system = nullptr;
        const char*                                 fmod_error  = nullptr;
        FMOD::Channel*                              channel_ui  = nullptr;
        std::unordered_map<std::string, SOUND_FILE> sounds_ui;

        void LoadSoundsUI();

        static inline bool FMOD_ASSERT(FMOD_RESULT result);

        MSound(MSound&);

    }; // class MSound

} // namespace endless
