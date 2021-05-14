
namespace endless
{
    void MWorld::Update()
    {
        __TRY__

        //

        __CATCH__

    } // Update

    void MWorld::Setup()
    {
        __TRY__

        std::unique_ptr<MWorld_AssetMain> mworld_assetmain( new MWorld_AssetMain() );

        mworld_assetmain->Load(*this);

        __CATCH__

    } // Setup

    void MWorld::Release()
    {
        //

    } // Release

    MWorld::MWorld():
    worlddata()
    {}

    MWorld::MWorld(MWorld&)
    {}

    MWorld::~MWorld()
    {
        Release();

    } // ~MWorld

} // namespace endless
