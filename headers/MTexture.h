#pragma once

namespace endless
{
    class MTexture
    {
    public:

        struct AssetInfoTexture
        {
            std::string id            = "";
            std::string path_diffuse  = "";
            std::string path_normals  = "";
            std::string path_specular = "";

        }; // struct AssetInfoTexture

        struct TextureInternalData
        {
            typedef struct _component
            {
                ID3D11Resource*           resource        = nullptr;
                ID3D11ShaderResourceView* shader_res_view = nullptr;
                ID3D11SamplerState*       sampler_state   = nullptr;

            } Component;

            Component diffuse  = {};
            Component normal   = {};
            Component specular = {};

        }; // struct TextureInternalData

        ID3D11Resource*           Diffuse()       { return textureinternaldata.diffuse.resource; }
        ID3D11ShaderResourceView* DiffuseSRV()    { return textureinternaldata.diffuse.shader_res_view; }
        ID3D11SamplerState*       DiffuseSampler(){ return textureinternaldata.diffuse.sampler_state; }

        ID3D11Resource*           Normal()       { return textureinternaldata.normal.resource; }
        ID3D11ShaderResourceView* NormalSRV()    { return textureinternaldata.normal.shader_res_view; }
        ID3D11SamplerState*       NormalSampler(){ return textureinternaldata.normal.sampler_state; }

        ID3D11Resource*           Specular()       { return textureinternaldata.specular.resource; }
        ID3D11ShaderResourceView* SpecularSRV()    { return textureinternaldata.specular.shader_res_view; }
        ID3D11SamplerState*       SpecularSampler(){ return textureinternaldata.specular.sampler_state; }

        MTexture();
        MTexture( TextureInternalData texintdata );
        virtual ~MTexture();

    private:
        
        TextureInternalData textureinternaldata = {};

        MTexture(MTexture&);

    }; // class MTexture

} // namespace endless
