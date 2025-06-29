include(FetchContent)

FetchContent_Declare(vcpkg
    GIT_REPOSITORY https://github.com/microsoft/vcpkg.git
    GIT_TAG 89dc8be6dbcf18482a5a1bf86a2f4615c939b0fb)
FetchContent_MakeAvailable(vcpkg)

set(CMAKE_TOOLCHAIN_FILE "${vcpkg_SOURCE_DIR}/scripts/buildsystems/vcpkg.cmake"
    CACHE STRING "CMake toolchain file")

cmake_minimum_required(VERSION 3.31)
project(U3D)

# I do not want to support asm code, so disable it
# there were real problems with cpuid on Ubuntu 13.04 i386
ADD_DEFINITIONS( -DU3D_NO_ASM )

if( NOT MSVC )
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif( NOT MSVC )

# check zlib availibility
find_package(ZLIB REQUIRED)

# check png availibility
find_package(PNG REQUIRED)

# check jpeg availibility
find_package(JPEG REQUIRED)

set(U3D_PLATFORM Win32)
INCLUDE_DIRECTORIES( 
	RTL/Component/Include 
	RTL/Kernel/Include RTL/Platform/Include
	RTL/Component/Base
	RTL/Component/BitStream
	RTL/Component/Bones
	RTL/Component/BoundHierarchy
	RTL/Component/CLODAuthor
	RTL/Component/Common
	RTL/Component/Generators/CLOD
	RTL/Component/Generators/Glyph2D
	RTL/Component/Generators/LineSet
	RTL/Component/Generators/PointSet
	RTL/Component/Mesh
	RTL/Component/ModifierChain
	RTL/Component/Palette
	RTL/Component/Rendering
	RTL/Component/SceneGraph
	RTL/Component/Shaders
	RTL/Component/Subdiv
	RTL/Component/Texture
	RTL/Component/UVGenerator
	RTL/Kernel/IFXCom
	RTL/Kernel/Common
	RTL/Dependencies/FNVHash
	RTL/Dependencies/Predicates
	RTL/Dependencies/WildCards
)

set(Kernel_SRCS
	RTL/Kernel/Common/CIFXConnector.cpp
	RTL/Kernel/Common/CIFXPerformanceTimer.cpp
	RTL/Kernel/Common/IFXCheckX.cpp
	RTL/Kernel/IFXCom/CIFXComponentManager.cpp
	RTL/Kernel/IFXCom/CIFXGUIDHashMap.cpp
	RTL/Kernel/IFXCom/CIFXPluginProxy.cpp
	RTL/Kernel/IFXCom/IFXCom.cpp
	RTL/Kernel/Memory/IFXMemory.cpp
	RTL/Kernel/DataTypes/IFXCoreArray.cpp
	RTL/Kernel/DataTypes/IFXCoreList.cpp
	RTL/Kernel/DataTypes/IFXFastAllocator.cpp
	RTL/Kernel/DataTypes/IFXListNode.cpp
	RTL/Kernel/DataTypes/IFXMatrix4x4.cpp
	RTL/Kernel/DataTypes/IFXQuaternion.cpp
	RTL/Kernel/DataTypes/IFXString.cpp
	RTL/Kernel/DataTypes/IFXUnitAllocator.cpp
	RTL/Kernel/DataTypes/IFXVector3.cpp
	RTL/Kernel/DataTypes/IFXVector4.cpp
	RTL/Kernel/Common/IFXDebug.cpp
)

add_library(Kernel STATIC ${Kernel_SRCS})
target_include_directories(Kernel PUBLIC
	"RTL/Kernel/Include"
)


