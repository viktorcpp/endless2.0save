#pragma once

namespace endless
{
    class MAssetsDB_GameObjects
    {
    public:

        void Load( MAssetsDB& parent );

        MAssetsDB_GameObjects();
        virtual ~MAssetsDB_GameObjects();

    private:

        MAssetsDB_GameObjects(MAssetsDB_GameObjects&);

    }; // class MAssetsDB_GameObjects

} // namespace endless
