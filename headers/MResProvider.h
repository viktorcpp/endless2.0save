#pragma once

#include <MTexture.h>

#include <MResProvider_MeshGLTF.h>
#include <MResProvider_MeshObj.h>
#include <MResProvider_Rigids.h>
#include <MResProvider_Textures.h>

namespace endless
{
    class MResProvider : public Singleton<MResProvider>
    {
    public:

        MGameObject*        LoadGameObject( const char* id ) throw(std::exception);
        MMesh*              LoadMesh      ( const char* id ) throw(std::exception);
        MMaterial*          LoadMaterial  ( const char* id ) throw(std::exception);
        MTexture*           LoadTexture   ( const char* id ) throw(std::exception);
        void                LoadTexture   ( MTexture** tex, const char* id ) throw(std::exception);
        MRigidBody*         LoadRigid     ( const char* id ) throw(std::exception);

        ID3D11PixelShader*  CreateShaderPixel( const char* path, const char* entry="PS" );
        ID3D11VertexShader* CreateShaderVertex( const char* path, ID3DBlob** vs_data, const char* entry="VS" );
        void                Setup();

        MResProvider();
        ~MResProvider();

    private:

        friend class MResProvider_MeshGLTF;
        friend class MResProvider_MeshObj;
        friend class MResProvider_Rigids;
        friend class MResProvider_Textures;

        MResProvider(MResProvider&);

    }; // class MResProvider

} // namespace endless
