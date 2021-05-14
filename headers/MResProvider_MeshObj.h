#pragma once

namespace endless
{
    class MResProvider_MeshObj
    {
    public:

        MMesh* Load( const char* path );

        MResProvider_MeshObj();
        virtual ~MResProvider_MeshObj();

    private:

        void ParseFile( std::stringstream&, std::vector<XMFLOAT3>&, std::vector<XMFLOAT3>&, std::vector<XMFLOAT3>&, std::vector<MMESH_INDEX>& );
        void CreateVertBuffer( MMESH_VERTEX*&, std::vector<XMFLOAT3>&, std::vector<XMFLOAT3>&, std::vector<XMFLOAT3>&, std::vector<MMESH_INDEX>& );

        MResProvider_MeshObj(MResProvider_MeshObj&);

    }; // class MResProvider_MeshObj

} // namespace endless
