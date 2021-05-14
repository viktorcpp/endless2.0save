#pragma once

#define DIRECTX_VERSION 11

#if DIRECTX_VERSION == 11

#pragma warning( push )
#pragma warning(disable:4005)
#   include <d3d11.h>
#   include <d3d11_1.h>
#   include <dxgi.h>
#   include <D3DX11.h>
#   include <directxcolors.h>
#   include <d3dcompiler.h>
#   include <DirectXTex.h>
#pragma warning( pop )

#	pragma comment(lib, "d3dcompiler.lib")
//#	pragma comment(lib, "dxerr.lib")
#	pragma comment(lib, "comctl32.lib")

#ifdef _DEBUG
#	pragma comment(lib, "d3d11.lib")
#	pragma comment(lib, "d3dx11d.lib")
#	pragma comment(lib, "d3dx10d.lib")
#	pragma comment(lib, "DirectXEffects11_d.lib")
#   pragma comment(lib, "DirectXTex_d.lib")
#else
#   pragma comment(lib, "d3d11.lib")
#   pragma comment(lib, "d3dx11.lib")
#   pragma comment(lib, "d3dx10.lib")
#	pragma comment(lib, "DirectXEffects11.lib")
#   pragma comment(lib, "DirectXTex.lib")
#endif

#endif

namespace endless
{
    using namespace DirectX;

} // endless
