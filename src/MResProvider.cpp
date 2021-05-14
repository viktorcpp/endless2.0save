
namespace endless
{
    MGameObject* MResProvider::LoadGameObject( const char* id )
    {
        MGameObject* go = nullptr;
        //MGameObject::GameObject goinfo = MASSETSDB->

        return go;

    } // LoadGameObject

    MMesh* MResProvider::LoadMesh( const char* id )
    {
        __TRY__

        MMesh*               mesh      = nullptr;
        MMesh::AssetInfoMesh mesh_info = MCore::GetMAssetsDB()->GetMesh(id);
        std::string          fullpath  = CFG.datapath + mesh_info.path_mesh;
        std::ifstream        file;
        
        file.open(fullpath);
        if( !file )
        {
            LOGE("%s : error loading <%s> at <%s> \n", __FUNCTION__, id, fullpath.c_str());
            file.close();
            return nullptr;
        }
        file.close();

        if( fullpath.find(".obj", 0) != std::string::npos )
        {
            std::unique_ptr<MResProvider_MeshObj> mresprov_meshobj( new MResProvider_MeshObj() );
            mesh = mresprov_meshobj->Load(fullpath.c_str());
        }
        if( fullpath.find(".gltf", 0) != std::string::npos )
        {
            std::unique_ptr<MResProvider_MeshGLTF> mresprov_meshgltf( new MResProvider_MeshGLTF() );
            mesh = mresprov_meshgltf->Load(fullpath.c_str());
        }
        
        return mesh;

        __CATCH__

    } // LoadMesh

    MMaterial* MResProvider::LoadMaterial( const char* id )
    {
        MMaterial* material = nullptr;
        const MMaterial::AssetInfoMaterial& assetinfomaterial = MCore::GetMAssetsDB()->GetMat(id);

        return new MMaterial(assetinfomaterial);

    } // LoadMaterial

    void MResProvider::LoadTexture( MTexture** tex, const char* id )
    {
        *tex = LoadTexture( id );

    } // LoadTexture

    MTexture* MResProvider::LoadTexture( const char* id )
    {
        __TRY__

        MTexture*                        texture  = nullptr;
        const MTexture::AssetInfoTexture tex_info = MCore::GetMAssetsDB()->GetTex( id );
        MTexture::TextureInternalData    tex_data = {};
        std::unique_ptr<MResProvider_Textures> mresprov_textures( new MResProvider_Textures() );
        
        std::string   fullpath;
        std::ifstream file;

        // diffuse
        fullpath = CFG.datapath + tex_info.path_diffuse;
        file.open(fullpath);
        if( !file )
        {
            LOGE("%s : error loading <%s> at <%s> \n", __FUNCTION__, id, fullpath.c_str());
            fullpath = CFG.datapath + "textures/null.dds";
        }
        file.close();
        mresprov_textures->Load( tex_data.diffuse, fullpath.c_str() );

        //normal
        fullpath = CFG.datapath + tex_info.path_normals;
        file.open(fullpath);
        if( !file )
        {
            LOGE("%s : error loading <%s> at <%s> \n", __FUNCTION__, id, fullpath.c_str());
            fullpath = CFG.datapath + "textures/null.dds";
        }
        file.close();
        mresprov_textures->Load( tex_data.normal, fullpath.c_str() );

        //normal
        fullpath = CFG.datapath + tex_info.path_specular;
        file.open(fullpath);
        if( !file )
        {
            LOGE("%s : error loading <%s> at <%s> \n", __FUNCTION__, id, fullpath.c_str());
            fullpath = CFG.datapath + "textures/null.dds";
        }
        file.close();
        mresprov_textures->Load( tex_data.specular, fullpath.c_str() );

        texture  = new MTexture(tex_data);

        return texture;

        __CATCH__

    } // LoadTexture

