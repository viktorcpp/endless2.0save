
namespace endless
{
    const char* MGameObject::Id( const char* newid )
    {
        if( newid != nullptr )
            id = newid;

        return id.c_str();

    } // Id

    MMesh& MGameObject::Mesh( MMesh* mesh )
    {
        if( mesh != nullptr )
            mmesh = mesh;

        return *mmesh;

    } // Mesh

    MMaterial& MGameObject::Material( MMaterial* material )
    {
        if( material != nullptr )
            mmaterial = material;

        return *mmaterial;

    } // Material

    MRigidBody& MGameObject::RigidBody( MRigidBody* rigidbody )
    {
        if( rigidbody != nullptr )
            mrigidbody = rigidbody;

        return *mrigidbody;

    } // RigidBody

    MTransform& MGameObject::Transform( MTransform* transform )
    {
        if( transform != nullptr )
            mtransform = transform;

        return *mtransform;

    } // Transform

    MGameObject::MGameObject(AssetInfoGO& go_desc) :
        mmesh(nullptr),
        mrigidbody(nullptr),
        mmaterial(nullptr)
    {}

    MGameObject::MGameObject() :
        mmesh(nullptr),
        mrigidbody(nullptr),
        mmaterial(nullptr)
    {}

    MGameObject::MGameObject(MGameObject&)
    {}

    MGameObject::~MGameObject(){}

} // namespace endless
