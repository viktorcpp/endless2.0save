
namespace endless
{

    void MResManager::LoadTexture( MTexture** tex, std::string id )
    {
        __TRY__

        auto t = textures.find( id );

        if( t != textures.end() )
        {
            *tex = t->second;
        }
        
        textures[id] = MCore::GetMResProvider()->LoadTexture(id.c_str());

        *tex = textures[id];

        __CATCH__

    } // LoadTexture

    void MResManager::LoadMesh( MMesh** mesh, std::string id )
    {
        __TRY__

        auto m = meshes.find( id );

        if( m != meshes.end() )
        {
            *mesh = m->second;
        }

        meshes[id] = MCore::GetMResProvider()->LoadMesh( id.c_str() );

        *mesh = meshes[id];

        __CATCH__

    } // LoadMesh

    void MResManager::LoadRigid( MRigidBody** rb, std::string id )
    {
        __TRY__

        auto r = rigids.find( id );

        if( r != rigids.end() )
        {
            *rb = r->second;
        }

        rigids[id] = new MRigidBody();
        *rb = rigids[id];

        __CATCH__

    } // LoadRigid

    void MResManager::Setup()
    {
        __TRY__

        LOGN( "%s init:\n", __FUNCTION__ );

        //

        LOGN( "%s ready\n\n", __FUNCTION__ );

        __CATCH__

    } // Setup

    MResManager::MResManager()
    {}

    MResManager::MResManager(MResManager&)
    {}

    MResManager::~MResManager()
    {}

    template<> MResManager* Singleton<MResManager>::_instance = 0;

} // namespace endless
