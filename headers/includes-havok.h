#ifndef _HAVOK_INC_
#define _HAVOK_INC_

#include <SDL.h>
#pragma comment(lib,  "SDL2main.lib")

///* Havok Physics
#include <Common/Base/hkBase.h>
#include <Common/Base/Container/String/hkStringBuf.h>
#include <Common/Base/Ext/hkBaseExt.h>

#include <Common/Base/DebugUtil/StatisticsCollector/hkStatisticsCollector.h>
#include <Common/Base/DebugUtil/MemoryExceptionTestingUtil/hkMemoryExceptionTestingUtil.h>

#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>

#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Monitor/MonitorStreamAnalyzer/hkMonitorStreamAnalyzer.h>

#include <Common/Base/Reflection/hkClass.h>
#include <Common/Base/Reflection/hkInternalClassMember.h>
#include <Common/Base/Reflection/hkTypeInfo.h>
#include <Common/Base/Reflection/Attributes/hkAttributes.h>
#include <Common/Base/Reflection/Registry/hkVtableClassRegistry.h>

#include <Common/Base/System/Io/FileSystem/hkFileSystem.h>
#include <Common/Base/System/Io/Reader/hkStreamReader.h>
#include <Common/Base/System/Stopwatch/hkStopwatch.h>

#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

#include <Common/Compat/hkCompat.h>

#include <Common/GeometryUtilities/hkGeometryUtilities.h>

#include <Common/Internal/hkInternal.h>

#include <Common/SceneData/hkSceneData.h>
#include <Common/SceneData/Scene/hkxScene.h>

#include <Common/Serialize/hkSerialize.h>
#include <Common/Serialize/Util/hkLoader.h>
#include <Common/Serialize/Util/hkSerializeUtil.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/Serialize/Util/hkBuiltinTypeRegistry.h>
#include <Common/Serialize/Version/hkVersionUtil.h>
#include <Common/Serialize/Version/hkVersionPatchManager.h>

#include <Common/Visualize/hkVisualize.h>

#include <Physics/Collide/hkpCollide.h>
#include <Physics/Collide/Agent/ConvexAgent/SphereBox/hkpSphereBoxAgent.h>
#include <Physics/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics/Collide/Shape/Convex/Sphere/hkpSphereShape.h>
#include <Physics/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h>
#include <Physics/Collide/Shape/Compound/Collection/ExtendedMeshShape/hkpExtendedMeshShape.h>
#include <Physics/Collide/Dispatch/hkpAgentRegisterUtil.h>
#include <Physics/Collide/Dispatch/hkpCollisionDispatcher.h>
#include <Physics/Collide/Query/Multithreaded/CollisionQuery/hkpCollisionQueryJobQueueUtils.h>
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastInput.h>			
#include <Physics/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>
#include <Physics/Collide/Agent/hkpProcessCollisionInput.h>

#include <Physics/Internal/hkpInternal.h>

#include <Physics/Dynamics/hkpDynamics.h>
#include <Physics/Dynamics/Entity/hkpRigidBody.h>
#include <Physics/Dynamics/World/hkpWorld.h>
#include <Physics/Dynamics/World/hkpPhysicsSystem.h>
#include <Physics/Dynamics/World/hkpSimulationIsland.h>
#include <Physics/Dynamics/World/Simulation/hkpSimulation.h>

#include <Physics/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>
#include <Physics/Utilities/Serialize/hkpPhysicsData.h>
#include <Physics/Utilities/Dynamics/TimeSteppers/hkpAsynchronousTimestepper.h>
#include <Physics/Utilities/VisualDebugger/hkpPhysicsContext.h>
#include <Physics/Utilities/Collide/TriggerVolume/hkpTriggerVolume.h>
#include <Physics/Utilities/Collide/hkpShapeGenerator.h>

#include <Common/Base/Thread/Job/ThreadPool/Cpu/hkCpuJobThreadPool.h>
//#include <Common/Base/Thread/Job/ThreadPool/Spu/hkSpuJobThreadPool.h>
#include <Common/Base/Thread/JobQueue/hkJobQueue.h>

