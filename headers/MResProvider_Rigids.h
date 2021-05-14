#pragma once

namespace endless
{
    class MResProvider_Rigids
    {
    public:

        void LoadAssetBin( MRigidBody** mrb, const char* path );
        void LoadAssetXml( MRigidBody** mrb, const char* path );
        void Extract( MRigidBody** mrb, PxCollection* coll );

        MResProvider_Rigids();
        virtual ~MResProvider_Rigids();

    private:

        MResProvider_Rigids(MResProvider_Rigids&);

    }; // class MResProvider_Rigids

} // namespace endless