SET( IFXCore_SRCS
	RTL/Platform/${U3D_PLATFORM}/IFXCore/IFXCoreDllMain.cpp
	RTL/IFXCorePluginStatic/IFXCorePluginStatic.cpp
	RTL/Platform/${U3D_PLATFORM}/Common/IFXOSLoader.cpp
	RTL/Platform/${U3D_PLATFORM}/Common/IFXOSRenderWindow.cpp
	RTL/Platform/${U3D_PLATFORM}/Common/IFXOSUtilities.cpp
	RTL/Component/Base/IFXCoincidentVertexMap.cpp
	RTL/Component/Base/IFXCornerIter.cpp
	RTL/Component/Base/IFXEuler.cpp
	RTL/Component/Base/IFXFatCornerIter.cpp
	RTL/Component/Base/IFXTransform.cpp
	RTL/Component/Base/IFXVectorHasher.cpp
	RTL/Component/Base/IFXVertexMap.cpp
	RTL/Component/Base/IFXVertexMapGroup.cpp
	RTL/Component/BitStream/CIFXBitStreamX.cpp
	RTL/Component/BitStream/CIFXDataBlockQueueX.cpp
	RTL/Component/BitStream/CIFXDataBlockX.cpp
	RTL/Component/BitStream/IFXHistogramDynamic.cpp
	RTL/Component/Bones/CIFXAnimationModifier.cpp
	RTL/Component/Bones/CIFXBoneWeightsModifier.cpp
	RTL/Component/Bones/CIFXSkeleton.cpp
	RTL/Component/Bones/IFXBoneCacheArray.cpp
	RTL/Component/Bones/IFXBoneNode.cpp
	RTL/Component/Bones/IFXBonesManagerImpl.cpp
	RTL/Component/Bones/IFXCharacter.cpp
	RTL/Component/Bones/IFXCoreNode.cpp
	RTL/Component/Bones/IFXKeyTrack.cpp
	RTL/Component/Bones/IFXMeshGroup_Character.cpp
	RTL/Component/Bones/IFXMixerQueue.cpp
	RTL/Component/Bones/IFXMixerQueueImpl.cpp
	RTL/Component/Bones/IFXMotion.cpp
	RTL/Component/Bones/IFXMotionManagerImpl.cpp
	RTL/Component/Bones/IFXMotionMixerImpl.cpp
	RTL/Component/Bones/IFXSkin.cpp
	RTL/Component/Bones/IFXSkin_p3.cpp
	RTL/Component/Bones/IFXVertexWeight.cpp
	RTL/Component/Bones/IFXVertexWeights.cpp
	RTL/Component/BoundHierarchy/CIFXAABBHierarchyBuilder.cpp
	RTL/Component/BoundHierarchy/CIFXAxisAlignedBBox.cpp
	RTL/Component/BoundHierarchy/CIFXBoundFace.cpp
	RTL/Component/BoundHierarchy/CIFXBoundHierarchy.cpp
	RTL/Component/BoundHierarchy/CIFXBoundUtil.cpp
	RTL/Component/BoundHierarchy/CIFXBTree.cpp
	RTL/Component/BoundHierarchy/CIFXBTreeNode.cpp
	RTL/Component/BoundHierarchy/CIFXCollisionResult.cpp
	RTL/Component/BoundHierarchy/CIFXPickObject.cpp
	RTL/Component/BoundHierarchy/CIFXPrimitiveOverlap.cpp
	RTL/Component/BoundHierarchy/CIFXResultAllocator.cpp
	RTL/Component/CLODAuthor/CIFXAuthorCLODGen.cpp
	RTL/Component/CLODAuthor/CIFXAuthorMeshMap.cpp
	RTL/Component/CLODAuthor/CIFXSetAdjacencyX.cpp
	RTL/Component/CLODAuthor/CIFXSetX.cpp
	RTL/Component/CLODAuthor/CLODGenerator.cpp
	RTL/Component/CLODAuthor/ContractionRecorder.cpp
	RTL/Component/CLODAuthor/Face.cpp
	RTL/Component/CLODAuthor/Matrix4x4.cpp
	RTL/Component/CLODAuthor/NormalMap.cpp
	RTL/Component/CLODAuthor/Pair.cpp
	RTL/Component/CLODAuthor/PairFinder.cpp
	RTL/Component/CLODAuthor/PairHash.cpp
	RTL/Component/CLODAuthor/PairHeap.cpp
	RTL/Component/CLODAuthor/Primitives.cpp
	RTL/Component/CLODAuthor/Vertex.cpp
	RTL/Component/CLODAuthor/VertexPairContractor.cpp
	RTL/Component/Common/CIFXCoreServices.cpp
	RTL/Component/Common/CIFXCoreServicesRef.cpp
	RTL/Component/Common/CIFXHashMap.cpp
	RTL/Component/Common/CIFXIDManager.cpp
	RTL/Component/Common/CIFXMetaData.cpp
	RTL/Component/Common/CIFXNameMap.cpp
	RTL/Component/Common/CIFXSimpleHash.cpp
	RTL/Component/Common/CIFXVoidWrapper.cpp
	RTL/Component/Common/IFXComponentDescriptorList.cpp
	RTL/Component/Common/IFXComponentIds.cpp
	RTL/Component/Common/IFXDids.cpp
	RTL/Component/Generators/CLOD/CIFXAuthorCLODResource.cpp
	RTL/Component/Generators/CLOD/CIFXAuthorMesh.cpp
	RTL/Component/Generators/CLOD/CIFXAuthorMeshScrub.cpp
	RTL/Component/Generators/CLOD/CIFXCLODModifier.cpp
	RTL/Component/Generators/CLOD/CIFXMeshCompiler.cpp
	RTL/Component/Generators/CLOD/CIFXMeshMap.cpp
	RTL/Component/Generators/CLOD/IFXCLODManager.cpp
	RTL/Component/Generators/CLOD/IFXNeighborResController.cpp
	RTL/Component/Generators/Glyph2D/CIFXContour.cpp
	RTL/Component/Generators/Glyph2D/CIFXContourExtruder.cpp
	RTL/Component/Generators/Glyph2D/CIFXContourGenerator.cpp
	RTL/Component/Generators/Glyph2D/CIFXContourTessellator.cpp
	RTL/Component/Generators/Glyph2D/CIFXGlyph2DCommands.cpp
	RTL/Component/Generators/Glyph2D/CIFXGlyph2DModifier.cpp
	RTL/Component/Generators/Glyph2D/CIFXGlyph3DGenerator.cpp
	RTL/Component/Generators/Glyph2D/CIFXGlyphCommandList.cpp
	RTL/Component/Generators/Glyph2D/CIFXQuadEdge.cpp
	RTL/Component/Generators/LineSet/CIFXAuthorLineSetAnalyzer.cpp
	RTL/Component/Generators/LineSet/CIFXAuthorLineSet.cpp
	RTL/Component/Generators/LineSet/CIFXAuthorLineSetResource.cpp
	RTL/Component/Generators/PointSet/CIFXAuthorPointSet.cpp
	RTL/Component/Generators/PointSet/CIFXAuthorPointSetResource.cpp
	RTL/Component/Mesh/CIFXInterleavedData.cpp
	RTL/Component/Mesh/CIFXMesh.cpp
	RTL/Component/Mesh/CIFXMeshGroup.cpp
	RTL/Component/Mesh/CIFXNeighborMesh.cpp
	RTL/Component/Mesh/CIFXRenderable.cpp
	RTL/Component/Mesh/IFXFaceLists.cpp
	RTL/Component/ModifierChain/CIFXDidRegistry.cpp
	RTL/Component/ModifierChain/CIFXModifierChain.cpp
	RTL/Component/ModifierChain/CIFXModifier.cpp
	RTL/Component/ModifierChain/CIFXModifierDataElementIter.cpp
	RTL/Component/ModifierChain/CIFXModifierDataPacket.cpp
	RTL/Component/ModifierChain/CIFXSubject.cpp
	RTL/Component/ModifierChain/IFXModifierChainState.cpp
	RTL/Component/Palette/CIFXPalette.cpp
	RTL/Component/Palette/CIFXSimpleObject.cpp
	RTL/Component/SceneGraph/CIFXBoundSphereDataElement.cpp
	RTL/Component/SceneGraph/CIFXDevice.cpp
	RTL/Component/SceneGraph/CIFXDummyModifier.cpp
	RTL/Component/SceneGraph/CIFXFileReference.cpp
	RTL/Component/SceneGraph/CIFXGroup.cpp
	RTL/Component/SceneGraph/CIFXLight.cpp
	RTL/Component/SceneGraph/CIFXLightResource.cpp
	RTL/Component/SceneGraph/CIFXLightSet.cpp
	RTL/Component/SceneGraph/CIFXMarker.cpp
	RTL/Component/SceneGraph/CIFXMaterialResource.cpp
	RTL/Component/SceneGraph/CIFXMixerConstruct.cpp
	RTL/Component/SceneGraph/CIFXModel.cpp
	RTL/Component/SceneGraph/CIFXMotionResource.cpp
	RTL/Component/SceneGraph/CIFXNode.cpp
	RTL/Component/SceneGraph/CIFXResourceClient.cpp
	RTL/Component/SceneGraph/CIFXSceneGraph.cpp
	RTL/Component/SceneGraph/CIFXShaderList.cpp
	RTL/Component/SceneGraph/CIFXSimpleCollection.cpp
	RTL/Component/SceneGraph/CIFXSimpleList.cpp
	RTL/Component/SceneGraph/CIFXView.cpp
	RTL/Component/SceneGraph/CIFXViewResource.cpp
	RTL/Component/SceneGraph/IFXRenderPass.cpp
	RTL/Component/Shaders/CIFXShader.cpp
	RTL/Component/Shaders/CIFXShaderLitTexture.cpp
	RTL/Component/Shaders/CIFXShadingModifier.cpp
	RTL/Component/Subdiv/CIFXSubdivModifier.cpp
	RTL/Component/Subdiv/IFXAttributeNeighborhood.cpp
	RTL/Component/Subdiv/IFXButterflyScheme.cpp
	RTL/Component/Subdiv/IFXScreenSpaceMetric.cpp
	RTL/Component/Subdiv/IFXSharedUnitAllocator.cpp
	RTL/Component/Subdiv/IFXSubdivisionManager.cpp
	RTL/Component/Subdiv/IFXTQTAddress.cpp
	RTL/Component/Subdiv/IFXTQTAttribute.cpp
	RTL/Component/Subdiv/IFXTQTBaseTriangle.cpp
	RTL/Component/Subdiv/IFXTQTTriangleAllocator.cpp
	RTL/Component/Subdiv/IFXTQTTriangle.cpp
	RTL/Component/Subdiv/IFXVertexAllocator.cpp
	RTL/Component/Texture/CIFXImageTools.cpp
	RTL/Component/Texture/CIFXTextureImageTools.cpp
	RTL/Component/Texture/CIFXTextureObject.cpp
	RTL/Component/UVGenerator/CIFXUVGenerator.cpp
	RTL/Component/UVGenerator/CIFXUVMapperCylindrical.cpp
	RTL/Component/UVGenerator/CIFXUVMapperNone.cpp
	RTL/Component/UVGenerator/CIFXUVMapperPlanar.cpp
	RTL/Component/UVGenerator/CIFXUVMapperReflection.cpp
	RTL/Component/UVGenerator/CIFXUVMapperSpherical.cpp
	RTL/Dependencies/WildCards/wcmatch.cpp
	RTL/Dependencies/Predicates/predicates.cpp
)
SET( IFXCore_HDRS
	${Component_HDRS}
	${Platform_HDRS}
	RTL/Component/Base/IFXVectorHasher.h
	RTL/Component/BitStream/CIFXBitStreamX.h
	RTL/Component/BitStream/CIFXDataBlockQueueX.h
	RTL/Component/BitStream/CIFXDataBlockX.h
	RTL/Component/Bones/CIFXAnimationModifier.h
	RTL/Component/Bones/CIFXBoneWeightsModifier.h
	RTL/Component/Bones/CIFXSkeleton.h
	RTL/Component/Bones/IFXBoneCache.h
	RTL/Component/Bones/IFXBoneCacheArray.h
	RTL/Component/Bones/IFXBoneContext.h
	RTL/Component/Bones/IFXBoneLinks.h
	RTL/Component/Bones/IFXBoneNode.h
	RTL/Component/Bones/IFXBoneNodeList.h
	RTL/Component/Bones/IFXBonesManagerImpl.h
	RTL/Component/Bones/IFXCharacter.h
	RTL/Component/Bones/IFXConstraints.h
	RTL/Component/Bones/IFXCoreNode.h
	RTL/Component/Bones/IFXCylinder.h
	RTL/Component/Bones/IFXIKModes.h
	RTL/Component/Bones/IFXKeyFrameContext.h
	RTL/Component/Bones/IFXLong3.h
	RTL/Component/Bones/IFXMatrix3x4.h
	RTL/Component/Bones/IFXMeshGroup_Character.h
	RTL/Component/Bones/IFXMeshGroup_Impl.h
	RTL/Component/Bones/IFXMeshInterface.h
	RTL/Component/Bones/IFXMeshVertexMap.h
	RTL/Component/Bones/IFXMixerQueueImpl.h
	RTL/Component/Bones/IFXMotionManagerImpl.h
	RTL/Component/Bones/IFXMotionMixerImpl.h
	RTL/Component/Bones/IFXMotionReader.h
	RTL/Component/Bones/IFXPackWeights.h
	RTL/Component/Bones/IFXSkin.h
	RTL/Component/Bones/IFXVertexWeight.h
	RTL/Component/Bones/IFXVertexWeights.h
	RTL/Component/BoundHierarchy/CIFXAABBHierarchyBuilder.h
	RTL/Component/BoundHierarchy/CIFXAxisAlignedBBox.h
	RTL/Component/BoundHierarchy/CIFXBoundFace.h
	RTL/Component/BoundHierarchy/CIFXBoundHierarchy.h
	RTL/Component/BoundHierarchy/CIFXBoundUtil.h
	RTL/Component/BoundHierarchy/CIFXBTree.h
	RTL/Component/BoundHierarchy/CIFXBTreeNode.h
	RTL/Component/BoundHierarchy/CIFXCollisionResult.h
	RTL/Component/BoundHierarchy/CIFXPickObject.h
	RTL/Component/BoundHierarchy/CIFXPrimitiveOverlap.h
	RTL/Component/BoundHierarchy/CIFXResultAllocator.h
	RTL/Component/CLODAuthor/CIFXAuthorCLODGen.h
	RTL/Component/CLODAuthor/CIFXAuthorMeshMap.h
	RTL/Component/CLODAuthor/CIFXSetAdjacencyX.h
	RTL/Component/CLODAuthor/CIFXSetX.h
	RTL/Component/CLODAuthor/CLODGenerator.h
	RTL/Component/CLODAuthor/ContractionRecorder.h
	RTL/Component/CLODAuthor/CostMap.h
	RTL/Component/CLODAuthor/Face.h
	RTL/Component/CLODAuthor/FaceExam.h
	RTL/Component/CLODAuthor/FacePtrSet.h
	RTL/Component/CLODAuthor/FaceUpdate.h
	RTL/Component/CLODAuthor/GeometryObject.h
	RTL/Component/CLODAuthor/IFXSList.h
	RTL/Component/CLODAuthor/Matrix4x4.h
	RTL/Component/CLODAuthor/NormalMap.h
	RTL/Component/CLODAuthor/Pair.h
	RTL/Component/CLODAuthor/PairFinder.h
	RTL/Component/CLODAuthor/PairHash.h
	RTL/Component/CLODAuthor/PairHeap.h
	RTL/Component/CLODAuthor/Primitives.h
	RTL/Component/CLODAuthor/QEConstants.h
	RTL/Component/CLODAuthor/SmallPtrSet.h
	RTL/Component/CLODAuthor/Vertex.h
	RTL/Component/CLODAuthor/VertexPairContractor.h
	RTL/Component/Common/CIFXCoreServices.h
	RTL/Component/Common/CIFXCoreServicesRef.h
	RTL/Component/Common/CIFXHashMap.h
	RTL/Component/Common/CIFXIDManager.h
	RTL/Component/Common/CIFXMetaData.h
	RTL/Component/Common/CIFXNameMap.h
	RTL/Component/Common/CIFXSimpleHash.h
	RTL/Component/Common/CIFXVoidWrapper.h
	RTL/Component/Common/IFXComponentFactories.h
	RTL/Component/Generators/CLOD/CIFXAuthorCLODResource.h
	RTL/Component/Generators/CLOD/CIFXAuthorMesh.h
	RTL/Component/Generators/CLOD/CIFXAuthorMeshScrub.h
	RTL/Component/Generators/CLOD/CIFXCLODModifier.h
	RTL/Component/Generators/CLOD/CIFXMeshCompiler.h
	RTL/Component/Generators/CLOD/CIFXMeshMap.h
	RTL/Component/Generators/CLOD/IFXCLODManager.h
	RTL/Component/Generators/CLOD/IFXNeighborResController.h
	RTL/Component/Generators/Glyph2D/CIFXContour.h
	RTL/Component/Generators/Glyph2D/CIFXContourExtruder.h
	RTL/Component/Generators/Glyph2D/CIFXContourGenerator.h
	RTL/Component/Generators/Glyph2D/CIFXContourTessellator.h
	RTL/Component/Generators/Glyph2D/CIFXGeom2D.h
	RTL/Component/Generators/Glyph2D/CIFXGlyph2DCommands.h
	RTL/Component/Generators/Glyph2D/CIFXGlyph2DModifier.h
	RTL/Component/Generators/Glyph2D/CIFXGlyph3DGenerator.h
	RTL/Component/Generators/Glyph2D/CIFXGlyphCommandList.h
	RTL/Component/Generators/Glyph2D/CIFXQuadEdge.h
	RTL/Component/Generators/Glyph2D/IFXContour.h
	RTL/Component/Generators/Glyph2D/IFXContourExtruder.h
	RTL/Component/Generators/Glyph2D/IFXContourGenerator.h
	RTL/Component/Generators/Glyph2D/IFXContourTessellator.h
	RTL/Component/Generators/Glyph2D/IFXGlyph3DGenerator.h
	RTL/Component/Generators/LineSet/CIFXAuthorLineSet.h
	RTL/Component/Generators/LineSet/CIFXAuthorLineSetAnalyzer.h
	RTL/Component/Generators/LineSet/CIFXAuthorLineSetResource.h
	RTL/Component/Generators/PointSet/CIFXAuthorPointSet.h
	RTL/Component/Generators/PointSet/CIFXAuthorPointSetResource.h
	RTL/Component/Mesh/CIFXInterleavedData.h
	RTL/Component/Mesh/CIFXMesh.h
	RTL/Component/Mesh/CIFXMeshGroup.h
	RTL/Component/Mesh/CIFXNeighborMesh.h
	RTL/Component/Mesh/CIFXRenderable.h
	RTL/Component/Mesh/IFXFaceLists.h
	RTL/Component/ModifierChain/CIFXDidRegistry.h
	RTL/Component/ModifierChain/CIFXModifier.h
	RTL/Component/ModifierChain/CIFXModifierChain.h
	RTL/Component/ModifierChain/CIFXModifierDataElementIter.h
	RTL/Component/ModifierChain/CIFXModifierDataPacket.h
	RTL/Component/ModifierChain/CIFXObserverStateTree.h
	RTL/Component/ModifierChain/CIFXSubject.h
	RTL/Component/ModifierChain/CRedBlackTree.h
	RTL/Component/ModifierChain/IFXModifierChainInternal.h
	RTL/Component/ModifierChain/IFXModifierChainState.h
	RTL/Component/ModifierChain/IFXModifierDataPacketInternal.h
	RTL/Component/ModifierChain/IFXSet.h
	RTL/Component/Palette/CIFXPalette.h
	RTL/Component/Palette/CIFXSimpleObject.h
	RTL/Component/Rendering/CIFXDeviceBase.h
	RTL/Component/Rendering/CIFXDeviceLight.h
	RTL/Component/Rendering/CIFXDeviceTexture.h
	RTL/Component/Rendering/CIFXDeviceTexUnit.h
	RTL/Component/Rendering/CIFXRender.h
	RTL/Component/Rendering/CIFXRenderContext.h
	RTL/Component/Rendering/CIFXRenderDevice.h
	RTL/Component/Rendering/CIFXRenderServices.h
	RTL/Component/Rendering/DX7/CIFXDeviceLightDX7.h
	RTL/Component/Rendering/DX7/CIFXDeviceTextureDX7.h
	RTL/Component/Rendering/DX7/CIFXDeviceTexUnitDX7.h
	RTL/Component/Rendering/DX7/CIFXDirectX7.h
	RTL/Component/Rendering/DX7/CIFXRenderDeviceDX7.h
	RTL/Component/Rendering/DX7/CIFXRenderDX7.h
	RTL/Component/Rendering/DX7/IFXRenderPCHDX7.h
	RTL/Component/Rendering/DX8/CIFXDeviceLightDX8.h
	RTL/Component/Rendering/DX8/CIFXDeviceTextureDX8.h
	RTL/Component/Rendering/DX8/CIFXDeviceTexUnitDX8.h
	RTL/Component/Rendering/DX8/CIFXDirectX8.h
	RTL/Component/Rendering/DX8/CIFXRenderDeviceDX8.h
	RTL/Component/Rendering/DX8/CIFXRenderDX8.h
	RTL/Component/Rendering/DX8/IFXRenderPCHDX8.h
	RTL/Component/Rendering/IFXAAFilter.h
	RTL/Component/Rendering/IFXRenderPCH.h
	RTL/Component/Rendering/Null/CIFXDeviceLightNULL.h
	RTL/Component/Rendering/Null/CIFXDeviceTextureNULL.h
	RTL/Component/Rendering/Null/CIFXDeviceTexUnitNULL.h
	RTL/Component/Rendering/Null/CIFXRenderDeviceNULL.h
	RTL/Component/Rendering/Null/CIFXRenderNULL.h
	RTL/Component/Rendering/Null/IFXRenderPCHNULL.h
	RTL/Component/Rendering/OpenGL/CIFXDeviceLightOGL.h
	RTL/Component/Rendering/OpenGL/CIFXDeviceTextureOGL.h
	RTL/Component/Rendering/OpenGL/CIFXDeviceTexUnitOGL.h
	RTL/Component/Rendering/OpenGL/CIFXOpenGL.h
	RTL/Component/Rendering/OpenGL/CIFXRenderDeviceOGL.h
	RTL/Component/Rendering/OpenGL/CIFXRenderOGL.h
	RTL/Component/Rendering/OpenGL/IFXRenderPCHOGL.h
	RTL/Component/SceneGraph/CIFXBoundSphereDataElement.h
	RTL/Component/SceneGraph/CIFXDevice.h
	RTL/Component/SceneGraph/CIFXDummyModifier.h
	RTL/Component/SceneGraph/CIFXFileReference.h
	RTL/Component/SceneGraph/CIFXGroup.h
	RTL/Component/SceneGraph/CIFXLight.h
	RTL/Component/SceneGraph/CIFXLightResource.h
	RTL/Component/SceneGraph/CIFXLightSet.h
	RTL/Component/SceneGraph/CIFXMarker.h
	RTL/Component/SceneGraph/CIFXMaterialResource.h
	RTL/Component/SceneGraph/CIFXMixerConstruct.h
	RTL/Component/SceneGraph/CIFXModel.h
	RTL/Component/SceneGraph/CIFXMotionResource.h
	RTL/Component/SceneGraph/CIFXNode.h
	RTL/Component/SceneGraph/CIFXResourceClient.h
	RTL/Component/SceneGraph/CIFXSceneGraph.h
	RTL/Component/SceneGraph/CIFXShaderList.h
	RTL/Component/SceneGraph/CIFXSimpleCollection.h
	RTL/Component/SceneGraph/CIFXSimpleList.h
	RTL/Component/SceneGraph/CIFXView.h
	RTL/Component/SceneGraph/CIFXViewResource.h
	RTL/Component/SceneGraph/IFXSceneGraphPCH.h
	RTL/Component/Shaders/CIFXShader.h
	RTL/Component/Shaders/CIFXShaderLitTexture.h
	RTL/Component/Shaders/CIFXShadingModifier.h
	RTL/Component/Subdiv/CIFXSubdivModifier.h
	RTL/Component/Subdiv/IFXAttributeNeighborhood.h
	RTL/Component/Subdiv/IFXBFMaskLayout.h
	RTL/Component/Subdiv/IFXButterflyMask.h
	RTL/Component/Subdiv/IFXButterflyScheme.h
	RTL/Component/Subdiv/IFXScreenSpaceMetric.h
	RTL/Component/Subdiv/IFXSharedUnitAllocator.h
	RTL/Component/Subdiv/IFXSpecularMetric.h
	RTL/Component/Subdiv/IFXSubdivisionManager.h
	RTL/Component/Subdiv/IFXTQTAddress.h
	RTL/Component/Subdiv/IFXTQTAttribute.h
	RTL/Component/Subdiv/IFXTQTBaseTriangle.h
	RTL/Component/Subdiv/IFXTQTTriangle.h
	RTL/Component/Subdiv/IFXTQTTriangleAllocator.h
	RTL/Component/Subdiv/IFXTQTVertex.h
	RTL/Component/Subdiv/IFXVertexAllocator.h
	RTL/Component/Texture/CIFXImageTools.h
	RTL/Component/Texture/CIFXTextureImageTools.h
	RTL/Component/Texture/CIFXTextureObject.h
	RTL/Component/Texture/CIFXUtilities.h
	RTL/Component/Texture/IFXTextureErrors.h
	RTL/Component/UVGenerator/CIFXUVGenerator.h
	RTL/Component/UVGenerator/CIFXUVMapperCylindrical.h
	RTL/Component/UVGenerator/CIFXUVMapperNone.h
	RTL/Component/UVGenerator/CIFXUVMapperPlanar.h
	RTL/Component/UVGenerator/CIFXUVMapperReflection.h
	RTL/Component/UVGenerator/CIFXUVMapperSpherical.h
	RTL/Dependencies/FNVHash/FNVPlusPlus.h
	RTL/Dependencies/Predicates/predicates.h
	RTL/Dependencies/WildCards/wcmatch.h
)

