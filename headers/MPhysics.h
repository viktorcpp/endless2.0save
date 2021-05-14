#pragma once

#include <MPhysicsErrorReport.h>
#include <MPhysicsMemAllocator.h>

namespace endless
{
    class MPhysics : public Singleton<MPhysics>
    {
    public:

        void Update() throw(std::exception);

        PxSerializationRegistry* GetSerReg() { return pxserializationregistry; }
        PxPhysics*               GetPhy()    { return pxphysics; }
        PxCooking*               GetCooking(){ return pxcooking; }

        void AddCollection( PxCollection* col );
        void AddRigid     ( PxActor* rb );

        void Setup() throw(std::exception);
        
        MPhysics();
        virtual ~MPhysics();

    private:

        void TestScene();

        void CreateVisualDebugger() throw(std::exception);
        void CreateFoundation()     throw(std::exception);
        void CreatePhysics()        throw(std::exception);
        void CreateExtensions()     throw(std::exception);
        void CreateCooking()        throw(std::exception);
        void CreateCPUDispatcher()  throw(std::exception);
        void CreateSerialization()  throw(std::exception);
        void CreateSceneWorld()     throw(std::exception);
        void CreateVisualization()  throw(std::exception);

        MPhysicsErrorReport*     pxmerror_report         = 0;
        MPhysicsMemAllocator*    pxmem_allocator         = 0;
        PxTolerancesScale        pxtolerancescale        = {};
        PxMaterial*              pxmaterial_default      = 0;
        PxFoundation*            pxfoundation            = 0;
        PxPhysics*               pxphysics               = 0;
        PxPvd*                   pxpvd                   = 0;
        PxPvdTransport*          pxpvdtransport          = 0;
        PxCooking*               pxcooking               = 0;
        PxScene*                 pxscene_world           = 0;
        PxSerializationRegistry* pxserializationregistry = 0;
        PxDefaultCpuDispatcher*  pxdefaultcpudispatcher  = 0;

    }; // class MPhysics

} // namespace endless
