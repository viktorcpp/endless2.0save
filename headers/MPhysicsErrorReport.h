#pragma once

namespace endless
{
    class MPhysicsErrorReport : public PxErrorCallback
    {

    public:

        void reportError( PxErrorCode::Enum code, const char* message, const char* file, int line );

        MPhysicsErrorReport();
        virtual ~MPhysicsErrorReport();

    private:

        MPhysicsErrorReport(MPhysicsErrorReport&);

    }; // class MPhysicsErrorReport

} // namespace endless
