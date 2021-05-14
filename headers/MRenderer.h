#pragma once

#include <MRendererDriver.h>

namespace endless
{
    typedef struct WorldConstBuffer
    {
	    XMMATRIX world;
	    XMMATRIX view;
	    XMMATRIX projection;
        XMMATRIX wvp;

    } WORLD_CONST_BUFFER;

    __declspec(align(16)) class MRenderer : public Singleton<MRenderer>
    {
    public:

        MCamera* GetCameraMain(){ return cameras[0]; }

        void Setup()  throw(std::exception);
        bool Update() throw(std::exception);
        void OnResize(int w, int h);

        MRenderer();
        virtual ~MRenderer();

        void* operator new(size_t i)  { return _aligned_malloc(i, 16); }
        void  operator delete(void* p){ _aligned_free(p); }

        MMesh* test_mesh  = nullptr;
        MMesh* test_mesh2 = nullptr;

    private:

        std::vector<MCamera*> cameras;

        HRESULT                  hr                    = S_OK;
        MRendererDriver*         mdriver               = nullptr;
        ID3D11Device*            device                = nullptr;
        ID3D11DeviceContext*     d3dcontext            = nullptr;
        IDXGISwapChain*          swapchain             = nullptr;
        ID3D11RenderTargetView*  rendertargetview      = nullptr;

        D3D11_BUFFER_DESC        buffer_constants_desc = {};
        WORLD_CONST_BUFFER       buffer_constants_data = {};
        ID3D11Buffer*            buffer_constants      = nullptr;

        ID3D11VertexShader*      main_shader_vs        = nullptr;
        ID3D11PixelShader*       main_shader_px        = nullptr;
        ID3D11InputLayout*       main_shader_il        = nullptr;

        ID3D11SamplerState*      id3d11samplerstate    = nullptr;

        ID3D11Texture2D*         depth_tex             = nullptr;
        ID3D11DepthStencilView*  depth_view            = nullptr;
        ID3D11DepthStencilState* depth_state           = nullptr;

        MRenderer(MRenderer&);

        friend class MCore;
        friend class MRendererDriver;

    }; // MRenderer

} // endless
