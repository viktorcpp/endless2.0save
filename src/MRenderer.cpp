
namespace endless
{
    ID3D11RasterizerState* rs_state = nullptr;

    bool MRenderer::Update()
    {
        __TRY__

        BOOL sciter_render = FALSE;

        d3dcontext->ClearRenderTargetView( rendertargetview, Colors::MidnightBlue );
        d3dcontext->ClearDepthStencilView( depth_view, D3D11_CLEAR_DEPTH, 1.0f, 0 );

        if( !MCORE->IsPausedHUD() )
        {
            cameras[0]->Read();
            cameras[0]->Update();
        }

        WORLD_CONST_BUFFER cb;
	    cb.world      = XMMatrixTranspose( XMMatrixIdentity() );
	    cb.view       = XMMatrixTranspose( cameras[0]->GetMatView() );
	    cb.projection = XMMatrixTranspose( cameras[0]->GetMatProj() );
        cb.wvp        = XMMatrixTranspose( XMMatrixIdentity() * cb.view * cb.projection );

        d3dcontext->UpdateSubresource( buffer_constants, 0, nullptr, &cb, 0, 0 );
        d3dcontext->IASetInputLayout( main_shader_il );
        d3dcontext->VSSetShader( main_shader_vs, nullptr, 0 );
        d3dcontext->VSSetConstantBuffers( 0, 1, &buffer_constants );  
        d3dcontext->PSSetShader( main_shader_px,  nullptr, 0 );
        d3dcontext->PSSetSamplers( 0, 1, &id3d11samplerstate );
        
        // RENDER begin
        if( test_mesh )
        {
            test_mesh->Draw();
        }
        if( test_mesh2 )
        {
            test_mesh2->Draw();
        }

        MHud::Ref()->Frame();

        // fucking Crazy Eddy! stupid cunt
        d3dcontext->RSGetState(&rs_state);
        
        d3dcontext->RSSetState(rs_state);
        d3dcontext->OMSetDepthStencilState( depth_state, 1 );
        // RENDER end */
        
        std::this_thread::sleep_for( std::chrono::seconds(0) );
        swapchain->Present( 0, 0 );

        __CATCH__

        return true;

    } // Frame

    void MRenderer::Setup()
    {
        __TRY__

        LOGN("%s: init:\n", __FUNCTION__);

        std::string path_buffer = "";

        mdriver          = MCore::GetMRendererDriver();
        device           = mdriver->GetDevice();
        d3dcontext       = mdriver->GetContext();
        swapchain        = mdriver->GetSwapChain();
        rendertargetview = mdriver->GetRenderTargetView();
        depth_view       = mdriver->GetDSView();

        // Create the constant buffer
	    buffer_constants_desc.Usage          = D3D11_USAGE_DEFAULT;
	    buffer_constants_desc.ByteWidth      = sizeof(WORLD_CONST_BUFFER);
	    buffer_constants_desc.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
	    buffer_constants_desc.CPUAccessFlags = 0;
        HRESULT hr = device->CreateBuffer( &buffer_constants_desc, nullptr, &buffer_constants );
        if( FAILED( hr ) )
        {
            LOGE( "MRenderer: ID3D11Device::CreateBuffer CONST FAILED\n" );
        }
        
        // VERTEX shader
        ID3DBlob* shader_vs_blob = nullptr;
        main_shader_vs = MCore::GetMResProvider()->CreateShaderVertex( "render-main.fx", &shader_vs_blob );

        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        UINT numElements = ARRAYSIZE( layout );

        hr = device->CreateInputLayout( layout, numElements, shader_vs_blob->GetBufferPointer(), shader_vs_blob->GetBufferSize(), &main_shader_il );
	    shader_vs_blob->Release();
	    if( FAILED( hr ) )
        {
            LOGE("MRenderer::Setup: CreateInputLayout VS FAILED\n");
            return;
        }
        d3dcontext->IASetInputLayout( main_shader_il );

        // PIXEL shader
        main_shader_px = MCore::GetMResProvider()->CreateShaderPixel( "render-main.fx" );

        // Create the sample state
        D3D11_SAMPLER_DESC sampler_desc;
        ZeroMemory( &sampler_desc, sizeof(sampler_desc) );
        sampler_desc.Filter         = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sampler_desc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
        sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        sampler_desc.MinLOD         = 0;
        sampler_desc.MaxLOD         = D3D11_FLOAT32_MAX;
        hr = device->CreateSamplerState( &sampler_desc, &id3d11samplerstate );
        if( FAILED( hr ) )
        {
            LOGE( "MRenderer::Setup : CreateSamplerState FAILED\n" );
            return;
        }

        MCamera* camera_main = new MCamera();
        cameras.push_back(camera_main);

        LOGN( "%s: ready\n\n", __FUNCTION__ );

        __CATCH__

    } // Setup

    void MRenderer::OnResize(int w, int h)
    {
        mdriver          = MCore::GetMRendererDriver();
        device           = mdriver->GetDevice();
        d3dcontext       = mdriver->GetContext();
        swapchain        = mdriver->GetSwapChain();
        rendertargetview = mdriver->GetRenderTargetView();
        depth_view       = mdriver->GetDSView();

    } // OnResize

    MRenderer::MRenderer():
        cameras(),
        hr(S_OK),
        mdriver(nullptr),
        device(nullptr),
        d3dcontext(nullptr),
        swapchain(nullptr),
        rendertargetview(nullptr),
        buffer_constants_desc(),
        buffer_constants_data(),
        buffer_constants(nullptr),
        main_shader_vs(nullptr),
        main_shader_px(nullptr),
        main_shader_il(nullptr),
        id3d11samplerstate(nullptr),
        depth_tex(nullptr),
        depth_view(nullptr),
        depth_state(nullptr)
    {}

    MRenderer::MRenderer(MRenderer&)
    {}

    MRenderer::~MRenderer(){}

    template<> MRenderer* Singleton<MRenderer>::_instance  = 0;

} // endless
