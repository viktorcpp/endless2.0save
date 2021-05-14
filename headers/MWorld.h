#pragma once

#include <MRegion.h>
#include <MWorld_AssetMain.h>

namespace endless
{
    class MWorld
    {
    public:

        struct WorldData
        {
            struct Placed
            {
                std::string id       = "";
                XMFLOAT3    position = {0,0,0};
                XMFLOAT3    rotation = {0,0,0};

            }; // struct Placed

            struct Cell
            {
                std::string id = "";

                std::unordered_map<std::string, Placed> placed;
                
            }; // struct Cell

            struct Region
            {
                std::string id = "";

                std::unordered_map<std::string, Cell> cells;
                
            }; // struct Region

            std::unordered_map<std::string, Region> regions;

        }; // struct WorldData

        void Update() throw(std::exception);

        void Setup() throw(std::exception);
        void Release();

        MWorld();
        virtual ~MWorld();

    private:

        const std::string world_asset_path = "world/";
        const std::string asset_main       = "world.asset.js";
        WorldData         worlddata        = {};

        MWorld(MWorld&);

        friend class MCore;
        friend class MWorld_AssetMain;

    }; // class MWorld

} // namespace endless