    MRigidBody* MResProvider::LoadRigid( const char* id )
    {
        __TRY__

        MRigidBody*                 mrb        = nullptr;
        MRigidBody::AssetInfoRigids rigid_info = MCore::GetMAssetsDB()->GetRid(id);
        std::string                 fullpath   = CFG.datapath + rigid_info.path;
        std::ifstream               file;

        file.open(fullpath);
        if( !file )
        {
            LOGE("%s : error loading <%s> at <%s> \n", __FUNCTION__, id, fullpath.c_str());
            file.close();
            return nullptr;
        }
        file.close();

        std::unique_ptr<MResProvider_Rigids> mresprovr_rigids( new MResProvider_Rigids() );
        if( fullpath.find(".phybin") != std::string::npos )
        {
            mresprovr_rigids->LoadAssetBin( &mrb, fullpath.c_str() );
        }
        else if( fullpath.find(".xml") != std::string::npos )
        {
            mresprovr_rigids->LoadAssetXml( &mrb, fullpath.c_str() );
        }

        return mrb;

        __CATCH__

    } // LoadRigid

    ID3D11PixelShader* MResProvider::CreateShaderPixel( const char* path, const char* entry )
    {
        HRESULT            hr;
        std::string        path_buffer    = CFG.datapath + path;
        ID3D11Device*      device         = const_cast<ID3D11Device*>( MCore::GetMRendererDriver()->GetDevice() );
        ID3DBlob*          shader_ps_blob = nullptr;
        ID3D11PixelShader* shader         = nullptr;

        hr = MUtils::CompileShaderFromFile( path_buffer.c_str(), entry, "ps_4_0", &shader_ps_blob );
        if( FAILED( hr ) )
        {
            LOGE( "%s : (CompileShaderFromFile) \"%s\" FAILED\n", __FUNCTION__, path_buffer.c_str() );
            return nullptr;
        }

        hr = device->CreatePixelShader( shader_ps_blob->GetBufferPointer(), shader_ps_blob->GetBufferSize(), nullptr, &shader );
	    shader_ps_blob->Release();
        if( FAILED( hr ) )
        {
            LOGE( "%s : (CreatePixelShader) \"%s\" FAILED\n", __FUNCTION__, path_buffer.c_str() );
            return nullptr;
        }

        return shader;

    } // CreatePixelShader

    ID3D11VertexShader* MResProvider::CreateShaderVertex( const char* path, ID3DBlob** vs_data, const char* entry )
    {
        HRESULT             hr;
        std::string         path_buffer    = CFG.datapath + path;
        ID3D11Device*       device         = const_cast<ID3D11Device*>( MCore::GetMRendererDriver()->GetDevice() );
        ID3DBlob*           shader_vs_blob = *vs_data;
        ID3D11VertexShader* shader         = nullptr;

        hr = MUtils::CompileShaderFromFile( path_buffer.c_str(), entry, "vs_4_0", &shader_vs_blob );
        if( FAILED( hr ) )
        {
            LOGE("MRenderer::Setup: MUtils::CompileShaderFromFile VS FAILED\n");
            return nullptr;
        }

        hr = device->CreateVertexShader( shader_vs_blob->GetBufferPointer(), shader_vs_blob->GetBufferSize(), nullptr, &shader );
	    if( FAILED( hr ) )
	    {
		    shader_vs_blob->Release();
            LOGE("MRenderer::Setup: CreateVertexShader VS FAILED\n");
            return nullptr;
	    }
        *vs_data = shader_vs_blob;

        return shader;

    } // CreateShaderVertex

    void MResProvider::Setup()
    {
        __TRY__

        LOGN( "%s init:\n", __FUNCTION__ );

        //

        LOGN( "%s ready\n\n", __FUNCTION__ );

        __CATCH__

    } // Setup

    MResProvider::MResProvider()
    {}

    MResProvider::MResProvider(MResProvider&)
    {}

    MResProvider::~MResProvider()
    {}

    template<> MResProvider* Singleton<MResProvider>::_instance = 0;

} // namespace endless
