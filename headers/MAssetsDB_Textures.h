#pragma once

namespace endless
{
    class MAssetsDB_Textures
    {
    public:

        void Load( MAssetsDB& parent );

        MAssetsDB_Textures();
        virtual ~MAssetsDB_Textures();

    private:

        MAssetsDB_Textures(MAssetsDB_Textures&);

    }; // class MAssetsDB_Textures

} // namespace endless
