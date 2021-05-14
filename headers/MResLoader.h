#pragma once

namespace endless
{
    class MResLoader : Singleton<MResLoader>
    {
    public:

        void LoadTexture( MTexture**   tex,  const char* path ) throw(std::exception);
        void LoadMesh   ( MMesh**      mesh, const char* path ) throw(std::exception);
        void LoadRigid  ( MRigidBody** rb,   const char* path ) throw(std::exception);

        const auto& GetExceptions(){ return exceptions; }

        void Setup() throw(std::exception);

        MResLoader();
        virtual ~MResLoader();

    private:

        void Run() throw(std::exception);

        std::vector<std::exception_ptr> exceptions;
        std::thread                     self_thread;
        std::recursive_mutex            self_mutex;
        std::recursive_mutex*           main_mutex;
        bool                            is_ready = false;
        
        MResLoader(MResLoader&);

    }; // class MResLoader

} // namespace endless
