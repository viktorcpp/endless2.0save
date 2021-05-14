#pragma once

namespace endless
{
    class MRendererDriver : public Singleton<MRendererDriver>
    {
    public:

        struct DisplayResolution
        {
            int w;
            int h;
        };

        ID3D11Device*           GetDevice(){ return device; }
        ID3D11DeviceContext*    GetContext(){ return context; }
        IDXGISwapChain*         GetSwapChain(){ return swapchain; }
        ID3D11DepthStencilView* GetDSView(){ return depth_view; }
        ID3D11RenderTargetView* GetRenderTargetView(){ return rendertargetview; }

        DisplayResolution& GetResolution( std::string id ){ return displayresolutions[id]; }
        auto&              GetResolutionsList(){ return displayresolutions; }

        void Resize( int w, int h ) throw(std::exception);

        void Setup() throw(std::exception);

        MRendererDriver();
        virtual ~MRendererDriver();

    private:

        UINT                     device_flags        = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
        D3D_FEATURE_LEVEL        feature_lvl_current = D3D_FEATURE_LEVEL_11_1;
        ID3D11Device*            device              = nullptr;
        ID3D11DeviceContext*     context             = nullptr;
        IDXGISwapChain*          swapchain           = nullptr;
        ID3D11RenderTargetView*  rendertargetview    = nullptr;
        ID3D11DepthStencilView*  depth_view          = nullptr;
        ID3D11DepthStencilState* depth_state         = nullptr;

        const D3D_FEATURE_LEVEL feature_lvls[7] =
        {
            D3D_FEATURE_LEVEL_11_1,
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_10_1,
            D3D_FEATURE_LEVEL_10_0,
            D3D_FEATURE_LEVEL_9_3,
            D3D_FEATURE_LEVEL_9_2,
            D3D_FEATURE_LEVEL_9_1
        };

        ID3D11Texture2D* back_buffer = nullptr;
        ID3D11Texture2D* depth_tex   = nullptr;

        std::unordered_map<std::string, DisplayResolution> displayresolutions;

        void CreateDevice() throw(std::exception);
        void CreateBackBuffer() throw(std::exception);
        void CreateRenderTarget() throw(std::exception);
        void CreateDepthStencilState() throw(std::exception);
        void CreateDepthStencilView() throw(std::exception);
        void CreateViewport() throw(std::exception);

        void GeneDisplayResolutions();

        MRendererDriver(MRendererDriver&);

    }; // MRendererDriver

} // namespace endless