#include <Animation/Animation/hkaAnimation.h>
#include <Animation/Animation/hkaAnimationContainer.h>
#include <Animation/Animation/Playback/Control/Default/hkaDefaultAnimationControl.h>
#include <Animation/Animation/Playback/hkaAnimatedSkeleton.h>
#include <Animation/Animation/Playback/Utilities/hkaAnimationContext.h>
#include <Animation/Animation/Rig/hkaPose.h>
#include <Animation/Ragdoll/hkaRagdoll.h>

#include <Common/Visualize/hkVisualDebugger.h>

#ifdef _DEBUG
#	pragma comment(lib, "hkaAnimation.lib")
#	pragma comment(lib, "hkaInternal.lib")
#	pragma comment(lib, "hkaRagdoll.lib")

#	pragma comment(lib, "hkBase.lib")
#	pragma comment(lib, "hkCompat.lib")
#	pragma comment(lib, "hkSceneData.lib")
#	pragma comment(lib, "hkSerialize.lib")
#	pragma comment(lib, "hkVisualize.lib")
#	pragma comment(lib, "hkInternal.lib")
#   pragma comment(lib, "hkGeometryUtilities.lib")

#	pragma comment(lib, "hkpCollide.lib")
#	pragma comment(lib, "hkpConstraintSolver.lib")
#	pragma comment(lib, "hkpDynamics.lib")
#	pragma comment(lib, "hkpInternal.lib")
#	pragma comment(lib, "hkpUtilities.lib")
#	pragma comment(lib, "hkpVehicle.lib")

//#	pragma comment(lib, "hkgBridge.lib")
//#	pragma comment(lib, "hkgCommon.lib")
//#	pragma comment(lib, "hkgDx9.lib")
//#	pragma comment(lib, "hkgDx9s.lib")
//#	pragma comment(lib, "hkgOgl.lib")
#else
#	pragma comment(lib, "hkaAnimation.lib")
#	pragma comment(lib, "hkaInternal.lib")
#	pragma comment(lib, "hkaRagdoll.lib")

#	pragma comment(lib, "hkBase.lib")
#	pragma comment(lib, "hkCompat.lib")
#	pragma comment(lib, "hkSceneData.lib")
#	pragma comment(lib, "hkSerialize.lib")
#	pragma comment(lib, "hkVisualize.lib")
#	pragma comment(lib, "hkInternal.lib")
#   pragma comment(lib, "hkGeometryUtilities.lib")

#	pragma comment(lib, "hkpCollide.lib")
#	pragma comment(lib, "hkpConstraintSolver.lib")
#	pragma comment(lib, "hkpDynamics.lib")
#	pragma comment(lib, "hkpInternal.lib")
#	pragma comment(lib, "hkpUtilities.lib")
#	pragma comment(lib, "hkpVehicle.lib")

//#	pragma comment(lib, "hkgBridge.lib")
//#	pragma comment(lib, "hkgCommon.lib")
//#	pragma comment(lib, "hkgDx9.lib")
//#	pragma comment(lib, "hkgDx9s.lib")
//#	pragma comment(lib, "hkgOgl.lib")
#endif

// @begin Õ≈ ”ƒ¿Àﬂ“‹ ¡Àﬂ“‹!!!
#include <Common/Base/keycode.cxx>

#undef HK_FEATURE_PRODUCT_AI
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#undef HK_FEATURE_PRODUCT_BEHAVIOR
#define HK_CLASSES_FILE <Common/Serialize/Classlist/hkClasses.h>
//#include <Common/Serialize/Util/hkBuiltinTypeRegistry.cxx>
#define HK_FEATURE_REFLECTION_PHYSICS
#define HK_FEATURE_PRODUCT_PHYSICS
#define HK_FEATURE_PRODUCT_ANIMATION
#include <Common/Base/Config/hkProductFeatures.cxx>

#endif
