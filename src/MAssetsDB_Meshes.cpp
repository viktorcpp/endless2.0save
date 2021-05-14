
namespace endless
{
    //MAssetsDB_Meshes

    void MAssetsDB_Meshes::Load( MAssetsDB& parent )
    {
        MScripts* ms = MCore::GetMScripts();
        std::stringstream buffer;
        MUtils::FileLoadBuffer( (CFG.datapath + parent.def_path_mesh_data).c_str(), buffer );
        duk_context* context = duk_create_heap(nullptr, nullptr, nullptr, nullptr, MScripts::duk_fatal_handle );
        ms->DoString( context, buffer.str().c_str() );
        long arr_size = (long)duk_get_length(context, -1);
        for( long x = 0; x < arr_size; ++x )
        {
            MMesh::AssetInfoMesh data;

            duk_get_prop_index(context, -1, x);

                ms->GetPropString( context, "id",          data.id );
                ms->GetPropString( context, "path_mesh",   data.path_mesh );
                ms->GetPropString( context, "rigid_id",    data.rigid_id );
                ms->GetPropString( context, "material_id", data.material_id );

            duk_pop(context); //duk_get_prop_index

            parent.assetmeshdata[data.id] = data;

        } // for

        buffer.str("");
        buffer.clear();

        duk_destroy_heap(context);

    } // LoadData

    MAssetsDB_Meshes::MAssetsDB_Meshes()
    {}

    MAssetsDB_Meshes::MAssetsDB_Meshes(MAssetsDB_Meshes&)
    {}

    MAssetsDB_Meshes::~MAssetsDB_Meshes()
    {}

} // namespace endless
