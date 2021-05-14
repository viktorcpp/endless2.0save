
namespace endless
{
    //MResProvider_Textures
    void MResProvider_Textures::Load( MTexture::TextureInternalData::Component& comp, const char* path )
    {
        if( path == 0 )
        {
            LOGE( "%s : path == 0", __FUNCTION__ );
            return;
        }

        std::string                     _error_buffer;
        D3D11_SHADER_RESOURCE_VIEW_DESC _srv_desc;
        TexMetadata                     _tex_metadata;
        ScratchImage                    _scratch_image;
        D3D11_SAMPLER_DESC              _sampler_desc;
        ID3D11Resource*                 _texture_res    = nullptr;
        ID3D11ShaderResourceView*       _shader_resview = nullptr;
        ID3D11SamplerState*             _samplerstate   = nullptr;
        ID3D11Device*                   _device         = const_cast<ID3D11Device*>( MCore::GetMRendererDriver()->GetDevice() );
        
        ZeroMemory( &_srv_desc,     sizeof( D3D11_SHADER_RESOURCE_VIEW_DESC ) );
        ZeroMemory( &_tex_metadata, sizeof( TexMetadata ) );
        ZeroMemory( &_sampler_desc, sizeof( D3D11_SAMPLER_DESC ) );

        std::wstring wpath;
        MUtils::LtoW( path, wpath);

        __TRY__

        HRESULT hr = LoadFromDDSFile( wpath.c_str(), DDS_FLAGS_NONE, nullptr, _scratch_image );
        if( FAILED(hr) )
        {
            MUtils::TranslateLastError(_error_buffer);
            LOGE( "%s : LoadFromDDSFile FAILED <%s> at <%s>\n", __FUNCTION__, _error_buffer.c_str(), path );
            return;
        }

        _tex_metadata    = _scratch_image.GetMetadata();
        _srv_desc.Format = _tex_metadata.format;

        hr = CreateTexture( _device, _scratch_image.GetImages(), _scratch_image.GetImageCount(), _tex_metadata, &_texture_res );
        if( FAILED(hr) )
        {
            MUtils::TranslateLastError(_error_buffer);
            LOGE( "%s : CreateTexture FAILED <%s>\n", __FUNCTION__, _error_buffer.c_str() );
            return;
        }

        if( _tex_metadata.arraySize > 1 )
        {
            _srv_desc.ViewDimension            = D3D11_SRV_DIMENSION_TEXTURE1DARRAY;
            _srv_desc.Texture1DArray.MipLevels = (UINT)_tex_metadata.mipLevels;
            _srv_desc.Texture1DArray.ArraySize = (UINT)_tex_metadata.arraySize;
        }
        else
        {
            _srv_desc.ViewDimension       = D3D11_SRV_DIMENSION_TEXTURE2D;
            _srv_desc.Texture1D.MipLevels = (UINT)_tex_metadata.mipLevels;
        }

        hr = _device->CreateShaderResourceView( _texture_res, &_srv_desc, &_shader_resview );
        if( FAILED(hr) )
        {
            MUtils::TranslateLastError(_error_buffer);
            LOGE( "%s : CreateShaderResourceView FAILED <%s>\n", __FUNCTION__, _error_buffer.c_str() );
            return;
        }

        // Sampler State default
        _sampler_desc.Filter         = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        _sampler_desc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
        _sampler_desc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
        _sampler_desc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
        _sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        _sampler_desc.MinLOD         = 0;
        _sampler_desc.MaxLOD         = D3D11_FLOAT32_MAX;
        _sampler_desc.MipLODBias     = 0.0f;
        _sampler_desc.MaxAnisotropy  = 1;
        _sampler_desc.BorderColor[0] = 0;
        _sampler_desc.BorderColor[1] = 0;
        _sampler_desc.BorderColor[2] = 0;
        _sampler_desc.BorderColor[3] = 0;
        hr = _device->CreateSamplerState( &_sampler_desc, &_samplerstate );
        if( FAILED( hr ) )
        {
            MUtils::TranslateLastError(_error_buffer);
            LOGE( "%s : CreateSamplerState FAILED <%s>\n", __FUNCTION__, _error_buffer.c_str() );
            return;
        }

        comp.resource        = _texture_res;
        comp.sampler_state   = _samplerstate;
        comp.shader_res_view = _shader_resview;

        __CATCH__

    } // Load

    MResProvider_Textures::MResProvider_Textures()
    {}

    MResProvider_Textures::MResProvider_Textures(MResProvider_Textures&)
    {}

    MResProvider_Textures::~MResProvider_Textures()
    {}

} // namespace endless
