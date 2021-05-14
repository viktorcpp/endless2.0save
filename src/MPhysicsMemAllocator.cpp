
namespace endless
{
    void* MPhysicsMemAllocator::allocate(size_t size, const char* typeName, const char* filename, int line)
    {
        return _aligned_malloc(size, 16);

    } // allocate

    void MPhysicsMemAllocator::deallocate(void* ptr)
    {
        _aligned_free(ptr);

    } // deallocate

    MPhysicsMemAllocator::MPhysicsMemAllocator()
    {}

    MPhysicsMemAllocator::MPhysicsMemAllocator(MPhysicsMemAllocator&)
    {}

    MPhysicsMemAllocator::~MPhysicsMemAllocator()
    {}

} // namespace endless
