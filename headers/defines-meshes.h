#pragma once

namespace endless
{
    typedef struct MMesh_Vertex
    {
        XMFLOAT3 position;
        XMFLOAT3 normal;
        XMFLOAT2 tex;

    } MMESH_VERTEX;

    typedef struct MMesh_Index
    {
        uint32 ivert;
        uint32 itex;
        uint32 inorm;

    } MMESH_INDEX;

    typedef struct MMesh_Subset
    {
        ulong         vertices_count  = 0;
        ID3D11Buffer* vertices_buffer = nullptr;
        ulong         indices_count   = 0;
        ID3D11Buffer* indices_buffer  = nullptr;

        XMFLOAT3      position;

        D3D11_SUBRESOURCE_DATA vertices_buffer_data = {};
        D3D11_BUFFER_DESC      vertices_buffer_desc = {};

    } MMESH_SUBSET;

} // namespace endless
