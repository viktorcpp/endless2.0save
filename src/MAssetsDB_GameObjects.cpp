
namespace endless
{
    void MAssetsDB_GameObjects::Load( MAssetsDB& parent )
    {
        MScripts* ms = MCore::GetMScripts();
        std::stringstream buffer;
        MUtils::FileLoadBuffer( (CFG.datapath + parent.def_path_gameobject_data).c_str(), buffer );
        duk_context* context = duk_create_heap(nullptr, nullptr, nullptr, nullptr, MScripts::duk_fatal_handle );
        ms->DoString( context, buffer.str().c_str() );
        long arr_size = (long)duk_get_length(context, -1);
        for( long x = 0; x < arr_size; ++x )
        {
            MGameObject::AssetInfoGO data;

            duk_get_prop_index(context, -1, x);

                ms->GetPropString( context, "id",      data.id );
                ms->GetPropString( context, "mesh_id", data.mesh_id );
                ms->GetPropString( context, "mat_id",  data.mat_id );
                ms->GetPropString( context, "rb_id",   data.rb_id );

                duk_get_prop_string(context, -1, "position");
                    duk_get_prop_index(context, -1, 0);
                        data.position.x = (float)duk_get_number(context, -1);
                    duk_pop(context); //duk_get_prop_index

                    duk_get_prop_index(context, -1, 1);
                        data.position.y = (float)duk_get_number(context, -1);
                    duk_pop(context); //duk_get_prop_index

                    duk_get_prop_index(context, -1, 2);
                        data.position.z = (float)duk_get_number(context, -1);
                    duk_pop(context); //duk_get_prop_index
                duk_pop(context); //duk_get_prop_string

                duk_get_prop_string(context, -1, "rotation");
                    duk_get_prop_index(context, -1, 0);
                        data.rotation.x = (float)duk_get_number(context, -1);
                    duk_pop(context); //duk_get_prop_index

                    duk_get_prop_index(context, -1, 1);
                        data.rotation.y = (float)duk_get_number(context, -1);
                    duk_pop(context); //duk_get_prop_index

                    duk_get_prop_index(context, -1, 2);
                        data.rotation.z = (float)duk_get_number(context, -1);
                    duk_pop(context); //duk_get_prop_index
                duk_pop(context); //duk_get_prop_string

            duk_pop(context); //duk_get_prop_index

            parent.assetgodata[data.id] = data;

        } // for

        buffer.str("");
        buffer.clear();

        duk_destroy_heap(context);

    } // LoadData

    MAssetsDB_GameObjects::MAssetsDB_GameObjects()
    {}

    MAssetsDB_GameObjects::MAssetsDB_GameObjects(MAssetsDB_GameObjects&)
    {}

    MAssetsDB_GameObjects::~MAssetsDB_GameObjects()
    {}

} // namespace endless
