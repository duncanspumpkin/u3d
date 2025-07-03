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
  @file Guids.cpp

      This module defines ...
*/

//***************************************************************************
//  Includes
//***************************************************************************

#define IFX_INIT_GUID
#include "IFXGUID.h"

#include "U3DHeaders.h"

#include "IFXAuthorCLODAccess.h"
#include "IFXAuthorLineSetAccess.h"
#include "IFXAuthorLineSetAnalyzer.h"
#include "IFXAuthorPointSetAccess.h"
#include "IFXBTTHash.h"
#include "IFXBitStreamCompressedX.h"
#include "IFXBitStreamX.h"
#include "IFXBlockReaderX.h"
#include "IFXBoundHierarchyMgr.h"
#include "IFXConnection.h"
#include "IFXConnectionServer.h"
#include "IFXContour.h"
#include "IFXContourExtruder.h"
#include "IFXContourGenerator.h"
#include "IFXContourTessellator.h"
#include "IFXCoreServicesRef.h"
#include "IFXDataBlock.h"
#include "IFXDecoderChainX.h"
#include "IFXDecoderX.h"
#include "IFXDevice.h"
#include "IFXDidRegistry.h"
#include "IFXDummyModifier.h"
#include "IFXExportingCIDs.h"
#include "IFXExportingInterfaces.h"
#include "IFXExtensionDecoderX.h"
#include "IFXGlyph3DGenerator.h"
#include "IFXHashMap.h"
#include "IFXIDManager.h"
#include "IFXImportingCIDs.h"
#include "IFXInet.h"
#include "IFXLightSet.h"
#include "IFXMeshCompiler.h"
#include "IFXModifierChainInternal.h"
#include "IFXNeighborMesh.h"
#include "IFXObserver.h"
#include "IFXPerformanceTimer.h"
#include "IFXPickObject.h"
#include "IFXReadBufferX.h"
#include "IFXSetAdjacencyX.h"
#include "IFXSetX.h"
#include "IFXSimpleHash.h"
#include "IFXUVGenerator.h"
#include "IFXUVMapper.h"
#include "IFXVoidWrapper.h"
#include "IFXWriteBufferX.h"
