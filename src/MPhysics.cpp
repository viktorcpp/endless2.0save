
namespace endless
{
    void MPhysics::Update()
    {
        __TRY__

        if( pxscene_world != 0 && !MCORE->IsPaused() )
        {
            float deltat = (float)MCore::GetMTimer()->DeltaTime()*0.000001f;
            pxscene_world->simulate( deltat );
            pxscene_world->fetchResults(true);
        }

        __CATCH__

    } // Update

    void MPhysics::AddCollection( PxCollection* col )
    {
        PxSceneWriteLock scoped_lock( *pxscene_world );
        pxscene_world->addCollection( *col );

    } // AddCollection

    void MPhysics::AddRigid( PxActor* rb )
    {
        PxSceneWriteLock scoped_lock( *pxscene_world );
        pxscene_world->addActor(*rb);

    } // AddRigid

    void MPhysics::Setup()
    {
        __TRY__

        LOGN("%s: init:\n", __FUNCTION__);
        
        pxmem_allocator = new MPhysicsMemAllocator();
        pxmerror_report = new MPhysicsErrorReport();

        CreateFoundation();
        CreateVisualDebugger();
        CreatePhysics();
        CreateExtensions();
        CreateCooking();
        CreateCPUDispatcher();
        CreateSerialization();
        CreateSceneWorld();
        CreateVisualization();

        TestScene();
        
        LOGN("%s: ready\n\n", __FUNCTION__);

        __CATCH__

    } // Setup()

    void MPhysics::TestScene()
    {
        PxSceneWriteLock scoped_lock( *pxscene_world );

        PxTransform     dyn_sphere_pos( PxVec3(0.f, 30.0f, 0.f) );
        PxMaterial*     dyn_sphere_mat   = pxphysics->createMaterial(0.01f, 0.01f, 0.01f);
        PxRigidDynamic* dyn_sphere_rb    = pxphysics->createRigidDynamic( dyn_sphere_pos );
        PxShape*        dyn_sphere_shape = PxRigidActorExt::createExclusiveShape( *dyn_sphere_rb, PxSphereGeometry(1.0f), *pxmaterial_default );
        dyn_sphere_rb->setMass(1000.0f);

        PxTransform     dyn_sphere_pos2( PxVec3(1.f, 60.0f, 0.f) );
        PxMaterial*     dyn_sphere_mat2   = pxphysics->createMaterial(0.01f, 0.01f, 0.01f);
        PxRigidDynamic* dyn_sphere_rb2    = pxphysics->createRigidDynamic( dyn_sphere_pos2 );
        PxShape*        dyn_sphere_shape2 = PxRigidActorExt::createExclusiveShape( *dyn_sphere_rb2, PxSphereGeometry(5.0f), *pxmaterial_default );
        dyn_sphere_rb2->setMass(1000.0f);
        //dyn->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
        //sphere->setLocalPose(PxTransform( PxVec3(0.f, 20.0f, 0.f) ));
        //dyn->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
        //dyn->setAngularVelocity(PxVec3(0.f, 0.f, 0.f));
        //dyn->setAngularDamping(0.f);

        PxTransform    stat_plane_pos( PxVec3(0.f, -0.1f, 0.f) );
        PxMaterial*    stat_plane_mat   = pxphysics->createMaterial(0.01f, 0.01f, 0.01f);
        PxRigidStatic* stat_plane       = pxphysics->createRigidStatic( stat_plane_pos );
        PxShape*       stat_shape_plane = PxRigidActorExt::createExclusiveShape( *stat_plane, PxBoxGeometry(5.0f, 0.1f, 5.0f), *stat_plane_mat );

        pxscene_world->addActor( *dyn_sphere_rb );
        pxscene_world->addActor( *dyn_sphere_rb2 );
        //pxscene_world->addActor( *stat_plane );

    } // TestScene

    void MPhysics::CreateVisualDebugger()
    {
#ifdef _DEBUG
        pxpvdtransport = PxDefaultPvdSocketTransportCreate( "localhost", 5425, 1000 );
        if( pxpvdtransport == 0 )
        {
            throw std::exception("PhysX: PxDefaultPvdSocketTransportCreate FAILED\n");
        }
        pxpvd = PxCreatePvd( *pxfoundation );
        pxpvd->connect( *pxpvdtransport, PxPvdInstrumentationFlag::eALL );
#endif

    } // CreateVisualDebugger

