
namespace endless
{
    void MAssetsDB_Rigids::Load( MAssetsDB& parent )
    {
        MScripts* ms = MCore::GetMScripts();
        std::stringstream buffer;
        MUtils::FileLoadBuffer( (CFG.datapath + parent.def_path_rigids_data).c_str(), buffer );
        duk_context* context = duk_create_heap(nullptr, nullptr, nullptr, nullptr, MScripts::duk_fatal_handle );
        ms->DoString( context, buffer.str().c_str() );
        long arr_size = (long)duk_get_length(context, -1);
        for( long x = 0; x < arr_size; ++x )
        {
            MRigidBody::AssetInfoRigids data;

            duk_get_prop_index(context, -1, x);

                ms->GetPropString( context, "id",   data.id );
                ms->GetPropString( context, "path", data.path );

            duk_pop(context); //duk_get_prop_index

            parent.assetinforigids[data.id] = data;

        } // for

        buffer.str("");
        buffer.clear();

        duk_destroy_heap(context);

    } // Load

    MAssetsDB_Rigids::MAssetsDB_Rigids()
    {}

    MAssetsDB_Rigids::MAssetsDB_Rigids(MAssetsDB_Rigids&)
    {}

    MAssetsDB_Rigids::~MAssetsDB_Rigids()
    {}

} // namespace endless
