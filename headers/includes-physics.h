#pragma once

#include "PxPhysicsAPI.h"

#ifndef _DEBUG

#pragma comment( lib, "PhysX3.lib" )
#pragma comment( lib, "PhysX3Common.lib" )
#pragma comment( lib, "PxFoundation.lib" )
#pragma comment( lib, "PhysX3Cooking.lib" )
#pragma comment( lib, "PhysX3CharacterKinematic.lib" )
#pragma comment( lib, "PxPvdSDK.lib" )
//#pragma comment( lib, "PhysX3Vehicle.lib" )
#pragma comment( lib, "PhysX3Extensions.lib" )

#else

#pragma comment( lib, "PhysX3_d.lib" )
#pragma comment( lib, "PhysX3Common_d.lib" )
#pragma comment( lib, "PxFoundation_d.lib" )
#pragma comment( lib, "PhysX3Cooking_d.lib" )
#pragma comment( lib, "PhysX3CharacterKinematic_d.lib" )
#pragma comment( lib, "PxPvdSDK_d.lib" )
//#pragma comment( lib, "PhysX3Vehicle_d.lib" )
#pragma comment( lib, "PhysX3Extensions_d.lib" )

#endif

namespace endless
{
    using namespace physx;

    PxFilterFlags FilterShader(
	    PxFilterObjectAttributes attributes0, PxFilterData filterData0,
	    PxFilterObjectAttributes attributes1, PxFilterData filterData1,
	    PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize )
    {
	    pairFlags = PxPairFlag::eTRIGGER_DEFAULT | PxPairFlag::eCONTACT_DEFAULT | PxPairFlag::eNOTIFY_TOUCH_FOUND;
	    return PxFilterFlag::eDEFAULT;
    }

} // namespace endless
