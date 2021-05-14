
namespace endless
{
    void MPhysicsErrorReport::reportError( PxErrorCode::Enum code, const char* message, const char* file, int line )
    {
        LOGE( "PhysX: [%d] %s\nFile: %s\nLine: %d\n", (long)code, message, file, line );

    } // MPhysicsErrorReport::OnError

    MPhysicsErrorReport::MPhysicsErrorReport()
    {}

    MPhysicsErrorReport::MPhysicsErrorReport(MPhysicsErrorReport&)
    {}

    MPhysicsErrorReport::~MPhysicsErrorReport()
    {}

} // namespace endless