    void MPhysics::CreateFoundation()
    {
        pxfoundation = PxCreateFoundation( PX_FOUNDATION_VERSION, *pxmem_allocator, *pxmerror_report );
        if( pxfoundation == 0 )
        {
            throw std::exception("PhysX: PxCreateFoundation FAILED\n");
        }

    } // CreateFoundation

    void MPhysics::CreatePhysics()
    {
        __TRY__

        pxphysics = PxCreatePhysics( PX_PHYSICS_VERSION, *pxfoundation, pxtolerancescale, true, pxpvd );
        if( pxphysics == 0 )
        {
            throw std::exception("PhysX: PxCreatePhysics FAILED\n");
        }

        pxmaterial_default = pxphysics->createMaterial(0.01f, 0.01f, 0.01f);
        if( pxmaterial_default == 0 )
        {
            throw std::exception("PhysX: createMaterial FAILED\n");
        }

        __CATCH__

    } // CreatePhysics

    void MPhysics::CreateExtensions()
    {
        __TRY__

        if( !PxInitExtensions( *pxphysics, pxpvd ) )
        {
            throw std::exception("PhysX: PxInitExtensions FAILED\n");
        }

        __CATCH__

    } // CreateExtensions

    void MPhysics::CreateCooking()
    {
        __TRY__

        pxcooking = PxCreateCooking( PX_PHYSICS_VERSION, *pxfoundation, PxCookingParams(pxtolerancescale) );
        if( pxcooking == 0 )
        {
            throw std::exception("PhysX: PxCreateCooking FAILED\n");
            return;
        }

        __CATCH__

    } // CreateCooking

    void MPhysics::CreateCPUDispatcher()
    {
        __TRY__

        pxdefaultcpudispatcher = PxDefaultCpuDispatcherCreate(1);
        if( pxdefaultcpudispatcher == 0 )
        {
            throw std::exception("PhysX: PxDefaultCpuDispatcherCreate FAILED\n");
        }

        __CATCH__

    } // CreateCPUDispatcher

    void MPhysics::CreateSerialization()
    {
        __TRY__

        pxserializationregistry = PxSerialization::createSerializationRegistry( *pxphysics );
        if( pxserializationregistry == 0 )
        {
            throw std::exception("PhysX: PxSerialization::createSerializationRegistry FAILED\n");
        }

        __CATCH__

    } // CreateSerialization

    void MPhysics::CreateSceneWorld()
    {
        __TRY__

        PxSceneDesc pxscenedesc( pxphysics->getTolerancesScale() );
        pxscenedesc.gravity       = PxVec3( CFG.phy_gravity.x, CFG.phy_gravity.y, CFG.phy_gravity.z );
        pxscenedesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
        pxscenedesc.filterShader  = FilterShader;
        pxscenedesc.flags        |= PxSceneFlag::eENABLE_PCM;
        pxscenedesc.flags        |= PxSceneFlag::eENABLE_CCD;
	    pxscenedesc.flags        |= PxSceneFlag::eENABLE_STABILIZATION; // test feature

        pxscene_world = pxphysics->createScene( pxscenedesc );
        if( pxscene_world == 0 )
        {
            throw std::exception("PhysX: PxPhysics::createScene FAILED\n");
        }

        __CATCH__

    } // CreateSceneWorld

    void MPhysics::CreateVisualization()
    {
#ifdef _DEBUG
        
        __TRY__

        PxSceneWriteLock scoped_lock( *pxscene_world );

        pxscene_world->setVisualizationParameter( PxVisualizationParameter::eACTOR_AXES, 2.0f );

        PxPvdSceneClient* pxpvd_client = pxscene_world->getScenePvdClient();
	    if( pxpvd_client != 0 )
	    {
		    pxpvd_client->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS,  true);
		    pxpvd_client->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS,     true);
		    pxpvd_client->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	    }

        __CATCH__
#endif
    } // CreateVisualization

    MPhysics::MPhysics():
        pxmerror_report(nullptr),
        pxmem_allocator(nullptr),
        pxtolerancescale(),
        pxmaterial_default(nullptr),
        pxfoundation(nullptr),
        pxphysics(nullptr),
        pxpvd(nullptr),
        pxpvdtransport(nullptr),
        pxcooking(nullptr),
        pxscene_world(nullptr),
        pxserializationregistry(nullptr),
        pxdefaultcpudispatcher(nullptr)
    {}

    MPhysics::~MPhysics()
    {
        __release(pxphysics);
        __release(pxfoundation);
        __deletea(pxmem_allocator);
        __deletea(pxmerror_report);

    } // ~MPhysics

    template<> MPhysics* Singleton<MPhysics>::_instance = 0;

} // namespace endless
