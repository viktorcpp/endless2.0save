
namespace endless
{
    MMesh* MResProvider_MeshGLTF::Load( const char* path )
    {
        Asset            asset;
        MGLTFAssetLoader loader;

        loader.Load( path, asset );

        ID3D11Device* device            = MCore::GetMRendererDriver()->GetDevice();
        MMESH_SUBSET* mesh_subsets_list = new MMESH_SUBSET[asset.meshes.size()];
        MMesh*        mmesh             = new MMesh();
        long          bin_data_offset   = 0U;
        long          mem_size          = 0U;
        
        for( int x_subsets = 0; x_subsets < (int)asset.meshes.size(); ++x_subsets )
        {
            
            MMESH_SUBSET& subset = mesh_subsets_list[x_subsets];

            Primitive&  mesh_subset     = asset.meshes[x_subsets].primitives[0];
            Accessor&   acc_vertices    = asset.accessors[mesh_subset.attributes[0]["POSITION"]];
            Accessor&   acc_normals     = asset.accessors[mesh_subset.attributes[0]["NORMAL"]];
            Accessor&   acc_texcoords   = asset.accessors[mesh_subset.attributes[0]["TEXCOORD_0"]];
            Accessor&   acc_indices     = asset.accessors[mesh_subset.indices];
            BufferView& bview           = asset.bufferViews[acc_vertices.bufferView];
            Buffer&     buffer          = asset.buffers[bview.buffer]; // init only beacase of LINK

            BufferView& bview_indices   = asset.bufferViews[acc_indices.bufferView];
            BufferView& bview_vertices  = asset.bufferViews[acc_vertices.bufferView];
            BufferView& bview_normals   = asset.bufferViews[acc_normals.bufferView];
            BufferView& bview_texcoords = asset.bufferViews[acc_texcoords.bufferView];

            std::unique_ptr<ushort[]>   indices_temp ( new ushort  [acc_indices.count ]  );
            std::unique_ptr<XMFLOAT3[]> vertex_floats( new XMFLOAT3[acc_vertices.count]  );
            std::unique_ptr<XMFLOAT3[]> normal_floats( new XMFLOAT3[acc_normals.count]   );
            std::unique_ptr<XMFLOAT2[]> tex_floats   ( new XMFLOAT2[acc_texcoords.count] );

            bin_data_offset = acc_indices.byteOffset + bview_indices.byteOffset;
            mem_size        = acc_indices.count*sizeof(ushort);
            buffer          = asset.buffers[bview_indices.buffer];
            memcpy(indices_temp.get(), &(asset.data.get()[bin_data_offset]), mem_size);
            
            bin_data_offset = acc_vertices.byteOffset + bview_vertices.byteOffset;
            mem_size        = acc_vertices.count*sizeof(XMFLOAT3);
            buffer          = asset.buffers[bview_vertices.buffer];
            memcpy(vertex_floats.get(), &(asset.data.get()[bin_data_offset]), mem_size);

            bin_data_offset = acc_normals.byteOffset + bview_normals.byteOffset;
            mem_size        = acc_normals.count*sizeof(XMFLOAT3);
            buffer          = asset.buffers[bview_normals.buffer];
            memcpy(normal_floats.get(), &(asset.data.get()[bin_data_offset]), mem_size);
            
            bin_data_offset = acc_texcoords.byteOffset + bview_texcoords.byteOffset;
            mem_size        = acc_texcoords.count*sizeof(XMFLOAT2);
            buffer          = asset.buffers[bview_texcoords.buffer];
            memcpy(tex_floats.get(), &(asset.data.get()[bin_data_offset]), mem_size);
            
            subset.indices_count  = acc_indices.count;
            subset.vertices_count = acc_indices.count;

            ZeroMemory( &subset.vertices_buffer_data, sizeof(D3D11_SUBRESOURCE_DATA) );
            ZeroMemory( &subset.vertices_buffer_desc, sizeof(D3D11_BUFFER_DESC) );
            subset.vertices_buffer_desc.Usage          = D3D11_USAGE_DEFAULT;
            subset.vertices_buffer_desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
	        subset.vertices_buffer_desc.CPUAccessFlags = 0;

            unique_ptr<MMESH_VERTEX[]> tmp_mesh(new MMESH_VERTEX[subset.indices_count]);

            for( int x = 0; x < (int)subset.indices_count; ++x )
            {
                long          index  = indices_temp[x];
                MMESH_VERTEX& vertex = tmp_mesh[x];

                vertex.position = vertex_floats[index];
                vertex.normal   = normal_floats[index];
                vertex.tex      = tex_floats[index];
                //LOGN("VERT [%d]:\n", x);
                //LOGN("pos: %f    %f    %f\n", vertex.position.x, vertex.position.y, vertex.position.z);
                //LOGN("nrm: %f    %f    %f\n", vertex.normal.x, vertex.normal.y, vertex.normal.z);
                //LOGN("tex: %f    %f\n", vertex.tex.x, vertex.tex.y);
            }

            subset.vertices_buffer_desc.ByteWidth = sizeof( MMESH_VERTEX ) * subset.vertices_count;
            subset.vertices_buffer_data.pSysMem   = tmp_mesh.get();
        
            HRESULT hr = device->CreateBuffer( &subset.vertices_buffer_desc, &subset.vertices_buffer_data, &subset.vertices_buffer );
            if( FAILED( hr ) )
            {
                LOGE( "%s: CreateBuffer VERTEX FAILED <%s>\n", __FUNCTION__, path );
            }

            //__deletea(buffer.data);

            mmesh->AddSubset(mesh_subsets_list[x_subsets]);

        } // for

        return mmesh;

    } // Load

    MResProvider_MeshGLTF::MResProvider_MeshGLTF()
    {}

    MResProvider_MeshGLTF::MResProvider_MeshGLTF(MResProvider_MeshGLTF&)
    {}

    MResProvider_MeshGLTF::~MResProvider_MeshGLTF()
    {}

} // namespace endless
