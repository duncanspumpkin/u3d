//***************************************************************************
//
//  Copyright (c) 1999 - 2006 Intel Corporation
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//***************************************************************************

/**
	@file	IFXComponentDescriptorList.cpp

			This module contains the component descriptors for the Core DL.
*/


//***************************************************************************
//  Includes
//***************************************************************************


#include "IFXComponentFactories.h"
#include "IFXCoreCIDs.h"
#include "IFXExportingCIDs.h"
#include "IFXImportingCIDs.h"

extern IFXRESULT IFXAPI_CALLTYPE CIFXAuthorGeomCompiler_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXAuthorCLODEncoderX_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXMaterialResourceEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXMotionResourceEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXGlyphGeneratorEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXShaderLitTextureEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXSubdivisionModifierEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXShadingModifierEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXAnimationModifierEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXGroupNodeEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXLightNodeEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXLightResourceEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXModelNodeEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXViewNodeEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXViewResourceEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXFileReferenceEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXBlockPriorityQueueX_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXBlockWriterX_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXWriteManager_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXStdioWriteBufferX_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXPointSetEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXLineSetEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXBoneWeightsModifierEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXCLODModifierEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXDummyModifierEncoder_Factory(IFXREFIID interfaceId, void** ppInterface);

extern IFXRESULT IFXAPI_CALLTYPE CIFXAuthorCLODDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXGroupDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXLightDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXLightResourceDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXMaterialDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXModelDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXAnimationModifierDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXMotionDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXGlyphGeneratorDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXShaderLitTextureDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXTextureDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXSubdivisionModifierDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXShadingModifierDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXDecoderChainX_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXViewResourceDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXViewDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXBlockReaderX_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXBTTHash_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXLoadManager_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXNameMap_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXStdioReadBufferX_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXInternetReadBufferX_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXPointSetDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXLineSetDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXBoneWeightsModifierDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXCLODModifierDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);
extern IFXRESULT IFXAPI_CALLTYPE CIFXDummyModifierDecoder_Factory(IFXREFIID interfaceId, void** ppInterface);

//***************************************************************************
//  Global data
//***************************************************************************


