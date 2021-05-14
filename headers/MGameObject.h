#pragma once

namespace endless
{
    class MGameObject : public MTransform
    {
    public:

        struct AssetInfoGO
        {
            std::string id       = "";
            std::string mesh_id  = "";
            std::string mat_id   = "";
            std::string rb_id    = "";
            XMFLOAT3    position = {0,0,0};
            XMFLOAT4    rotation = {0,0,0,1};
            
        }; // struct AssetInfoGO

        const char* Id       ( const char* newid     = nullptr );
        MMesh&      Mesh     ( MMesh*      mesh      = nullptr );
        MMaterial&  Material ( MMaterial*  material  = nullptr );
        MRigidBody& RigidBody( MRigidBody* rigidbody = nullptr );
        MTransform& Transform( MTransform* transform = nullptr );

        MGameObject();
        MGameObject(AssetInfoGO&);
        virtual ~MGameObject();

    private:

        std::string id         = "";
        MMesh*      mmesh      = nullptr;
        MRigidBody* mrigidbody = nullptr;
        MMaterial*  mmaterial  = nullptr;
        MTransform* mtransform = nullptr;

        MGameObject(MGameObject&);

    }; // class MGameObject

} // namespace endless
