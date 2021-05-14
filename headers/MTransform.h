#pragma once

namespace endless
{
    class MTransform
    {
    public:

        XMFLOAT4& Position( XMFLOAT4* pos = 0 );
        XMFLOAT4& Rotation( XMFLOAT4* rot = 0 );
        XMFLOAT4& Scale   ( XMFLOAT4* rot = 0 );

        MTransform();
        virtual ~MTransform();

        static const XMFLOAT4 XMVECTORF32_ZERO;
        static const XMFLOAT4 XMVECTORF32_ONE;

    private:

        XMFLOAT4 tposition = {0.f,0.f,0.f,1.f};
        XMFLOAT4 trotation = {1.f,1.f,1.f,1.f};
        XMFLOAT4 tscale    = {1.f,1.f,1.f,1.f};

        MTransform(MTransform&);

    }; // class MTransform

} // namespace endless
