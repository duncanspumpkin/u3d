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
	@file	IFXOSLoader.h

			This module provides all required functionality to work with dynamic
			libraries and their analogs.

	@note	Do not put any OS specific includes or types in this header!
*/

#ifndef IFXOSLoader_H
#define IFXOSLoader_H

#include "IFXAPI.h"
#include "IFXResult.h"
#include "IFXString.h"

/**
	Pointer to a function obtained from the dynamically linked library.
*/
typedef IFXRESULT (*IFXOSFUNC)();

/**
	Parameters
		filename 
			Filename. 
		mode 
			Type of access permitted. 

	Return a pointer to the open file. A null pointer value indicates an error.
*/
extern "C"
FILE* IFXAPI IFXOSFileOpen(const wchar_t *filename, const wchar_t *mode);

#endif

