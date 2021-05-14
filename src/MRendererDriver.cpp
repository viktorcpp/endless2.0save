
namespace endless
{
    void MRendererDriver::Setup()
    {
        __TRY__

        LOGN( "%s init:\n", __FUNCTION__ );

        std::string error                = "";
        HRESULT     hr                   = S_OK;
        HWND        hWnd                 = MCore::GetMWindow()->GetHandle();
        UINT        feature_levels_count = sizeof(feature_lvls) / sizeof(int);
        
        CreateDevice();
        CreateBackBuffer();
        CreateRenderTarget();
        CreateDepthStencilState();
        CreateDepthStencilView();
        
        context->OMSetRenderTargets( 1, &rendertargetview, depth_view );

        CreateViewport();

        depth_tex->Release();
        back_buffer->Release();

        GeneDisplayResolutions();

        LOGN( "%s ready\n\n", __FUNCTION__ );

        __CATCH__

    } // MRendererDriver::Create

    void MRendererDriver::Resize( int w, int h )
    {
        if( swapchain == nullptr ) return;

        __TRY__

        HRESULT hr    = S_OK;
        CFG.window_w = (FLOAT)w;
        CFG.window_h = (FLOAT)h;

        rendertargetview->Release();
        hr = swapchain->ResizeBuffers(2, w, h, DXGI_FORMAT_R8G8B8A8_UNORM, 0);
        if( FAILED(hr) )
        {
            std::string error;
            MUtils::TranslateLastError(error);
            error = MUtils::string_format( "%s : swapchain->ResizeBuffers FAILED\n    %s\n ", __FUNCTION__, error.c_str() );
            throw std::exception(error.c_str());
        }

        CreateBackBuffer();
        CreateRenderTarget();
        CreateDepthStencilState();
        CreateDepthStencilView();

        context->OMSetRenderTargets(1, &rendertargetview, depth_view );

        CreateViewport();
        
        MCore::GetMRenderer()->OnResize(w, h);
        MCore::GetMRenderer()->GetCameraMain()->OnResize(w, h);
        MCore::GetMWindow()->Resize(w, h);

        depth_tex->Release();
        back_buffer->Release();

        __CATCH__

    } // Resize

    void MRendererDriver::CreateDevice()
    {
        HRESULT     hr                   = S_OK;
        std::string error                = "";
        UINT        feature_levels_count = sizeof(feature_lvls) / sizeof(int);

        DXGI_SWAP_CHAIN_DESC dxgi_swap_chain_desc;
        ZeroMemory( &dxgi_swap_chain_desc, sizeof(DXGI_SWAP_CHAIN_DESC) );
        dxgi_swap_chain_desc.BufferCount                        = 1;
        dxgi_swap_chain_desc.BufferDesc.Width                   = (UINT)CFG.window_w;
        dxgi_swap_chain_desc.BufferDesc.Height                  = (UINT)CFG.window_h;
        dxgi_swap_chain_desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
        dxgi_swap_chain_desc.BufferDesc.RefreshRate.Numerator   = 60;
        dxgi_swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
        dxgi_swap_chain_desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        dxgi_swap_chain_desc.OutputWindow                       = MWINDOW->GetHandle();
        dxgi_swap_chain_desc.SampleDesc.Count                   = 1;
        dxgi_swap_chain_desc.SampleDesc.Quality                 = 0;
        dxgi_swap_chain_desc.Windowed                           = TRUE;

        // get current feature level profile
        hr = D3D11CreateDevice( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, &feature_lvls[0], feature_levels_count,
                                D3D11_SDK_VERSION, NULL, &feature_lvl_current, NULL );
        if(FAILED( hr ))
        {
            MUtils::TranslateLastError(error);
            error = MUtils::string_format( "%s : D3D11CreateDevice getting profile FAILED:\n    %s\n", __FUNCTION__, error.c_str() );
            throw std::exception(error.c_str());
        }
        // create with current profile
        hr = D3D11CreateDeviceAndSwapChain( nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, device_flags, &feature_lvls[0], feature_levels_count,
                                            D3D11_SDK_VERSION, &dxgi_swap_chain_desc, &swapchain, &device, &feature_lvl_current, &context );
        if( FAILED( hr ) )
        {
            MUtils::TranslateLastError(error);
            error = MUtils::string_format( "%s : D3D11CreateDeviceAndSwapChain FAILED:\n    %s\n", __FUNCTION__, error.c_str() );
            throw std::exception(error.c_str());
        }

    } // CreateDevice

