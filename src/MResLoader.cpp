
namespace endless
{
    void MResLoader::LoadTexture( MTexture** tex, const char* path )
    {
        std::lock_guard<std::recursive_mutex> locker( self_mutex );

    } // LoadTexture

    void MResLoader::LoadMesh( MMesh** mesh, const char* path )
    {
        std::lock_guard<std::recursive_mutex> locker( self_mutex );

    } // LoadMesh

    void MResLoader::LoadRigid( MRigidBody** rb, const char* path )
    {
        std::lock_guard<std::recursive_mutex> locker( self_mutex );

    } // LoadRigid

    void MResLoader::Setup()
    {
        if( is_ready ) return;

        __TRY__

        self_thread = std::thread( &MResLoader::Run, this );

        is_ready = true;

        __CATCH__

    } // Setup

    void MResLoader::Run()
    {//return;
        while( true )
        {
            try
            {
                std::lock_guard<std::recursive_mutex> locker( self_mutex );
                
                ulong t = (ulong)time(0);
                //LOGN( "Mutex test: %d\n", t );

                std::this_thread::sleep_for( std::chrono::milliseconds(100/3) );
            }
            catch(std::exception exc)
            {
                std::lock_guard<std::recursive_mutex> locker( self_mutex );
                exceptions.push_back( std::current_exception() );
            }

        } // while
        
    } // Setup

    MResLoader::MResLoader()
    {}

    MResLoader::MResLoader(MResLoader&)
    {}

    MResLoader::~MResLoader()
    {}

    template<> MResLoader* Singleton<MResLoader>::_instance  = 0;

} // namespace endless