SET( CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/RTL/Platform/Win32/IFXCore )
ADD_LIBRARY( IFXCore SHARED ${IFXCore_SRCS} ${IFXCore_HDRS} ${CORE_DIR}/IFXCore.rc ${CORE_DIR}/IFXResource.h ${CORE_DIR}/IFXCore.def ${DEPENDENCIES_SRCS} )

target_link_libraries(IFXCore
	PUBLIC
		Kernel
	PRIVATE
		ZLIB::ZLIB PNG::PNG JPEG::JPEG Winmm
)

INCLUDE_DIRECTORIES(
	RTL/Component/Include
    RTL/Platform/Include
	RTL/Component/Exporting
	RTL/Dependencies/WildCards )
SET( IFXExporting_HDRS
	${Component_HDRS}
	${Platform_HDRS}
	RTL/Component/Exporting/CIFXAnimationModifierEncoder.h
	RTL/Component/Exporting/CIFXAuthorCLODEncoderX.h
	RTL/Component/Exporting/CIFXAuthorGeomCompiler.h
	RTL/Component/Exporting/CIFXBlockPriorityQueueX.h
	RTL/Component/Exporting/CIFXBlockWriterX.h
	RTL/Component/Exporting/CIFXBoneWeightsModifierEncoder.h
	RTL/Component/Exporting/CIFXCLODModifierEncoder.h
	RTL/Component/Exporting/CIFXDummyModifierEncoder.h
	RTL/Component/Exporting/CIFXFileReferenceEncoder.h
	RTL/Component/Exporting/CIFXGlyphModifierEncoder.h
	RTL/Component/Exporting/CIFXGroupNodeEncoder.h
	RTL/Component/Exporting/CIFXLightNodeEncoder.h
	RTL/Component/Exporting/CIFXLightResourceEncoder.h
	RTL/Component/Exporting/CIFXLineSetEncoder.h
	RTL/Component/Exporting/CIFXMaterialResourceEncoder.h
	RTL/Component/Exporting/CIFXModelNodeEncoder.h
	RTL/Component/Exporting/CIFXMotionResourceEncoder.h
	RTL/Component/Exporting/CIFXNodeBaseEncoder.h
	RTL/Component/Exporting/CIFXPointSetEncoder.h
	RTL/Component/Exporting/CIFXShaderLitTextureEncoder.h
	RTL/Component/Exporting/CIFXShadingModifierEncoder.h
	RTL/Component/Exporting/CIFXStdioWriteBufferX.h
	RTL/Component/Exporting/CIFXSubdivisionModifierEncoder.h
	RTL/Component/Exporting/CIFXViewNodeEncoder.h
	RTL/Component/Exporting/CIFXViewResourceEncoder.h
	RTL/Component/Exporting/CIFXWriteManager.h
	RTL/Dependencies/WildCards/wcmatch.h
)
SET( IFXExporting_SRCS
	RTL/Platform/${U3D_PLATFORM}/IFXExporting/IFXExportingDllMain.cpp
	RTL/Component/Exporting/CIFXAnimationModifierEncoder.cpp
	RTL/Component/Exporting/CIFXAuthorCLODEncoderX.cpp
	RTL/Component/Exporting/CIFXAuthorCLODEncoderX_P.cpp
	RTL/Component/Exporting/CIFXAuthorCLODEncoderX_S.cpp
	RTL/Component/Exporting/CIFXAuthorGeomCompiler.cpp
	RTL/Component/Exporting/CIFXBlockPriorityQueueX.cpp
	RTL/Component/Exporting/CIFXBlockWriterX.cpp
	RTL/Component/Exporting/CIFXBoneWeightsModifierEncoder.cpp
	RTL/Component/Exporting/CIFXCLODModifierEncoder.cpp
	RTL/Component/Exporting/CIFXDummyModifierEncoder.cpp
	RTL/Component/Exporting/CIFXFileReferenceEncoder.cpp
	RTL/Component/Exporting/CIFXGlyphModifierEncoder.cpp
	RTL/Component/Exporting/CIFXGroupNodeEncoder.cpp
	RTL/Component/Exporting/CIFXLightNodeEncoder.cpp
	RTL/Component/Exporting/CIFXLightResourceEncoder.cpp
	RTL/Component/Exporting/CIFXLineSetEncoder.cpp
	RTL/Component/Exporting/CIFXMaterialResourceEncoder.cpp
	RTL/Component/Exporting/CIFXModelNodeEncoder.cpp
	RTL/Component/Exporting/CIFXMotionResourceEncoder.cpp
	RTL/Component/Exporting/CIFXNodeBaseEncoder.cpp
	RTL/Component/Exporting/CIFXPointSetEncoder.cpp
	RTL/Component/Exporting/CIFXShaderLitTextureEncoder.cpp
	RTL/Component/Exporting/CIFXShadingModifierEncoder.cpp
	RTL/Component/Exporting/CIFXStdioWriteBufferX.cpp
	RTL/Component/Exporting/CIFXSubdivisionModifierEncoder.cpp
	RTL/Component/Exporting/CIFXViewNodeEncoder.cpp
	RTL/Component/Exporting/CIFXViewResourceEncoder.cpp
	RTL/Component/Exporting/CIFXWriteManager.cpp
	RTL/Component/Exporting/IFXExporting.cpp
	RTL/Component/Exporting/IFXExportingGuids.cpp
	RTL/IFXCorePluginStatic/IFXCorePluginStatic.cpp
	RTL/Platform/${U3D_PLATFORM}/Common/IFXOSUtilities.cpp
	RTL/Platform/${U3D_PLATFORM}/Common/IFXOSLoader.cpp
	RTL/Component/Base/IFXVertexMap.cpp
	RTL/Dependencies/WildCards/wcmatch.cpp
)

