
namespace endless
{
    MTransform& MMesh::Transform( MTransform& tr )
    {
        transform = tr;
        return transform;

    } // Transform

    void MMesh::SetTexture( MTexture* new_texture )
    {
        texture = new_texture;

    } // SetTexture

    void MMesh::AddSubset( MMESH_SUBSET subset )
    {
        mesh_subsets.push_back(subset);

    } // AddSubset

    void MMesh::Draw()
    {
        context = MCore::GetMRendererDriver()->GetContext();

        if( mesh_subsets.size() > 0 )
        {
            // diffuse
            if( texture != nullptr )
            {
                ID3D11ShaderResourceView* srv = texture->DiffuseSRV();
                if( context != nullptr )
                {
                    context->PSSetShaderResources( 0, 1, &srv );
                    ID3D11SamplerState* sstate = texture->DiffuseSampler();
                    context->PSSetSamplers( 0, 1, &sstate );
                }
            }
        }

        for( int x = 0; x < (int)mesh_subsets.size(); ++x )
        {
            MMESH_SUBSET& subset = mesh_subsets[x];

            UINT stride = sizeof( MMESH_VERTEX );
            UINT offset = 0;
            context->IASetVertexBuffers( 0, 1, &subset.vertices_buffer, &stride, &offset );
            context->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

            context->Draw( (UINT)subset.vertices_count, 0 );

        } // for

    } // Draw

    MMesh::MMesh():
        gameobject(nullptr),
        transform(),
        texture(nullptr),
        context(nullptr),
        mesh_subsets()
    {}

    MMesh::~MMesh(){}

} // namespace endless
