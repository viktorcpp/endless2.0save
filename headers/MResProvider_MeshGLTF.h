#pragma once

namespace endless
{
    class MResProvider_MeshGLTF
    {
    public:

        MMesh* Load( const char* path );

        MResProvider_MeshGLTF();
        virtual ~MResProvider_MeshGLTF();

    private:

        MResProvider_MeshGLTF(MResProvider_MeshGLTF&);

    }; // class MResProvider_MeshGLTF

} // namespace endless
