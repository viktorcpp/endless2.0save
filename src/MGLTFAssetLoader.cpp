
namespace endless
{
    bool MGLTFAssetLoader::Load( const char* path, Asset& asset )
    {
        __TRY__

        duk_context* context   = duk_create_heap(nullptr, nullptr, nullptr, nullptr, MScripts::duk_fatal_handle );
        std::string  content   = "";
        std::string  path_full = path;
        if( path_full.find(".glb") != std::string::npos )
        {
            //
        }
        else if( path_full.find(".gltf") != std::string::npos )
        {
            LoadASCII( path, content );
            duk_eval_string( context, content.c_str() );
            ParseASCII( context, asset );
        }

        duk_destroy_heap(context);
        
        return true;

        __CATCH__

    } // Load

    void MGLTFAssetLoader::LoadASCII( const char* path, std::string& out )
    {
        __TRY__

        if( !MUtils::FileExists(path) )
        {
            std::string error;
            MUtils::string_format( "%s : can't open file <%s> \n", __FUNCTION__, path );
            throw std::exception(error.c_str());
        }

        std::stringstream stream;
        std::string       file_path = path;
        std::ifstream     file(path);
        
        stream << "GLTF=" << file.rdbuf() << ";";

        out = stream.str();

        stream.str("");
        stream.clear();

        file.close();

        __CATCH__

    } // LoadFile

    void MGLTFAssetLoader::ParseASCII( duk_context* context, Asset& asset )
    {
        __TRY__

        ParseHeader     ( context, asset );
        ParseAccessors  ( context, asset );
        ParseBufferViews( context, asset );
        ParseBuffers    ( context, asset );
        ParseImages     ( context, asset );
        ParseMeshes     ( context, asset );
        ParseNodes      ( context, asset );
        ParseScene      ( context, asset );
        ParseTextures   ( context, asset );
        ParseSamplers   ( context, asset );
        LoadASCIIBuffer ( context, asset );

        __CATCH__
        
    } // ParseGLTF

    void MGLTFAssetLoader::LoadASCIIBuffer( duk_context* context, Asset& asset )
    {
        __TRY__

        Buffer buffer = asset.buffers[0];
        std::ifstream file( CFG.datapath +"meshes/"+ buffer.uri, std::ios::binary );
        if( !file.is_open() ){ throw std::exception( (std::string("LoadASCIIBuffer : Can't open file - ") + buffer.uri).c_str() ); }
        asset.data = std::unique_ptr<char[]>( new char[ buffer.byteLength ] );
        file.read( asset.data.get(), buffer.byteLength );
        file.close();

        __CATCH__

    } // LoadASCIIBuffer

    void MGLTFAssetLoader::ParseMaterials( duk_context* context, Asset& asset )
    {
        __TRY__
        
            duk_eval_string( context, "GLTF.materials" );

        __CATCH__

    } // ParseMaterials

    void MGLTFAssetLoader::ParseSamplers( duk_context* context, Asset& asset )
    {
        __TRY__

        duk_eval_string( context, "GLTF.samplers" );
        long c = (long)duk_get_length(context, -1);
        for( long x = 0; x < c; ++x )
        {
            Sampler sampler;
            duk_get_prop_index( context, -1, x );
            
                duk_get_prop_string( context, -1, "minFilter" );
                    sampler.minFilter = static_cast<Sampler::MinFilter>( duk_to_int(context, -1) );
                duk_pop(context); // duk_get_prop_string

                duk_get_prop_string( context, -1, "magFilter" );
                    sampler.magFilter = static_cast<Sampler::MagFilter>( duk_to_int(context, -1) );
                duk_pop(context); // duk_get_prop_string

                duk_get_prop_string( context, -1, "wrapS" );
                    sampler.wrapS = static_cast<Sampler::WrapMode>( duk_to_int(context, -1) );
                duk_pop(context); // duk_get_prop_string

                duk_get_prop_string( context, -1, "wrapT" );
                    sampler.wrapT = static_cast<Sampler::WrapMode>( duk_to_int(context, -1) );
                duk_pop(context); // duk_get_prop_string

            duk_pop(context); // duk_get_prop_index

            asset.samplers.push_back(sampler);

        } // for

        __CATCH__

    } // ParseSamplers

