#pragma once

#include <MGLTFAssetLoader.h>
#include <MAssetsDB_Meshes.h>
#include <MAssetsDB_Textures.h>
#include <MAssetsDB_Materials.h>
#include <MAssetsDB_Rigids.h>
#include <MAssetsDB_GameObjects.h>

namespace endless
{

#define MASSETSDB MAssetsDB::Ref()

    class MAssetsDB : public Singleton<MAssetsDB>
    {
    public:

        const MMesh::AssetInfoMesh         GetMesh( const std::string id ){ return assetmeshdata[id]; }
        const MTexture::AssetInfoTexture   GetTex ( const std::string id ){ return assettexturedata[id]; }
        const MMaterial::AssetInfoMaterial GetMat ( const std::string id ){ return assetmaterialdata[id]; }
        const MRigidBody::AssetInfoRigids  GetRid ( const std::string id ){ return assetinforigids[id]; }

        void Setup() throw(std::exception);

        MAssetsDB();
        virtual ~MAssetsDB();

    private:

        const std::string def_path_gameobject_data = "assets.gameobjects.js";
        std::unordered_map<std::string, MGameObject::AssetInfoGO> assetgodata;

        const std::string def_path_mesh_data = "assets.meshes.js";
        std::unordered_map<std::string, MMesh::AssetInfoMesh> assetmeshdata;

        const std::string def_path_texture_data = "assets.textures.js";
        std::unordered_map<std::string, MTexture::AssetInfoTexture> assettexturedata;

        const std::string def_path_materials_data = "assets.materials.js";
        std::unordered_map<std::string, MMaterial::AssetInfoMaterial> assetmaterialdata;

        const std::string def_path_rigids_data = "assets.rigids.js";
        std::unordered_map<std::string, MRigidBody::AssetInfoRigids> assetinforigids;

        MAssetsDB(MAssetsDB&);

        friend class MAssetsDB_Meshes;
        friend class MAssetsDB_Textures;
        friend class MAssetsDB_Materials;
        friend class MAssetsDB_Rigids;
        friend class MAssetsDB_GameObjects;
    
    }; // class MAssetsDB

} // namespace endless
