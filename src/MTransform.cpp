
namespace endless
{
    const XMFLOAT4 MTransform::XMVECTORF32_ZERO = { 0.f, 0.f, 0.f, 1.f };
    const XMFLOAT4 MTransform::XMVECTORF32_ONE  = { 1.f, 1.f, 1.f, 1.f };

    XMFLOAT4& MTransform::Position( XMFLOAT4* pos )
    {
        if( pos == 0 ) return tposition;
        tposition = *pos;
        return tposition;

    } // Position

    XMFLOAT4& MTransform::Rotation( XMFLOAT4* rot )
    {
        if( rot == 0 ) return trotation;
        trotation = *rot;
        return trotation;

    } // Rotation

    XMFLOAT4& MTransform::Scale( XMFLOAT4* sca )
    {
        if( sca == 0 ) return tscale;
        tscale = *sca;
        return tscale;

    } // Scale

    MTransform::MTransform() :
        tposition({0.f,0.f,0.f,0.f}),
        trotation({1.f,1.f,1.f,1.f}),
        tscale   ({1.f,1.f,1.f,1.f})
    {}

    MTransform::MTransform(MTransform&)
    {}

    MTransform::~MTransform(){}

} // namespace endless