    void MGLTFAssetLoader::ParseTextures( duk_context* context, Asset& asset )
    {
        __TRY__

        MScripts* ms = MCore::GetMScripts();
        duk_eval_string( context, "GLTF.textures" );
        long c = (long)duk_get_length(context, -1);
        for( long x = 0; x < c; ++x )
        {
            Texture texture;
            duk_get_prop_index( context, -1, x );
                ms->GetPropLong( context, "sampler", texture.sampler );
                ms->GetPropLong( context, "source",  texture.source );
            duk_pop(context); // duk_get_prop_index

            asset.textures.push_back(texture);

        } // for

        __CATCH__

    } // ParseTextures

    void MGLTFAssetLoader::ParseScene( duk_context* context, Asset& asset )
    {
        __TRY__

        duk_eval_string( context, "GLTF.scenes" );
        long c = (long)duk_get_length(context, -1);
        for( long x = 0; x < c; ++x )
        {
            Scene scene;
            duk_get_prop_index( context, -1, x );

                duk_get_prop_string( context, -1, "nodes" );
                    long cc = (long)duk_get_length(context, -1);
                    for( long y = 0; y < cc; ++y )
                    {
                        duk_get_prop_index( context, -1, y );
                            scene.nodes.push_back( duk_to_int(context, -1) );
                        duk_pop(context); // duk_get_prop_index
                    }
                duk_pop(context); // duk_get_prop_string

            duk_pop(context); // duk_get_prop_index

            asset.scenes.push_back( scene );

        } // for

        __CATCH__

    } // ParseScene

    void MGLTFAssetLoader::ParseNodes( duk_context* context, Asset& asset )
    {
        __TRY__

        MScripts* ms = MCore::GetMScripts();
        duk_eval_string( context, "GLTF.nodes" );
        long c = (long)duk_get_length(context, -1);
        for( long x = 0; x < c; ++x )
        {
            Node node;
            duk_get_prop_index( context, -1, x );
                ms->GetPropString( context, "name", node.name );
                ms->GetPropLong  ( context, "mesh", node.mesh );
            duk_pop(context); // duk_get_prop_index

        } // for

        __CATCH__

    } // ParseNodes

    void MGLTFAssetLoader::ParseMeshes( duk_context* context, Asset& asset )
    {
        __TRY__

        MScripts* ms = MCore::GetMScripts();
        duk_eval_string( context, "GLTF.meshes" );
        long c = (long)duk_get_length(context, -1);
        for( long x = 0; x < c; ++x )
        {
            Mesh mesh;
            duk_get_prop_index( context, -1, x );

                ms->GetPropString( context, "name", mesh.name );

                duk_get_prop_string(context, -1, "primitives");
                    long cc = (long)duk_get_length(context, -1);
                    for( long y = 0; y < cc; ++y )
                    {
                        Primitive primitive;
                        duk_get_prop_index( context, -1, y );

                            ms->GetPropLong( context, "indices",  primitive.indices );
                            ms->GetPropLong( context, "material", primitive.material );

                            Attributes attr;
                            attr.reserve(3);
                            duk_get_prop_string( context, -1, "attributes" );

                                duk_get_prop_string( context, -1, "POSITION" );
                                    attr["POSITION"] = duk_to_int(context, -1);
                                duk_pop(context); // duk_get_prop_string

                                duk_get_prop_string( context, -1, "NORMAL" );
                                    attr["NORMAL"] = duk_to_int(context, -1);
                                duk_pop(context); // duk_get_prop_string

                                duk_get_prop_string( context, -1, "TEXCOORD_0" );
                                    attr["TEXCOORD_0"] = duk_to_int(context, -1);
                                duk_pop(context); // duk_get_prop_string

                            duk_pop(context); // duk_get_prop_string

                            primitive.attributes.push_back(attr);

                        duk_pop(context); // duk_get_prop_index

                        mesh.primitives.push_back(primitive);

                    } // for
                duk_pop(context); // duk_get_prop_string

            duk_pop(context); // duk_get_prop_index

            asset.meshes.push_back(mesh);

        } // for

        __CATCH__

    } // ParseMeshes

