
namespace endless
{
    std::vector<PxActor*>& MRigidBody::Rigid( PxActor* newrigid )
    {
        if( newrigid != nullptr )
            rigid.push_back(newrigid);

        return rigid;

    } // Rigid

    MRigidBody::MRigidBody():
        rigid()
    {}

    MRigidBody::~MRigidBody()
    {}

} // namespace endless