    //Create our BackBuffer
    void MRendererDriver::CreateBackBuffer()
    {
        HRESULT     hr    = S_OK;
        std::string error = "";

        hr = swapchain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), (void**)&back_buffer );
        if( FAILED( hr ) )
        {
            MUtils::TranslateLastError(error);
            error = MUtils::string_format( "%s : swapchain->GetBuffer FAILED:\n    %s\n", __FUNCTION__, error.c_str() );
            throw std::exception(error.c_str());
        }

    } // CreateBackBuffer

    void MRendererDriver::CreateRenderTarget()
    {
        HRESULT     hr    = S_OK;
        std::string error = "";

        D3D11_TEXTURE2D_DESC d3d11_texture2d_desc;
	    ZeroMemory( &d3d11_texture2d_desc, sizeof(D3D11_TEXTURE2D_DESC) );
        d3d11_texture2d_desc.Width              = (UINT)CFG.window_w;
        d3d11_texture2d_desc.Height             = (UINT)CFG.window_h;
        d3d11_texture2d_desc.MipLevels          = 1;
        d3d11_texture2d_desc.ArraySize          = 1;
        d3d11_texture2d_desc.Format             = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
        d3d11_texture2d_desc.SampleDesc.Count   = 1;
        d3d11_texture2d_desc.SampleDesc.Quality = 0;
        d3d11_texture2d_desc.Usage              = D3D11_USAGE_DEFAULT;
        d3d11_texture2d_desc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
        d3d11_texture2d_desc.CPUAccessFlags     = 0;
        d3d11_texture2d_desc.MiscFlags          = 0;

        //Create our Render Target
        hr = device->CreateRenderTargetView( back_buffer, NULL, &rendertargetview );
        if( FAILED( hr ) )
        {
            LOGE("%s : CreateRenderTargetView FAILED\n", __FUNCTION__);
        }
        
        // Create depth stencil texture
        hr = device->CreateTexture2D( &d3d11_texture2d_desc, nullptr, &depth_tex );
        if( FAILED( hr ) )
        {
            LOGE("%s : CreateTexture2D FAILED\n", __FUNCTION__);
        }

    } // CreateRenderTarget

    void MRendererDriver::CreateDepthStencilState()
    {
        HRESULT     hr    = S_OK;
        std::string error = "";

        D3D11_DEPTH_STENCIL_DESC d3d11_depth_stencil_desc;
        ZeroMemory( &d3d11_depth_stencil_desc, sizeof(D3D11_DEPTH_STENCIL_DESC) );
        d3d11_depth_stencil_desc.DepthEnable                  = true;
        d3d11_depth_stencil_desc.DepthWriteMask               = D3D11_DEPTH_WRITE_MASK_ALL;
        d3d11_depth_stencil_desc.DepthFunc                    = D3D11_COMPARISON_LESS;
        d3d11_depth_stencil_desc.StencilEnable                = true;
        d3d11_depth_stencil_desc.StencilReadMask              = 0xFF;
        d3d11_depth_stencil_desc.StencilWriteMask             = 0xFF;
        d3d11_depth_stencil_desc.FrontFace.StencilFailOp      = D3D11_STENCIL_OP_KEEP;
        d3d11_depth_stencil_desc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
        d3d11_depth_stencil_desc.FrontFace.StencilPassOp      = D3D11_STENCIL_OP_KEEP;
        d3d11_depth_stencil_desc.FrontFace.StencilFunc        = D3D11_COMPARISON_ALWAYS;
        d3d11_depth_stencil_desc.BackFace.StencilFailOp       = D3D11_STENCIL_OP_KEEP;
        d3d11_depth_stencil_desc.BackFace.StencilDepthFailOp  = D3D11_STENCIL_OP_DECR;
        d3d11_depth_stencil_desc.BackFace.StencilPassOp       = D3D11_STENCIL_OP_KEEP;
        d3d11_depth_stencil_desc.BackFace.StencilFunc         = D3D11_COMPARISON_ALWAYS;

        hr = device->CreateDepthStencilState( &d3d11_depth_stencil_desc, &depth_state );
        if( FAILED(hr) )
        {
            LOGE("%s : CreateDepthStencilState FAILED\n", __FUNCTION__);
        }
        context->OMSetDepthStencilState( depth_state, 1 );

    } // CreateDepthStencilState

    void MRendererDriver::CreateDepthStencilView()
    {
        HRESULT     hr    = S_OK;
        std::string error = "";

        D3D11_DEPTH_STENCIL_VIEW_DESC stencilview_desc;
	    ZeroMemory( &stencilview_desc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC) );
        stencilview_desc.Format             = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
        stencilview_desc.ViewDimension      = D3D11_DSV_DIMENSION_TEXTURE2DMS;
        stencilview_desc.Texture2D.MipSlice = 0;

        hr = device->CreateDepthStencilView( depth_tex, &stencilview_desc, &depth_view );
        if( FAILED( hr ) )
        {
            LOGE("%s : CreateDepthStencilView FAILED\n", __FUNCTION__);
        }

    } // CreateDepthStencilView

    // Setup the viewport
    void MRendererDriver::CreateViewport()
    {
        D3D11_VIEWPORT d3d11_viewport;
        ZeroMemory( &d3d11_viewport, sizeof(D3D11_VIEWPORT) );
        d3d11_viewport.Width    = CFG.window_w;
        d3d11_viewport.Height   = CFG.window_h;
        d3d11_viewport.MinDepth = 0.0f;
        d3d11_viewport.MaxDepth = 1.0f;
        d3d11_viewport.TopLeftX = 0;
        d3d11_viewport.TopLeftY = 0;

        context->RSSetViewports( 1, &d3d11_viewport );

    } // CreateViewport

    void MRendererDriver::GeneDisplayResolutions()
    {
        HRESULT hr = S_OK;
        IDXGIDevice* device_dxgi = nullptr;
        hr = device->QueryInterface( __uuidof(IDXGIDevice), (void **)&device_dxgi );

        IDXGIAdapter* adapter_dxgi = nullptr;
        hr = device_dxgi->GetAdapter( &adapter_dxgi );

        IDXGIFactory * factory_dxgi = nullptr;
        adapter_dxgi->GetParent(__uuidof(IDXGIFactory), (void **)&factory_dxgi);

        UINT i = 0;
        IDXGIOutput* output_dxgi;
        std::vector<IDXGIOutput*> output_dxgi_list;
        while( adapter_dxgi->EnumOutputs( i, &output_dxgi ) != DXGI_ERROR_NOT_FOUND )
        {
            output_dxgi_list.push_back(output_dxgi);
            ++i;
        }

        UINT        num    = 0;
        DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM;
        UINT        flags  = DXGI_ENUM_MODES_INTERLACED;

        hr = output_dxgi_list[0]->GetDisplayModeList( format, flags, &num, 0);
        if(FAILED(hr))
        {
            std::string error;
            MUtils::TranslateLastError(error);
            LOGE( "%s : error GetDisplayModeList[1] : %s\n", __FUNCTION__, error.c_str() );
        }

        DXGI_MODE_DESC* pDescs = new DXGI_MODE_DESC[num];
        output_dxgi_list[0]->GetDisplayModeList( format, flags, &num, pDescs );
        if(FAILED(hr))
        {
            std::string error;
            MUtils::TranslateLastError(error);
            LOGE( "%s : error GetDisplayModeList[2] : %s\n", __FUNCTION__, error.c_str() );
        }

        for( ulong x = 0; x < num; x++ )
        {
            DXGI_MODE_DESC&   pdesc = pDescs[x];
            std::string       id    = MUtils::string_format( "%dx%d", pdesc.Width, pdesc.Height );
            DisplayResolution dr    = {};
            dr.w                    = pdesc.Width;
            dr.h                    = pdesc.Height;
            displayresolutions[id]  = dr;
        }

        //displayresolutions.sort()
        //std::sort( displayresolutions.begin(), displayresolutions.end() );

    } // GeneDisplayResolutions

    MRendererDriver::MRendererDriver():
        device_flags(0),
        feature_lvl_current(D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0),
        device(nullptr),
        context(nullptr),
        swapchain(nullptr),
        rendertargetview(nullptr),
        depth_view(nullptr),
        depth_state(nullptr)
    {
#ifdef _DEBUG
        device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
        device_flags |= D3D10_CREATE_DEVICE_BGRA_SUPPORT;
    }

    MRendererDriver::MRendererDriver(MRendererDriver&)
    {}

    MRendererDriver::~MRendererDriver()
    {}

    template<> MRendererDriver* Singleton<MRendererDriver>::_instance  = 0;

} // endless
