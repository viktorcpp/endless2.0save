#pragma once

namespace endless
{
    class MResManager : public Singleton<MResManager>
    {
    public:

        void LoadTexture( MTexture**,   std::string id );
        void LoadMesh   ( MMesh**,      std::string id );
        void LoadRigid  ( MRigidBody**, std::string id );

        void Setup();

        MResManager();
        virtual ~MResManager();

    private:

        std::unordered_map<std::string, MTexture*>   textures;
        std::unordered_map<std::string, MMesh*>      meshes;
        std::unordered_map<std::string, MRigidBody*> rigids;

        std::vector<std::exception_ptr> exceptions;

        MResManager(MResManager&);

        friend class MCore;

    }; // class MResManager

} // namespace endless
