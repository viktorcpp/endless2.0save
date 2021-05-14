#pragma once

namespace endless
{
    class MResProvider_Textures
    {
    public:

        void Load( MTexture::TextureInternalData::Component& comp, const char* path );

        MResProvider_Textures();
        virtual ~MResProvider_Textures();

    private:

        MResProvider_Textures(MResProvider_Textures&);

    }; // class MResProvider_Textures

} // namespace endless
