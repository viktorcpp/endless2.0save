
namespace endless
{
    MTexture::MTexture():
        textureinternaldata()
    {}

    MTexture::MTexture( TextureInternalData texintdata )
    {
        textureinternaldata = texintdata;

    } // MTexture

    MTexture::MTexture(MTexture&)
    {}

    MTexture::~MTexture()
    {
        __Release(textureinternaldata.diffuse.resource);
        __Release(textureinternaldata.diffuse.resource);
        __Release(textureinternaldata.diffuse.resource);

        __Release(textureinternaldata.normal.resource);
        __Release(textureinternaldata.normal.resource);
        __Release(textureinternaldata.normal.resource);

        __Release(textureinternaldata.diffuse.resource);
        __Release(textureinternaldata.diffuse.resource);
        __Release(textureinternaldata.diffuse.resource);
    }

} // namespace endless
