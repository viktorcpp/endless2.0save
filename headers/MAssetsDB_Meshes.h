#pragma once

namespace endless
{
    class MAssetsDB_Meshes
    {
    public:

        void Load( MAssetsDB& parent );

        MAssetsDB_Meshes();
        virtual ~MAssetsDB_Meshes();

    private:

        MAssetsDB_Meshes(MAssetsDB_Meshes&);

    }; // class MAssetsDB_Meshes

} // namespace endless
