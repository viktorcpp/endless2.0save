#pragma once

namespace endless
{
    class MAssetsDB_Materials
    {
    public:

        void Load( MAssetsDB& parent );

        MAssetsDB_Materials();
        virtual ~MAssetsDB_Materials();

    private:

        MAssetsDB_Materials(MAssetsDB_Materials&);

    }; // class MAssetsDB_Materials

} // namespace endless
