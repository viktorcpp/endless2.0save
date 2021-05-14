#pragma once

namespace endless
{
    class MPhysicsMemAllocator : public PxAllocatorCallback
    {

    public:
        
        virtual void* allocate(size_t size, const char* typeName, const char* filename, int line);
        virtual void  deallocate(void* ptr);

        MPhysicsMemAllocator();
        virtual ~MPhysicsMemAllocator();

    private:

        MPhysicsMemAllocator(MPhysicsMemAllocator&);

    }; // class MPhysicsMemAllocator */

} // namespace endless
