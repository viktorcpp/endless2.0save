
namespace endless
{
    MMesh* MResProvider_MeshObj::Load( const char* path )
    {
        MMesh*       mmesh = new MMesh();
        MMESH_SUBSET mesh_subset;
        
        MMESH_VERTEX*            mesh = 0;
        std::vector<XMFLOAT3>    vv;
        std::vector<XMFLOAT3>    vt;
        std::vector<XMFLOAT3>    vn;
        std::vector<ushort>      inx;
        std::vector<MMESH_INDEX> indexes;
        ID3D11Device*            id3d11device = MCore::GetMRendererDriver()->GetDevice();
        ID3D11DeviceContext*     d3d11context = MCore::GetMRendererDriver()->GetContext();

        std::stringstream file_mem;
        MUtils::FileLoadBuffer( path, file_mem );
        
        ParseFile( file_mem, vv, vt, vn, indexes );

        file_mem.str("");
        file_mem.clear();

        mesh_subset.vertices_count = (ulong)indexes.size();

        CreateVertBuffer( mesh, vv, vt, vn, indexes );

        ZeroMemory( &mesh_subset.vertices_buffer_data, sizeof(mesh_subset.vertices_buffer_data) );
        ZeroMemory( &mesh_subset.vertices_buffer_desc, sizeof(mesh_subset.vertices_buffer_desc) );
        mesh_subset.vertices_buffer_data                = {};
        mesh_subset.vertices_buffer_desc                = {};
        mesh_subset.vertices_buffer_desc.Usage          = D3D11_USAGE_DEFAULT;
        mesh_subset.vertices_buffer_desc.ByteWidth      = 0;
        mesh_subset.vertices_buffer_desc.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
	    mesh_subset.vertices_buffer_desc.CPUAccessFlags = 0;

        mesh_subset.vertices_buffer_desc.ByteWidth = (UINT)sizeof( MMESH_VERTEX ) * (UINT)indexes.size();
        mesh_subset.vertices_buffer_data.pSysMem   = mesh;
        
        HRESULT hr = id3d11device->CreateBuffer( &mesh_subset.vertices_buffer_desc, &mesh_subset.vertices_buffer_data, &mesh_subset.vertices_buffer );
        if( FAILED( hr ) )
        {
            LOGE( "%s: CreateBuffer VERTEX FAILED\nPath to: %s\n", __FUNCTION__, path );
        }

        delete[] mesh;

        vv.clear();
        vt.clear();
        vn.clear();
        indexes.clear();

        mmesh->AddSubset(mesh_subset);

        return mmesh;

    } // Load

    void MResProvider_MeshObj::ParseFile( std::stringstream& data, std::vector<XMFLOAT3>& v, std::vector<XMFLOAT3>& vt, std::vector<XMFLOAT3>& vn, std::vector<MMESH_INDEX>& indexes )
    {
        std::string line;
        char buffer[512];

        while( std::getline( data, line ) )
        {
            if( line.size() < 1 || line[0] == '\n' || line[0] == '#' ) continue;

            ZeroMemory(buffer, sizeof(buffer));

            line.copy(buffer, line.size()-2, 2);

            if( line[0] == 'v' && line[1] == ' ' ) // vertices
            {
                XMFLOAT3 vertex;
                sscanf_s( buffer, "%f %f %f", &vertex.x, &vertex.y, &vertex.z );
                v.push_back(vertex);
            }
            else if( line[0] == 'v' && line[1] == 't' ) // texture coords
            {
                XMFLOAT3 texture;
                sscanf_s( buffer, "%f %f", &texture.x, &texture.y );
                vt.push_back(texture);
            }
            else if( line[0] == 'v' && line[1] == 'n' ) // normals
            {
                XMFLOAT3 normals;
                sscanf_s( buffer, "%f %f %f", &normals.x, &normals.y, &normals.z );
                vn.push_back(normals);
            }
            else if( line[0] == 'f' && line[1] == ' ' ) // face
            {
                line.copy(buffer, line.size()-1, 1);

                MMESH_INDEX face1;
                MMESH_INDEX face2;
                MMESH_INDEX face3;
                //MMESH_INDEX face4;
                sscanf_s( buffer, "%d/%d/%d %d/%d/%d %d/%d/%d",
                        &face1.ivert, &face1.itex, &face1.inorm,
                        &face2.ivert, &face2.itex, &face2.inorm,
                        &face3.ivert, &face3.itex, &face3.inorm );

                indexes.push_back(face1);
                indexes.push_back(face2);
                indexes.push_back(face3);
                //indexes.push_back(face4);
            }
            else if( line[0] == 'v' && line[1] == 'p' ) // хуета какая-то я хз
            {
                //
            }
            else if( line[0] == 'g' && line[1] == ' ' ) // group
            {
                //
            }
            else if( line[0] == 'o' && line[1] == ' ' ) // object
            {
                //
            }
            else if( line[0] == 'u' && line[1] == 's' ) // usemtl
            {
                //
            }
            else if( line[0] == 'm' && line[1] == 't' ) // mtllib
            {
                //
            }

            line = '\n';

        } // endwhile

    } // ParseFile

    void MResProvider_MeshObj::CreateVertBuffer( MMESH_VERTEX*& out, std::vector<XMFLOAT3>& vv, std::vector<XMFLOAT3>& vt, std::vector<XMFLOAT3>& vn, std::vector<MMESH_INDEX>& indexes )
    {
        out = new MMESH_VERTEX[ indexes.size() ];
        
        for( ulong x = 0; x < indexes.size(); ++x )
        {
            out[x].position = vv[indexes[x].ivert-1];
            out[x].normal   = vn[indexes[x].inorm-1];
            out[x].tex.x    = vt[indexes[x].itex-1 ].x;
            out[x].tex.y    = vt[indexes[x].itex-1 ].y;
        }

    } // CreateVertBuffer

    MResProvider_MeshObj::MResProvider_MeshObj()
    {}

    MResProvider_MeshObj::MResProvider_MeshObj(MResProvider_MeshObj&)
    {}

    MResProvider_MeshObj::~MResProvider_MeshObj()
    {}

} // namespace endless