SET( EXPORT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/RTL/Platform/Win32/IFXExporting )
ADD_LIBRARY( IFXExporting  SHARED ${IFXExporting_SRCS} ${IFXExporting_HDRS} ${EXPORT_DIR}/IFXExporting.rc ${EXPORT_DIR}/IFXResource.h ${EXPORT_DIR}/IFXExporting.def )
TARGET_LINK_LIBRARIES( IFXExporting IFXCore Winmm)


INCLUDE_DIRECTORIES( RTL/Component/Include
    RTL/Platform/Include
	RTL/Dependencies/WildCards
	RTL/Component/Base
	IDTF
	IDTF/Include
	IDTF/Common 
        libIDTF )
SET( libIDTF_SRCS
	libIDTF/SceneConverterLib.cpp
	libIDTF/Writer.cpp
	libIDTF/IFXOSLoader.cpp
	libIDTF/IFXOSUtilities.cpp
	IDTF/PointSetConverter.cpp
	IDTF/MetaDataConverter.cpp
	IDTF/ResourceConverter.cpp
	IDTF/TextureConverter.cpp
	IDTF/File.cpp
	IDTF/LineSetConverter.cpp
	IDTF/ModelConverter.cpp
	IDTF/NodeConverter.cpp
	IDTF/MeshConverter.cpp
	IDTF/FileReferenceConverter.cpp
	IDTF/ModifierConverter.cpp
	IDTF/Helpers/MiscUtilities.cpp
	IDTF/Helpers/TGAImage.cpp
	IDTF/Helpers/ModifierUtilities.cpp
	IDTF/Helpers/SceneUtilities.cpp
	IDTF/Helpers/DebugInfo.cpp
	IDTF/Helpers/Guids.cpp
	IDTF/Common/GlyphModifier.cpp
	IDTF/Common/ModelResource.cpp
	IDTF/Common/ModifierList.cpp
	IDTF/Common/NodeList.cpp
	IDTF/Common/FileReference.cpp
	IDTF/Common/ResourceList.cpp
	IDTF/Common/SceneResources.cpp
	IDTF/Common/ModelResourceList.cpp
	IDTF/Common/MetaDataList.cpp
	IDTF/Common/ParentList.cpp
	IDTF/Common/GlyphCommandList.cpp
	RTL/Dependencies/WildCards/wcmatch.cpp
	RTL/Component/Base/IFXCoincidentVertexMap.cpp
	RTL/Component/Base/IFXFatCornerIter.cpp
	RTL/Component/Base/IFXCornerIter.cpp
	RTL/Component/Base/IFXTransform.cpp
	RTL/Component/Base/IFXVertexMap.cpp
	RTL/Component/Base/IFXEuler.cpp
	RTL/Component/Base/IFXVectorHasher.cpp
	RTL/Component/Base/IFXVertexMapGroup.cpp
	RTL/Component/Common/IFXDids.cpp
	RTL/IFXCoreStatic/IFXCoreStatic.cpp
)
SET( libIDTF_HDRS
	${Component_HDRS}
	${Platform_HDRS}
	libIDTF/SceneConverterLib.h
	libIDTF/Writer.h
	IDTF/DefaultSettings.h
	IDTF/File.h
	IDTF/FileReferenceConverter.h
	IDTF/IConverter.h
	IDTF/LineSetConverter.h
	IDTF/MeshConverter.h
	IDTF/MetaDataConverter.h
	IDTF/ModelConverter.h
	IDTF/ModifierConverter.h
	IDTF/NodeConverter.h
	IDTF/PointSetConverter.h
	IDTF/ResourceConverter.h
	IDTF/TextureConverter.h
	IDTF/Include/ConverterOptions.h
	IDTF/Include/ConverterResult.h
	IDTF/Include/DebugInfo.h
	IDTF/Include/SceneUtilities.h
	IDTF/Include/TGAImage.h
	IDTF/Include/U3DHeaders.h
	IDTF/Common/AnimationModifier.h
	IDTF/Common/BoneWeightModifier.h
	IDTF/Common/CLODModifier.h
	IDTF/Common/Color.h
	IDTF/Common/FileReference.h
	IDTF/Common/GlyphCommandList.h
	IDTF/Common/GlyphCommands.h
	IDTF/Common/GlyphModifier.h
	IDTF/Common/INode.h
	IDTF/Common/Int2.h
	IDTF/Common/Int3.h
	IDTF/Common/IResource.h
	IDTF/Common/LightNode.h
	IDTF/Common/LightResource.h
	IDTF/Common/LightResourceList.h
	IDTF/Common/LineSetResource.h
	IDTF/Common/MaterialResource.h
	IDTF/Common/MaterialResourceList.h
	IDTF/Common/MeshResource.h
	IDTF/Common/MetaDataList.h
	IDTF/Common/ModelNode.h
	IDTF/Common/ModelResource.h
	IDTF/Common/ModelResourceList.h
	IDTF/Common/ModelSkeleton.h
	IDTF/Common/Modifier.h
	IDTF/Common/ModifierList.h
	IDTF/Common/MotionResource.h
	IDTF/Common/MotionResourceList.h
	IDTF/Common/Node.h
	IDTF/Common/NodeList.h
	IDTF/Common/ParentData.h
	IDTF/Common/ParentList.h
	IDTF/Common/Point.h
	IDTF/Common/PointSetResource.h
	IDTF/Common/Quat.h
	IDTF/Common/Resource.h
	IDTF/Common/ResourceList.h
	IDTF/Common/SceneData.h
	IDTF/Common/SceneResources.h
	IDTF/Common/ShaderResource.h
	IDTF/Common/ShaderResourceList.h
	IDTF/Common/ShadingDescription.h
	IDTF/Common/ShadingDescriptionList.h
	IDTF/Common/ShadingModifier.h
	IDTF/Common/SubdivisionModifier.h
	IDTF/Common/TextureResource.h
	IDTF/Common/TextureResourceList.h
	IDTF/Common/Tokens.h
	IDTF/Common/UrlList.h
	IDTF/Common/ViewNodeData.h
	IDTF/Common/ViewNode.h
	IDTF/Common/ViewResource.h
	IDTF/Common/ViewResourceList.h
	RTL/Dependencies/WildCards/wcmatch.h
	RTL/Component/Base/IFXVectorHasher.h
)

ADD_LIBRARY( IDTF STATIC ${libIDTF_SRCS} ${libIDTF_HDRS} )

target_compile_definitions(IDTF PRIVATE UNICODE _UNICODE)
target_link_libraries(IDTF PRIVATE Winmm Kernel)

SET_PROPERTY(
	TARGET IDTF
	PROPERTY COMPILE_DEFINITIONS LIBIDTF )
install(
	TARGETS IDTF
	ARCHIVE DESTINATION ${LIB_DESTINATION}
	LIBRARY DESTINATION ${LIB_DESTINATION}
)
ADD_EXECUTABLE( IDTFGen Samples/SampleCode/IDTFGen.cpp ${libIDTF_HDRS} )
target_link_libraries( IDTFGen  IDTF ${CMAKE_DL_LIBS} )

install(
	TARGETS IDTFGen 
	DESTINATION ${BIN_DESTINATION}
)
