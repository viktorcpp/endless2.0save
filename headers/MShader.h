#pragma once

namespace endless
{
    class MShader
    {
    public:

        struct AssetInfoShader
        {
            std::string id         = "";
            std::string texture_id = "";

        }; // struct AssetMaterialInfo

        MShader();
        MShader( AssetInfoShader aim );
        virtual ~MShader();

    private:

        MShader( MShader& );

    }; // class MShader

} // namespace endless
