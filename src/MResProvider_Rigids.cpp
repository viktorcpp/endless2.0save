
namespace endless
{
    //MResProvider_Rigids
    void MResProvider_Rigids::LoadAssetBin( MRigidBody** mrb, const char* path )
    {
        std::ifstream file( path, std::ios::binary );
        unsigned long filesize  = MUtils::FileSize( file );
        void*         memory    = new char[filesize + PX_SERIAL_FILE_ALIGN];
        void*         memory128 = (void*)((size_t(memory) + PX_SERIAL_FILE_ALIGN)&~(PX_SERIAL_FILE_ALIGN-1));
        file.read((char*)memory128, filesize);
        file.close();
            
        PxCollection* collection     = PxSerialization::createCollectionFromBinary( memory128, *MCore::GetMPhysics()->GetSerReg() );
        PxMaterial*   collection_mat = MCore::GetMPhysics()->GetPhy()->createMaterial(0.01f, 0.01f, 0.01f);
        collection->add( *collection_mat, 1 );
        PxSerialization::complete( *collection, *MCore::GetMPhysics()->GetSerReg() );

        Extract( mrb, collection );

        collection->release();

    } // LoadPhysicsAssetBin

    void MResProvider_Rigids::LoadAssetXml( MRigidBody** mrb, const char* path )
    {
        PxSerializationRegistry* pxserreg   = MCore::GetMPhysics()->GetSerReg();
        PxCooking*               pxcooking  = MCore::GetMPhysics()->GetCooking();
        PxCollection*            collection = nullptr;
        PxDefaultFileInputData input_data( path );

        if( input_data.isValid() )
        {
            collection = PxSerialization::createCollectionFromXml( input_data, *pxcooking, *pxserreg );
            if( collection == 0 )
            {
                LOGE( "PhysX: PxSerialization::createCollectionFromXml FAILED\n" );
            }
            PxSerialization::complete( *collection, *pxserreg );
        }
        else
        {
            LOGE( "PhysX: LoadAssetXml file not found '%s'\n", path );
        }

        Extract( mrb, collection );

        collection->release();
            
    } // LoadAssetXml

    void MResProvider_Rigids::Extract( MRigidBody** mrb, PxCollection* coll )
    {
        *mrb = new MRigidBody();

        long size = coll->getNbObjects();
        for( long i = 0; i < size; i++ )
        {
            PxBase&  baseo   = coll->getObject(i);
            PxActor* pxactor = baseo.is<PxActor>();
            if( pxactor != nullptr )
            {
                PxType ptype = pxactor->getConcreteType();
                if( ptype == PxConcreteType::eRIGID_DYNAMIC || ptype == PxConcreteType::eRIGID_STATIC )
                {
                    (*mrb)->Rigid( pxactor->is<PxActor>() );
                }
            }

        } // for

    } // Extract

    MResProvider_Rigids::MResProvider_Rigids()
    {}

    MResProvider_Rigids::MResProvider_Rigids(MResProvider_Rigids&)
    {}

    MResProvider_Rigids::~MResProvider_Rigids()
    {}

} // namespace endless
