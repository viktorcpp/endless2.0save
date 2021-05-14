
namespace endless
{
    void MWorld_AssetMain::Load(MWorld& mworld) throw(std::exception)
    {
        __TRY__

        std::string filepath = CFG.datapath + mworld.world_asset_path + mworld.asset_main;
        if( !MUtils::FileExists( filepath.c_str() ) )
        {
            std::string error = MUtils::string_format( "%s : can't load <%s>\n", __FUNCTION__, filepath.c_str() );
            throw std::exception( error.c_str() );
        }

        std::stringstream buffer;
        MUtils::FileLoadBuffer( filepath.c_str(), buffer );
        duk_context* context = duk_create_heap( nullptr, nullptr, nullptr, nullptr, MScripts::duk_fatal_handle );
        duk_eval_string( context, buffer.str().c_str() );

        long regions_count = (long)duk_get_length(context, -1);
        for( long x = 0; x < regions_count; ++x )
        {
            MWorld::WorldData::Region region;
            duk_get_prop_index(context, -1, x);

                duk_get_prop_string(context, -1, "id");
                    region.id = duk_to_string(context, -1);
                duk_pop(context); // duk_get_prop_string

                duk_get_prop_string(context, -1, "cells");
                    long cells_count = (long)duk_get_length(context, -1);
                    for( long y = 0; y < cells_count; ++y )
                    {
                        MWorld::WorldData::Cell cell;
                        duk_get_prop_index(context, -1, y);

                            duk_get_prop_string(context, -1, "id");
                                cell.id = duk_to_string(context, -1);
                            duk_pop(context); // duk_get_prop_string

                            duk_get_prop_string(context, -1, "placed");
                                long placed_count = (long)duk_get_length(context, -1);
                                for( long z = 0; z < placed_count; ++z )
                                {
                                    MWorld::WorldData::Placed placed;
                                    duk_get_prop_index(context, -1, z);
                                        duk_get_prop_string(context, -1, "id");
                                            placed.id = duk_to_string(context, -1);
                                        duk_pop(context); // duk_get_prop_string
                                        duk_get_prop_string(context, -1, "position");
                                            duk_get_prop_index(context, -1, 0);
                                                placed.position.x = (float)duk_to_number(context, -1);
                                            duk_pop(context); // duk_get_prop_string
                                            duk_get_prop_index(context, -1, 1);
                                                placed.position.y = (float)duk_to_number(context, -1);
                                            duk_pop(context); // duk_get_prop_string
                                            duk_get_prop_index(context, -1, 2);
                                                placed.position.z = (float)duk_to_number(context, -1);
                                            duk_pop(context); // duk_get_prop_string
                                        duk_pop(context); // duk_get_prop_string
                                    duk_pop(context); // duk_get_prop_index

                                    cell.placed[placed.id] = placed;

                                } // for
                            duk_pop(context); // duk_get_prop_string

                        duk_pop(context); // duk_get_prop_index

                        region.cells[cell.id] = cell;

                    } // for
                duk_pop(context); // duk_get_prop_string

            duk_pop(context); // duk_get_prop_index

            mworld.worlddata.regions[region.id] = region;

        } // for

        duk_destroy_heap(context);

        buffer.str("");
        buffer.clear();

        __CATCH__

    } // Load

    MWorld_AssetMain::MWorld_AssetMain()
    {}

    MWorld_AssetMain::MWorld_AssetMain(MWorld_AssetMain&)
    {}

    MWorld_AssetMain::~MWorld_AssetMain()
    {}

} // namespace endless
