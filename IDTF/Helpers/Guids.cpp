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

#include "IFXIDManager.h"
#include "IFXObserver.h"
#include "IFXLightSet.h"
#include "IFXBitStreamX.h"
#include "IFXDecoderX.h"
#include "IFXPickObject.h"
#include "IFXContour.h"
#include "IFXContourExtruder.h"
#include "IFXContourTessellator.h"
#include "IFXGlyph3DGenerator.h"
#include "IFXContourGenerator.h"
#include "IFXNeighborMesh.h"
#include "IFXAuthorCLODAccess.h"
#include "IFXConnection.h"
#include "IFXConnectionServer.h"
#include "IFXBitStreamCompressedX.h"
#include "IFXDataBlock.h"
#include "IFXReadBufferX.h"
#include "IFXWriteBufferX.h"
#include "IFXDidRegistry.h"
#include "IFXCoreServicesRef.h"
#include "IFXPerformanceTimer.h"
#include "IFXSimpleHash.h"
#include "IFXBoundHierarchyMgr.h"
#include "IFXVoidWrapper.h"
#include "IFXHashMap.h"
#include "IFXInet.h"
#include "IFXModifierChainInternal.h"
#include "IFXAuthorLineSetAccess.h"
#include "IFXAuthorPointSetAccess.h"
#include "IFXMeshCompiler.h"
#include "IFXDevice.h"
#include "IFXUVGenerator.h"
#include "IFXDummyModifier.h"
#include "IFXUVMapper.h"
#include "IFXSetX.h"
#include "IFXSetAdjacencyX.h"
#include "IFXAuthorLineSetAnalyzer.h"
#include "IFXExportingInterfaces.h"
#include "IFXExportingCIDs.h"
