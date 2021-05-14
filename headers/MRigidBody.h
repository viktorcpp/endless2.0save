#pragma once

namespace endless
{
    class MRigidBody
    {
    public:

        struct AssetInfoRigids
        {
            std::string id   = "";
            std::string path = "";

        }; // struct AssetInfoRigids

        std::vector<PxActor*>& Rigid( PxActor* newrigid = nullptr );

        MRigidBody();
        virtual ~MRigidBody();

    private:

        std::vector<PxActor*> rigid;

        MRigidBody(MRigidBody&);

    }; // class MRigidBody

} // namespace endless
