#pragma once

namespace endless
{
    void MSound::PlayUI( const char* id )
    {
        channel_ui->setPaused(true);
        fmod_system->playSound( FMOD_CHANNEL_FREE, sounds_ui[id].sound, true, &channel_ui );
        channel_ui->setPaused(false);

    } // PlayUI

    void MSound::Update()
    {}

    void MSound::Setup()
    {
        __TRY__

        LOGN("%s: init:\n", __FUNCTION__);

        FMOD_ASSERT( FMOD::System_Create(&fmod_system) );
        FMOD_ASSERT( fmod_system->init(CFG.snd_max_channels, FMOD_INIT_NORMAL, 0) );
        FMOD_ASSERT( fmod_system->set3DSettings( CFG.snd_doppler_scale, CFG.snd_distance_factor, CFG.snd_rolloff_scale ) );

        LoadSoundsUI();

        LOGN("%s: ready\n\n", __FUNCTION__);

        __CATCH__

    } // Setup

    void MSound::LoadSoundsUI()
    {
        MScripts* ms = MCore::GetMScripts();
        std::stringstream buffer;
        MUtils::FileLoadBuffer( (CFG.datapath + "assets.sounds.js").c_str(), buffer );
        duk_context* context = duk_create_heap(nullptr, nullptr, nullptr, nullptr, MScripts::duk_fatal_handle );
        ms->DoString( context, buffer.str().c_str() );

        long n = (long)duk_get_length( context, -1 );
        for( long i = 0; i < n; i++ )
        {
            SOUND_FILE sf;
            duk_get_prop_index( context, -1, i );

                ms->GetPropString( context, "id",         sf.id_str );
                ms->GetPropString( context, "path",       sf.path );
                ms->GetPropLong  ( context, "load_type",  (long&)sf.load_type );
                ms->GetPropLong  ( context, "sound_type", (long&)sf.sound_type );

                sf.path = CFG.datapath + sf.path;

            duk_pop(context); // duk_get_prop_index

            sounds_ui[sf.id_str] = sf;
            
            FMOD_MODE fmode = FMOD_LOOP_OFF|FMOD_2D;
            fmode |= sf.load_type == FLT_LOAD ? FMOD_CREATESAMPLE : FMOD_CREATESTREAM;

            FMOD_ASSERT( fmod_system->createStream( sounds_ui[sf.id_str].path.c_str(), fmode, 0, &sounds_ui[sf.id_str].sound ) );
        }

        duk_destroy_heap(context);

        buffer.str("");
        buffer.clear();

    } // LoadSoundsUI

    inline bool MSound::FMOD_ASSERT(FMOD_RESULT result)
    {
        if( result != FMOD_OK )
        {
            LOGE( "FMOD FAILED: %s\n", FMOD_ErrorString(result) );
            return false;
        }

        return true;

    } // FMOD_ERRCHECK

    MSound::MSound():
        hr(FMOD_OK),
        fmod_system(nullptr),
        fmod_error(nullptr),
        channel_ui(nullptr),
        sounds_ui()
    {}

    MSound::MSound(MSound&)
    {}

    MSound::~MSound()
    {}

    template<> MSound* Singleton<MSound>::_instance = 0;

} // namespace endless
