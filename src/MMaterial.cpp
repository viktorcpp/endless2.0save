
namespace endless
{
    MTexture* MMaterial::Texture( MTexture* texture )
    {
        if( texture != nullptr )
            mtexture = texture;

        return mtexture;

    } // Texture

    MShader* MMaterial::Shader( MShader* shader )
    {
        if( shader != nullptr )
            mshader = shader;

        return mshader;

    } // Shader

    MMaterial::MMaterial( MMaterial::AssetInfoMaterial aim )
    {
        assetinfomaterial = aim;
    }

    MMaterial::MMaterial():
        mtexture(nullptr)
    {}

    MMaterial::MMaterial(MMaterial&)
    {}

    MMaterial::~MMaterial(){}

} // namespace endless
