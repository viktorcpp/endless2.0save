#pragma once

namespace endless
{
    typedef struct __Accessor
    {
        long bufferView = 0L;
        long byteOffset = 0L;

        enum class ComponentType : unsigned long
        {
            Byte   = 5120,
            UByte  = 5121,
            Short  = 5122,
            UShort = 5123,
            UInt   = 5125,
            Float  = 5126

        } componentType;

        long count = 0;

        float min[3] = {0};
        float max[3] = {0};

        enum class Type : unsigned long
        {
            Scalar = 0,
            Vec2,
            Vec3,
            Vec4,
            Mat2,
            Mat3,
            Mat4

        } type;

    } Accessor; // struct Accessor

    typedef struct __BufferView
    {
        long buffer     = 0L;
        long byteLength = 0L;
        long byteOffset = 0L;
        
        enum class Target : unsigned long
        {
            None               = 0,
            ArrayBuffer        = 34962,
            ElementArrayBuffer = 34963

        } target;

    } BufferView; // struct BufferView

    typedef struct __Buffer
    {
        long        byteLength = 0L;
        std::string uri        = "";

    } Buffer; // struct Buffer

    typedef struct __Image
    {
        std::string uri = "";

    } Image; // struct Image

    using Attributes = std::unordered_map<std::string, unsigned long>;

    typedef struct __Primitive
    {
        long indices  = 0L;
        long material = 0L;

        std::vector<Attributes> attributes;

        enum class Mode : unsigned long
        {
            Points        = 0,
            Lines         = 1,
            LineLoop      = 2,
            LineStrip     = 3,
            Triangles     = 4,
            TriangleStrip = 5,
            TriangleFan   = 6

        } mode = Mode::Triangles;

    } Primitive; // struct Primitive

    typedef struct __Mesh
    {
        std::string            name = "";
        std::vector<Primitive> primitives;

    } Mesh; // struct Mesh

    typedef struct __Node
    {
        long        mesh = 0L;
        std::string name = "";

        float matrix[4][4] = {0};

    } Node; // struct Node

    typedef struct __Scene
    {
        std::vector<long> nodes;

    } Scene; // struct Scene

    struct Texture
    {
        long sampler = 0L;
        long source  = 0L;

    }; // struct Texture

    typedef struct __Sampler
    {
        std::string name = "";

        enum class MagFilter : unsigned long
        {
            None    = 0L,
            Nearest = 9728,
            Linear  = 9729

        } magFilter{MagFilter::None};

        enum class MinFilter : unsigned long
        {
            None                 = 0L,
            Nearest              = 9728,
            Linear               = 9729,
            NearestMipMapNearest = 9984,
            LinearMipMapNearest  = 9985,
            NearestMipMapLinear  = 9986,
            LinearMipMapLinear   = 9987

        } minFilter{MinFilter::None};

        enum class WrapMode : unsigned long
        {
            ClampToEdge    = 33071,
            MirroredRepeat = 33648,
            Repeat         = 10497
        };

        WrapMode wrapS{WrapMode::Repeat};
        WrapMode wrapT{WrapMode::Repeat};

    } Sampler; // struct Sampler

    typedef struct __Material
    {
        std::string name              = "";
        float       emissiveFactor[3] = {0};

        enum class AlphaMode : unsigned long
        {
            Opaque,
            Mask,
            Blend

        } alphaMode{AlphaMode::Opaque};

    } Material; // struct Material

    typedef struct __Asset
    {
        float version = 2.f;
        long  scene   = 0L;

        std::vector<Accessor>   accessors;
        std::vector<BufferView> bufferViews;
        std::vector<Buffer>     buffers;
        std::vector<Image>      images;
        std::vector<Mesh>       meshes;
        std::vector<Node>       nodes;
        std::vector<Scene>      scenes;
        std::vector<Texture>    textures;
        std::vector<Sampler>    samplers;
        std::vector<Material>   materials;

        unique_ptr<char[]> data;

    } Asset; // struct Asset

    class MGLTFAssetLoader
    {
    public:

        bool Load( const char* path, Asset& asset ) throw(std::exception);
        
        MGLTFAssetLoader();
        virtual ~MGLTFAssetLoader();

    private:

        void LoadASCII       ( const char* path, std::string& out ) throw(std::exception);
        void ParseASCII      ( duk_context* context, Asset& asset ) throw(std::exception);
        void ParseAccessors  ( duk_context* context, Asset& asset ) throw(std::exception);
        void ParseHeader     ( duk_context* context, Asset& asset ) throw(std::exception);
        void ParseBufferViews( duk_context* context, Asset& asset ) throw(std::exception);
        void ParseBuffers    ( duk_context* context, Asset& asset ) throw(std::exception);
        void ParseImages     ( duk_context* context, Asset& asset ) throw(std::exception);
        void ParseMeshes     ( duk_context* context, Asset& asset ) throw(std::exception);
        void ParseNodes      ( duk_context* context, Asset& asset ) throw(std::exception);
        void ParseScene      ( duk_context* context, Asset& asset ) throw(std::exception);
        void ParseTextures   ( duk_context* context, Asset& asset ) throw(std::exception);
        void ParseSamplers   ( duk_context* context, Asset& asset ) throw(std::exception);
        void ParseMaterials  ( duk_context* context, Asset& asset ) throw(std::exception);
        void LoadASCIIBuffer ( duk_context* context, Asset& asset ) throw(std::exception);

    }; // class MGLTFAssetLoader

} // namespace endless