/**
	List of IFXComponentDescriptor structures for each IFXCOM component
	exposed by the DL.
*/
IFXComponentDescriptor g_coreComponentDescriptorList[] =
{
	{
		&CID_IFXNameMap,
		{CIFXNameMap_Factory},
		1
	},
	{
		&CID_IFXAuthorMeshMap,
		{CIFXAuthorMeshMap_Factory},
		1
	},
	{
		&CID_IFXCLODManager,
		{CIFXCLODManager_Factory},
		1
	},
	{
		&CID_IFXAuthorLineSetAnalyzer,
		{CIFXAuthorLineSetAnalyzer_Factory},
		1
	},
	{
		&CID_IFXMeshCompiler,
		{CIFXMeshCompiler_Factory},
		1
	},
	{
		&CID_IFXMeshMap,
		{CIFXMeshMap_Factory},
		1
	},
	{
		&CID_IFXAuthorCLODGen,
		{CIFXAuthorCLODGen_Factory},
		1
	},
	{
		&CID_IFXSetAdjacencyX,
		{CIFXSetAdjacencyX_Factory},
		1
	},
	{
		&CID_IFXSetX,
		{CIFXSetX_Factory},
		1
	},
	{
		&CID_IFXGlyph3DGenerator,
		{CIFXGlyph3DGenerator_Factory},
		1
	},
	{
		&CID_IFXGlyphCommandList,
		{CIFXGlyphCommandList_Factory},
		1
	},
	{
		&CID_IFXAuthorMesh,
		{CIFXAuthorMesh_Factory},
		1
	},
	{
		&CID_IFXAuthorCLODResource,
		{CIFXAuthorCLODResource_Factory},
		1
	},
	{
		&CID_IFXAuthorMeshScrub,
		{CIFXAuthorMeshScrub_Factory}, 1
	},
	{
		&CID_IFXBitStreamX,
		{CIFXBitStreamX_Factory}, 1
	},
	{
		&CID_IFXFileReference,
		{CIFXFileReference_Factory}, 1
	},
	{
		&CID_IFXBoundHierarchy,
		{CIFXBoundHierarchy_Factory}, 1
	},
	{
		&CID_IFXSkeleton,
		{CIFXSkeleton_Factory}, 1
	},
	{
		&CID_IFXBoneWeightsModifier,
		{CIFXBoneWeightsModifier_Factory}, 1
	},
	{
		&CID_IFXBoundSphereDataElement,
		{CIFXBoundSphereDataElement_Factory}, 1
	},
	{
		&CID_IFXAuthorLineSet,
		{CIFXAuthorLineSet_Factory},1
	},
	{
		&CID_IFXAuthorLineSetResource,
		{CIFXAuthorLineSetResource_Factory},1
	},
	{
		&CID_IFXAuthorPointSet,
		{CIFXAuthorPointSet_Factory},1
	},
	{
		&CID_IFXAuthorPointSetResource,
		{CIFXAuthorPointSetResource_Factory},1
	},
	{
		&CID_IFXConnector,
		{CIFXConnector_Factory}, 1
	},
	{
		&CID_IFXContour,
		{CIFXContour_Factory}, 1
	},
	{
		&CID_IFXContourExtruder,
		{CIFXContourExtruder_Factory}, 1
	},
	{
		&CID_IFXContourGenerator,
		{CIFXContourGenerator_Factory}, 1
	},
	{
		&CID_IFXContourTessellator,
		{CIFXContourTessellator_Factory}, 1
	},
	{
		&CID_IFXCoreServices,
		{CIFXCoreServices_Factory}, 1
	},
	{
		&CID_IFXCoreServicesRef,
		{CIFXCoreServicesRef_Factory}, 1
	},
	{
		&CID_IFXDataBlock,
		{CIFXDataBlockX_Factory}, 1
	},
	{
		&CID_IFXDataBlockX,
		{CIFXDataBlockX_Factory}, 1
	},
	{
		&CID_IFXDataBlockQueueX,
		{CIFXDataBlockQueueX_Factory}, 1
	},
	{
		&CID_IFXModifierDataPacket,
		{CIFXModifierDataPacket_Factory}, 1
	},
	{
		&CID_IFXDevice,
		{CIFXDevice_Factory}, 1
	},
	{
		&CID_IFXGlyphCurveToBlock,
		{CIFXCurveToBlock_Factory}, 1
	},
	{
		&CID_IFXGlyphLineToBlock,
		{CIFXGlyphLineToBlock_Factory}, 1
	},
	{
		&CID_IFXGlyphMoveToBlock,
		{CIFXGlyphMoveToBlock_Factory}, 1
	},
	{
		&CID_IFXGlyphTagBlock,
		{CIFXGlyphTagBlock_Factory}, 1
	},
	{
		&CID_IFXGroup,
		{CIFXGroup_Factory}, 1
	},
	{
		&CID_IFXHashMap,
		{CIFXHashMap_Factory}, 1
	},
	{
		&CID_IFXIDManager,
		{CIFXIDManagerFactory}, 1
	},
	{
		&CID_IFXImageCodec,
		{CIFXImageTools_Factory}, 1
	},
	{
		&CID_IFXLight,
		{CIFXLight_Factory}, 1
	},
	{
		&CID_IFXLightResource,
		{CIFXLightResource_Factory}, 1
	},
	{
		&CID_IFXViewResource,
		{CIFXViewResource_Factory}, 1
	},
	{
		&CID_IFXLightSet,
		{CIFXLightSet_Factory}, 1
	},
	{
		&CID_IFXMesh,
		{CIFXMeshFactory}, 1
	},
	{
		&CID_IFXMeshGroup,
		{CIFXMeshGroupFactory},1 
	},
	{
		&CID_IFXMetaDataX,
		{CIFXMetaData_Factory}, 1
	},
	{
		&CID_IFXInterleavedData,
		{CIFXInterleavedDataFactory}, 1
	},
	{
		&CID_IFXNeighborMesh,
		{CIFXNeighborMeshFactory}, 1
	},
	{
		&CID_IFXCLODModifier,
		{CIFXCLODModifier_Factory}, 1
	},
	{
		&CID_IFXMixerConstruct,
		{CIFXMixerConstruct_Factory}, 1
	},
	{
		&CID_IFXModifierChain,
		{CIFXModifierChain_Factory}, 1
	},
	{
		&CID_IFXShaderList,
		{CIFXShaderList_Factory}, 1
	},
	{
		&CID_IFXMaterialResource,
		{CIFXMaterialResource_Factory}, 1
	},
	{
		&CID_IFXModel,
		{CIFXModel_Factory}, 1
	},
	{
		&CID_IFXGlyph2DModifier,
		{CIFXGlyph2DModifier_Factory}, 1
	},
	{
		&CID_IFXMotionResource,
		{CIFXMotionResource_Factory}, 1
	},
	{
		&CID_IFXPalette,
		{CIFXPalette_Factory}, 1
	},
	{
		&CID_IFXPerformanceTimer,
		{CIFXPerformanceTimer_Factory}, 1
	},
	{
		&CID_IFXPickObject,
		{CIFXPickObject_Factory}, 1
	},
	{
		&CID_IFXSimpleHash,
		{CIFXSimpleHashFactory},1
	},
	{
		&CID_IFXSimpleList,
		{CIFXSimpleList_Factory}, 1
	},
	{
		&CID_IFXSimpleObject,
		{CIFXSimpleObject_Factory}, 1
	},
	{
		&CID_IFXSceneGraph,
		{CIFXSceneGraph_Factory}, 1
	},
	{
		&CID_IFXAnimationModifier,
		{CIFXAnimationModifier_Factory}, 1
	},
	{
		&CID_IFXSimpleCollection,
		{CIFXSimpleCollection_Factory}, 1
	},
	{
		&CID_IFXSubdivModifier,
		{CIFXSubdivModifier_Factory}, 1
	},
	{
		&CID_IFXTextureImageTools,
		{CIFXTextureImageTools_Factory}, 1
	},
	{
		&CID_IFXTextureObject,
		{CIFXTextureObject_Factory}, 1
	},
	{
		&CID_IFXUVGenerator,
		{CIFXUVGenerator_Factory}, 1
	},
	{
		&CID_IFXUVMapperCylindrical,
		{CIFXUVMapperCylindrical_Factory}, 1
	},
	{
		&CID_IFXUVMapperNone,
		{CIFXUVMapperNone_Factory}, 1
	},
	{
		&CID_IFXUVMapperPlanar,
		{CIFXUVMapperPlanar_Factory}, 1
	},
	{
		&CID_IFXUVMapperSpherical,
		{CIFXUVMapperSpherical_Factory}, 1
	},
	{
		&CID_IFXUVMapperReflection,
		{CIFXUVMapperReflection_Factory}, 1
	},
	{
		&CID_IFXView,
		{CIFXView_Factory}, 1
	},
	{
		&CID_IFXVoidWrapper,
		{CIFXVoidWrapper_Factory}, 1
	},
	{
		&CID_IFXDidRegistry,
		{CIFXDidRegistry_Factory}, 1
	},
	{
		&CID_IFXShadingModifier,
		{CIFXShadingModifier_Factory}, 1
	},
	{
		&CID_IFXDummyModifier,
		{CIFXDummyModifier_Factory}, 1
	},
	{
		&CID_IFXShaderLitTexture,
		{CIFXShaderLitTexture_Factory}, 1
	},
			{
		&CID_IFXAuthorCLODEncoderX,
		{CIFXAuthorCLODEncoderX_Factory},
		1
			},
	{
		&CID_IFXAnimationModifierEncoder,
		{CIFXAnimationModifierEncoder_Factory},
		1
	},
	{
		&CID_IFXMaterialResourceEncoder,
		{CIFXMaterialResourceEncoder_Factory},
		1
	},
	{
		&CID_IFXMotionResourceEncoder,
		{CIFXMotionResourceEncoder_Factory},
		1
	},
	{
		&CID_IFXGlyphGeneratorEncoder,
		{CIFXGlyphGeneratorEncoder_Factory},
		1
	},
	{
		&CID_IFXShaderLitTextureEncoder,
		{CIFXShaderLitTextureEncoder_Factory},
		1
	},
	{
		&CID_IFXSubdivisionModifierEncoder,
		{CIFXSubdivisionModifierEncoder_Factory},
		1
	},
	{
		&CID_IFXShadingModifierEncoder,
		{CIFXShadingModifierEncoder_Factory},
		1
	},
	{
		&CID_IFXGroupNodeEncoder,
		{CIFXGroupNodeEncoder_Factory},
		1
	},
	{
		&CID_IFXLightNodeEncoder,
		{CIFXLightNodeEncoder_Factory},
		1
	},
	{
		&CID_IFXLightResourceEncoder,
		{CIFXLightResourceEncoder_Factory},
		1
	},
	{
		&CID_IFXViewResourceEncoder,
		{CIFXViewResourceEncoder_Factory},
		1
	},
	{
		&CID_IFXModelNodeEncoder,
		{CIFXModelNodeEncoder_Factory},
		1
	},
	{
		&CID_IFXViewNodeEncoder,
		{CIFXViewNodeEncoder_Factory},
		1
	},
	{
		&CID_IFXFileReferenceEncoder,
		{CIFXFileReferenceEncoder_Factory},
		1
	},
	{
		&CID_IFXBlockPriorityQueueX,
		{CIFXBlockPriorityQueueX_Factory},
		1
	},
	{
		&CID_IFXBlockWriterX,
		{CIFXBlockWriterX_Factory},
		1
	},
	{
		&CID_IFXWriteManager,
		{CIFXWriteManager_Factory},
		1
	},
	{
		&CID_IFXAuthorGeomCompiler,
		{CIFXAuthorGeomCompiler_Factory},
		1
	},
	{
		&CID_IFXStdioWriteBuffer,
		{CIFXStdioWriteBufferX_Factory},
		1
	},
	{
		&CID_IFXStdioWriteBufferX,
		{CIFXStdioWriteBufferX_Factory},
		1
	},
	{
		&CID_IFXPointSetEncoder,
		{CIFXPointSetEncoder_Factory},
		1
	},
	{
		&CID_IFXLineSetEncoderX,
		{CIFXLineSetEncoder_Factory},
		1
	},
	{
		&CID_IFXBoneWeightsModifierEncoder,
		{CIFXBoneWeightsModifierEncoder_Factory},
		1
	},
	{
		&CID_IFXCLODModifierEncoder,
		{CIFXCLODModifierEncoder_Factory},
		1
	},
	{
		&CID_IFXDummyModifierEncoder,
		{CIFXDummyModifierEncoder_Factory},
		1
	},
			{
		&CID_IFXAuthorCLODDecoder,
		{CIFXAuthorCLODDecoder_Factory},
		1
			},
	{
		&CID_IFXGroupDecoder,
		{CIFXGroupDecoder_Factory},
		1
	},
	{
		&CID_IFXLightDecoder,
		{CIFXLightDecoder_Factory},
		1
	},
	{
		&CID_IFXLightResourceDecoder,
		{CIFXLightResourceDecoder_Factory},
			1
	},
	{
		&CID_IFXViewResourceDecoder,
		{CIFXViewResourceDecoder_Factory},
		1
	},
	{
		&CID_IFXMaterialDecoder,
		{CIFXMaterialDecoder_Factory},
		1
	},
	{
		&CID_IFXModelDecoder,
		{CIFXModelDecoder_Factory},
		1
	},
	{
		&CID_IFXAnimationModifierDecoder,
		{CIFXAnimationModifierDecoder_Factory},
		1
	},
	{
		&CID_IFXMotionDecoder,
		{CIFXMotionDecoder_Factory},
		1
	},
	{
		&CID_IFXGlyphGeneratorDecoder,
		{CIFXGlyphGeneratorDecoder_Factory},
			1
	},
	{
		&CID_IFXShaderLitTextureDecoder,
		{CIFXShaderLitTextureDecoder_Factory},
		1
	},
	{
		&CID_IFXTextureDecoder,
		{CIFXTextureDecoder_Factory},
		1
	},
	{
		&CID_IFXSubdivisionModifierDecoder,
		{CIFXSubdivisionModifierDecoder_Factory},
		1
	},
	{
		&CID_IFXShadingModifierDecoder,
		{CIFXShadingModifierDecoder_Factory},
			1
	},
	{
		&CID_IFXDecoderChainX,
		{CIFXDecoderChainX_Factory},
			1
	},
	{
		&CID_IFXViewDecoder,
			{CIFXViewDecoder_Factory},
			1
	},
	{
		&CID_IFXBlockReaderX,
			{CIFXBlockReaderX_Factory},
			1
	},
	{
		&CID_IFXBTTHash,
		{CIFXBTTHash_Factory},
			1
	},
	{
		&CID_IFXLoadManager,
		{CIFXLoadManager_Factory},
			1
	},
	{
		&CID_IFXStdioReadBuffer,
		{CIFXStdioReadBufferX_Factory},
			1
	},
	{
		&CID_IFXStdioReadBufferX,
		{CIFXStdioReadBufferX_Factory},
			1
	},
	{
		&CID_IFXInternetReadBuffer,
			{CIFXInternetReadBufferX_Factory},
			1
	},
	{
		&CID_IFXInternetReadBufferX,
			{CIFXInternetReadBufferX_Factory},
			1
	},
	{
		&CID_IFXPointSetDecoder,
			{CIFXPointSetDecoder_Factory},
			1
	},
	{
		&CID_IFXLineSetDecoder,
			{CIFXLineSetDecoder_Factory},
			1
	},
	{
		&CID_IFXBoneWeightsModifierDecoder,
			{CIFXBoneWeightsModifierDecoder_Factory},
			1
	},
	{
		&CID_IFXCLODModifierDecoder,
			{CIFXCLODModifierDecoder_Factory},
			1
	},
	{
		&CID_IFXDummyModifierDecoder,
		{CIFXDummyModifierDecoder_Factory},
		1
	}
};

/**
	Count of the number of IFXComponentDescriptor structures contained in
	gsComponentDescriptorList.
*/
U32 g_coreComponentNumber =
  sizeof( g_coreComponentDescriptorList ) / sizeof( IFXComponentDescriptor );
