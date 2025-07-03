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
	@file	CIFXComponentName.cpp

			This module defines the CIFXGuidHashMap class.
*/


//***************************************************************************
//	Includes
//***************************************************************************

#include "IFXPlugin.h"
#include "CIFXGuidHashMap.h"
#include "IFXResultComponentEngine.h"

//***************************************************************************
//	Defines
//***************************************************************************


//***************************************************************************
//	Constants
//***************************************************************************


//***************************************************************************
//	Enumerations
//***************************************************************************


//***************************************************************************
//	Classes, structures and types
//***************************************************************************


//***************************************************************************
//	Global data
//***************************************************************************


//***************************************************************************
//	Local data
//***************************************************************************


//***************************************************************************
//	Local function prototypes
//***************************************************************************


//***************************************************************************
//	Public methods
//***************************************************************************

CIFXGuidHashMap::CIFXGuidHashMap()
{
}


CIFXGuidHashMap::~CIFXGuidHashMap()
{
}



IFXRESULT CIFXGuidHashMap::Initialize( 
							const U32 numComponents, 
							const IFXComponentDescriptor *pCompDescList )
{
	IFXRESULT result = IFX_OK;

	for (U32 c = 0; c < numComponents; c++)
	{
		// Not clear, cut and paste error or Add return code is ignored by design
		// comment out result to avoid warning and keep the existing functionality
		// IFXRESULT result = IFX_OK;
		/* result = */ Add( &pCompDescList[c] );
	}

	return result;
}


IFXRESULT CIFXGuidHashMap::Add( const IFXComponentDescriptor* pCompDesc )
{
	IFXRESULT result = IFX_OK;

	m_hashTable[*pCompDesc->pComponentId] = pCompDesc;
	
	return result;
}


IFXRESULT CIFXGuidHashMap::Find ( const IFXCID& compID, const IFXComponentDescriptor** ppCompDesc) const
{
	IFXRESULT result = IFX_OK;
	
	auto res = m_hashTable.find(compID);
	if (res == m_hashTable.end()) {
		result = IFX_E_GUIDHASHMAP_ID_NOT_FOUND;
	}
	else {
		*ppCompDesc = res->second;
	}
	return result;
}


//***************************************************************************
//	Protected methods
//***************************************************************************


//***************************************************************************
//	Private methods
//***************************************************************************


//***************************************************************************
//	Global functions
//***************************************************************************


//***************************************************************************
//	Local functions
//***************************************************************************


