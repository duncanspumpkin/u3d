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
	@file	CIFXComponentManager.cpp

			This module defines the CIFXComponentManager class. It is used to
			manage all operations with components and component database.
*/

//***************************************************************************
//	Includes
//***************************************************************************

#include "CIFXComponentManager.h"
#include "CIFXGuidHashMap.h"
#include "IFXPlugin.h"
#include "IFXCOM.h"

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

extern IFXComponentDescriptor g_coreComponentDescriptorList[];
extern U32 g_coreComponentNumber;

//***************************************************************************
//	Local data
//***************************************************************************


//***************************************************************************
//	Local function prototypes
//***************************************************************************


//***************************************************************************
//	Public methods
//***************************************************************************

CIFXComponentManager::CIFXComponentManager()
{
	m_refCount = 0;
	m_pGuidHashMap = NULL;
}

CIFXComponentManager::~CIFXComponentManager()
{
	if( NULL != m_pGuidHashMap )
		delete m_pGuidHashMap;
	m_pGuidHashMap = NULL;
}

U32 CIFXComponentManager::AddRef()
{
	return ++m_refCount;
}

U32 CIFXComponentManager::Release()
{
	if(!(--m_refCount))
	{
		delete this;
		return 0;
	}
	return m_refCount;
}

IFXRESULT CIFXComponentManager::Initialize()
{
	IFXRESULT result = IFX_OK;

	if ( NULL != m_pGuidHashMap)
	{
		delete m_pGuidHashMap;
	}

	m_pGuidHashMap = new CIFXGuidHashMap;

	if ( NULL != m_pGuidHashMap)
	{
		// initialize component database and register core components
		result = m_pGuidHashMap->Initialize( g_coreComponentNumber,
											 g_coreComponentDescriptorList);
	}
	else
		result = IFX_E_OUT_OF_MEMORY;

	return result;
}

IFXRESULT CIFXComponentManager::CreateComponent( const IFXCID& rComponentId, 
												 const IFXIID& rInterfaceId, 
												 void** ppInterface)
{
	IFXRESULT result = IFX_OK;

	if( NULL != m_pGuidHashMap )
	{
		const IFXComponentDescriptor* pComponentDescriptor;

		result = m_pGuidHashMap->Find( rComponentId, &pComponentDescriptor );

		if( IFXSUCCESS(result) )
		{
			if( NULL != pComponentDescriptor->pFactoryFunction )
			{
				// creation request for core/client component
				// or for loaded plug-in components
				if (pComponentDescriptor->Version >= 0)
					result = (pComponentDescriptor->pFactoryFunction)
								(rInterfaceId, ppInterface);
				else
					result = (pComponentDescriptor->pCLIFactoryFunction)
								(rComponentId, rInterfaceId, ppInterface);
			}
			else {
				result = IFX_E_COMPONENT;
			}
		}
		else
			result = IFX_E_COMPONENT;
	}
	else
		result = IFX_E_NOT_INITIALIZED;

	return result;
}

//***************************************************************************
//	Private methods
//***************************************************************************


//***************************************************************************
//	Global functions
//***************************************************************************


//***************************************************************************
//	Local functions
//***************************************************************************