    void MGLTFAssetLoader::ParseImages( duk_context* context, Asset& asset )
    {
        __TRY__

        MScripts* ms = MCore::GetMScripts();
        duk_eval_string( context, "GLTF.images" );
        long c = (long)duk_get_length(context, -1);
        for( long x = 0; x < c; ++x )
        {
            Image image;
            duk_get_prop_index( context, -1, x );
                ms->GetPropString( context, "uri", image.uri );
            duk_pop(context); // duk_get_prop_index

            asset.images.push_back(image);

        } // for

        __CATCH__

    } // ParseImages

    void MGLTFAssetLoader::ParseBuffers( duk_context* context, Asset& asset )
    {
        __TRY__
        
        MScripts* ms = MCore::GetMScripts();
        duk_eval_string( context, "GLTF.buffers" );
        long c = (long)duk_get_length(context, -1);
        for( long x = 0; x < c; ++x )
        {
            Buffer buffer;
            duk_get_prop_index( context, -1, x );
                ms->GetPropLong( context,   "byteLength", buffer.byteLength );
                ms->GetPropString( context, "uri",        buffer.uri );
            duk_pop(context); // duk_get_prop_index

            asset.buffers.push_back(buffer);

        } // for

        __CATCH__

    } // ParseBuffers

    void MGLTFAssetLoader::ParseBufferViews( duk_context* context, Asset& asset )
    {
        __TRY__
        
        MScripts* ms = MCore::GetMScripts();
        duk_eval_string( context, "GLTF.bufferViews" );
        long c = (long)duk_get_length(context, -1);
        for( long x = 0; x < c; ++x )
        {
            BufferView bview;
            duk_get_prop_index( context, -1, x );

                ms->GetPropLong( context, "buffer", bview.buffer );
                ms->GetPropLong( context, "byteLength", bview.byteLength );
                ms->GetPropLong( context, "byteOffset", bview.byteOffset );

                duk_get_prop_string( context, -1, "target" );
                    bview.target = static_cast<BufferView::Target>( duk_to_int(context, -1) );
                duk_pop(context); // duk_get_prop_string

            duk_pop(context); // duk_get_prop_index

            asset.bufferViews.push_back(bview);

        } // for

        __CATCH__

    } // ParseBufferViews

    void MGLTFAssetLoader::ParseHeader( duk_context* context, Asset& asset )
    {
        __TRY__

        duk_eval_string( context, "GLTF.asset" );
        MCore::GetMScripts()->GetPropFloat(context, "version", asset.version);

        __CATCH__

    } // ParseHeader

    void MGLTFAssetLoader::ParseAccessors( duk_context* context, Asset& asset )
    {
        __TRY__

        MScripts* ms = MCore::GetMScripts();
        duk_eval_string( context, "GLTF.accessors" );
        long c = (long)duk_get_length( context, -1 );
        for( long x = 0; x < c; ++x )
        {
            Accessor accessor;
            duk_get_prop_index( context, -1, x );

                ms->GetPropLong( context, "bufferView", accessor.bufferView );
                ms->GetPropLong( context, "byteOffset", accessor.byteOffset );
                ms->GetPropLong( context, "count", accessor.count );
                
                duk_get_prop_string( context, -1, "componentType" );
                    accessor.componentType = static_cast<Accessor::ComponentType>( duk_to_int(context, -1) );
                duk_pop(context); // duk_get_prop_string

                duk_get_prop_string( context, -1, "type" );
                    std::string _type = duk_to_string(context, -1);
                    if (_type == "SCALAR") {
                        accessor.type = Accessor::Type::Scalar;
                    } else if (_type == "VEC2") {
                        accessor.type = Accessor::Type::Vec2;
                    } else if (_type == "VEC3") {
                        accessor.type = Accessor::Type::Vec3;
                    } else if (_type == "VEC4") {
                        accessor.type = Accessor::Type::Vec4;
                    } else if (_type == "MAT2") {
                        accessor.type = Accessor::Type::Mat2;
                    } else if (_type == "MAT3") {
                        accessor.type = Accessor::Type::Mat3;
                    } else if (_type == "MAT4") {
                        accessor.type = Accessor::Type::Mat4;
                    }
                duk_pop(context); // duk_get_prop_string

            duk_pop(context); // duk_get_prop_index

            asset.accessors.push_back(accessor);

        } // for

        __CATCH__

    } // ParseAccessors

    MGLTFAssetLoader::MGLTFAssetLoader(){}
    MGLTFAssetLoader::~MGLTFAssetLoader(){}

} // namespace endless
