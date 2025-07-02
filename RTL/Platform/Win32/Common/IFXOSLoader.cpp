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
	@file	IFXOSLoader.cpp

			This module contains the Windows specific functions required to
			work with dynamically liked library.
*/

//***************************************************************************
//	Includes
//***************************************************************************

#include "IFXOSLoader.h"
#include <wtypes.h>

#if __MINGW32__
#define swprintf _snwprintf
#endif

//***************************************************************************
//	Local data
//***************************************************************************

const U32 MAXPATHLEN = 512;

//***************************************************************************
//	Global functions
//***************************************************************************

extern "C"
FILE* IFXAPI IFXOSFileOpen(const wchar_t *filename, const wchar_t *mode)
{
	FILE *pFile = NULL;

#ifdef STDIO_HACK
	if (!wcscmp(filename,"stdin") || (!wcscmp(filename,"-")  && *mode=='r')) {
		pFile = stdin;
	} else if (!wcscmp(filename,"stdout") || (!wcscmp(filename,"-")  && *mode=='w')) {
		pFile = stdout;
		_setmode(_fileno(stdout),_O_BINARY);
	} else {
		pFile = _wfopen(filename, mode);
	}
#else
	pFile = _wfopen(filename, mode);
#endif

	return pFile;
}
