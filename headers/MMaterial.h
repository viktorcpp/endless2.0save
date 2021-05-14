#pragma once

namespace endless
{
    class MMaterial
    {
    public:

        struct AssetInfoMaterial
        {
            std::string id         = "";
            std::string sh_id      = "";
            std::string texture_id = "";

        }; // struct AssetMaterialInfo

        MTexture*   Texture    ( MTexture* texture = nullptr );
        MShader*    Shader     ( MShader* shader = nullptr );
        const char* Id()       { return assetinfomaterial.id.c_str(); }
        const char* TexId()    { return assetinfomaterial.texture_id.c_str(); }
        const char* ShaderId() { return assetinfomaterial.sh_id.c_str(); }

        MMaterial();
        MMaterial( AssetInfoMaterial aim );
        virtual ~MMaterial();

    private:

        MTexture*         mtexture          = nullptr;
        MShader*          mshader           = nullptr;
        AssetInfoMaterial assetinfomaterial = {};

        MMaterial(MMaterial&);

    }; // class MMaterial

} // namespace endless
