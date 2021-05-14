#pragma once

namespace endless
{
    class MWorld_AssetMain
    {
    public:

        void Load(MWorld& mworld) throw(std::exception);

        MWorld_AssetMain();
        virtual ~MWorld_AssetMain();

    private:

        MWorld_AssetMain(MWorld_AssetMain&);

    }; // class MWorld_AssetMain

} // namespace endless
