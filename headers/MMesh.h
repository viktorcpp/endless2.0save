#pragma once

namespace endless
{
    class MMesh
    {
    public:

        struct AssetInfoMesh
        {
            std::string id          = "";
            std::string path_mesh   = "";
            std::string rigid_id    = "";
            std::string material_id = "";

        }; // struct AssetInfoMesh

        MTransform& Transform(){ return transform; }
        MTransform& Transform( MTransform& tr );

        MTexture* GetTexture(){ return texture; }
        void      SetTexture( MTexture* texture );

        std::vector<MMESH_SUBSET>& GetSubset(){ return mesh_subsets; }
        void AddSubset( MMESH_SUBSET subset );

        MGameObject& GameObject(){ return *gameobject; }

        void Draw();

        MMesh();
        virtual ~MMesh();

    private:

        MGameObject*              gameobject   = nullptr;
        MTransform                transform    = {};
        MTexture*                 texture      = nullptr;
        ID3D11DeviceContext*      context      = nullptr;
        std::vector<MMESH_SUBSET> mesh_subsets = {};

    }; // class MMesh

} // namespace endless
