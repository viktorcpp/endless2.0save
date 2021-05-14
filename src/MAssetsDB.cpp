
namespace endless
{
    void MAssetsDB::Setup()
    {
        __TRY__

        LOGN( "%s init:\n", __FUNCTION__ );
        
        std::unique_ptr<MAssetsDB_Meshes> mdb_meshes( new MAssetsDB_Meshes() );
        mdb_meshes->Load( *this );

        std::unique_ptr<MAssetsDB_GameObjects> mdb_gameobjects( new MAssetsDB_GameObjects() );
        mdb_gameobjects->Load( *this );

        std::unique_ptr<MAssetsDB_Materials> mb_materials( new MAssetsDB_Materials() );
        mb_materials->Load( *this );

        std::unique_ptr<MAssetsDB_Rigids> mdb_rigids( new MAssetsDB_Rigids() );
        mdb_rigids->Load(*this);

        std::unique_ptr<MAssetsDB_Textures> mdb_textures( new MAssetsDB_Textures() );
        mdb_textures->Load( *this );

        LOGN( "%s ready\n\n", __FUNCTION__ );

        __CATCH__

    } // Setup

    MAssetsDB::MAssetsDB():
        assetmeshdata(),
        assettexturedata(),
        assetmaterialdata()
    {}

    MAssetsDB::~MAssetsDB()
    {}

    MAssetsDB::MAssetsDB(MAssetsDB&)
    {}

    template<> MAssetsDB* Singleton<MAssetsDB>::_instance = 0;

} // namespace endless
