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

#ifndef __CIFXGuidHashMap_H__
#define __CIFXGuidHashMap_H__


//***************************************************************************
//	Includes
//***************************************************************************

#include "IFXResultComponentEngine.h"
#include <unordered_map>

//***************************************************************************
//	Classes, structures and types
//***************************************************************************

struct IFXComponentDescriptor;

//#define IFXGUIDDEBUG
#define IFX_E_GUIDHASHMAP_ID_NOT_FOUND	MAKE_IFXRESULT_FAIL( IFXRESULT_COMPONENT_CORE_SERVICES, 0x00100 )

template <>
struct std::hash<IFXCID>
{
	std::size_t operator()(const IFXCID& k) const
	{
		// Who needs this to be good there are only <256 components
		return static_cast<std::size_t>(k.A) ^ (static_cast<std::size_t>(k.B) << 1);
	}
};

class CIFXGuidHashMap
{
public:

	CIFXGuidHashMap();
	~CIFXGuidHashMap();

	IFXRESULT Initialize(
				const U32 componentNumber, 
				const IFXComponentDescriptor* pComponentDescriptorList);
	IFXRESULT Find(const IFXCID& compID, 
				   const IFXComponentDescriptor** ppComponentDescriptor) const;

private:
	IFXRESULT Add(const IFXComponentDescriptor* pComponentDescriptor);

	std::unordered_map<IFXCID, const IFXComponentDescriptor*> m_hashTable;
};


#endif
