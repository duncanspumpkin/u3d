//***************************************************************************
//
//  Copyright (c) 2000 - 2006 Intel Corporation
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
//
//  DESCRIPTION
//    This file contains the implementation of the class for a dynamic sparse
//      Histogram object.
//*****************************************************************************

#include <memory.h>
#include "IFXException.h"
#include "IFXHistogramDynamic.h"
#include "IFXOSUtilities.h"

const U32 IFXHistogramDynamic::m_uMaximumSymbolInHistogram = 0x0000FFFF;

// Constructor
IFXHistogramDynamic::IFXHistogramDynamic(U32 uElephant)
{
  m_uOptimizationMode = IFXOSCheckCPUFeature(IFXCPUFeature_SSE2) ? IFXOptimization_SSE2 : IFXOSCheckCPUFeature(IFXCPUFeature_MMX) ? IFXOptimization_MMX : 0;
  m_uNumSymbols = 100;
  m_pu16RawSymbolCount = new U16[m_uNumSymbols + 8];
  m_pu16RawCumulativeCount4 = new U16[(m_uNumSymbols>>2)+9];
  m_pu16SymbolCount = m_pu16RawSymbolCount ;
  // Align the pointers on 16 byte boundary
  while((UPTR)m_pu16SymbolCount & (UPTR)0x0000000Fu) {
    m_pu16SymbolCount+=2;
  }
  m_pu16CumulativeCount4 = m_pu16RawCumulativeCount4;
  while((UPTR)m_pu16CumulativeCount4 & (UPTR)0x0000000Fu) {
    m_pu16CumulativeCount4+=2;
  }

  IFXASSERT(m_pu16SymbolCount);
  IFXASSERT(m_pu16CumulativeCount4);
  // If the new fails, the pointer will be NULL
  // The pointers should be checked for NULL before use
  if(m_pu16SymbolCount && m_pu16CumulativeCount4) {
    memset(m_pu16SymbolCount,0,sizeof(U16)*m_uNumSymbols);
    memset(m_pu16CumulativeCount4,0,sizeof(U16)*((m_uNumSymbols>>2)+1));
    m_pu16SymbolCount[0] = 1;
    m_pu16CumulativeCount4[0] = 1;
  } else {
    m_uNumSymbols = 0;
  }
  m_uElephant = uElephant;
}

// Destructor
IFXHistogramDynamic::~IFXHistogramDynamic()
{
  IFXDELETE_ARRAY(m_pu16RawSymbolCount);
  IFXDELETE_ARRAY(m_pu16RawCumulativeCount4);
}


// Symbol / Frequency conversion methods
// GetSymbolFreq - Returns the approximate occurence count of this symbol
U32 IFXHistogramDynamic::GetSymbolFreq(U32 symbol)
{
  U32 uCount = 0;

  if(m_pu16SymbolCount) {
    if(symbol < m_uNumSymbols) {
      uCount = (U32) m_pu16SymbolCount[symbol];
    } // else { uCount = 0; }
  }
  return uCount;
}

// GetCumSymbolFreq - Returns the sum of all symbol freqs for symbols less than the given symbol
U32 IFXHistogramDynamic::GetCumSymbolFreq(U32 symbol)
{
  U32 uCumSymbolFreq4 = 1;

  if(m_pu16CumulativeCount4 && m_pu16SymbolCount) {
    if(symbol <= m_uNumSymbols) {
      U32 uCount4 = (U32) m_pu16CumulativeCount4[symbol>>2];
      uCumSymbolFreq4 = ((U32)m_pu16CumulativeCount4[0]) - uCount4;
      U32 i;
      for(i= (symbol & -4 ); (i < symbol); i++) {
        uCumSymbolFreq4 += (U32) m_pu16SymbolCount[i];
      }
    } else {
      uCumSymbolFreq4 = ((U32)m_pu16CumulativeCount4[0]);
    }

  }
  return uCumSymbolFreq4;
}

// GetTotalSymbolFreq - Returns the approximate occurence count of all symbols
U32 IFXHistogramDynamic::GetTotalSymbolFreq()
{
  U32 uTotalSymbolFreq4 = 1;

  if(m_pu16CumulativeCount4) {
    uTotalSymbolFreq4 = (U32) m_pu16CumulativeCount4[0];
  }
  return uTotalSymbolFreq4;
}

// GetSymbolFromFreq - Return the symbol that corresponds to the given cumulative frequency
U32 IFXHistogramDynamic::GetSymbolFromFreq(U32 uCumulativeFrequency)
{
  U32 uSymbol4 = 0;

  if(m_pu16CumulativeCount4) {
    U32 uTotalCumulativeCount4 = (U32) m_pu16CumulativeCount4[0];
    if(uCumulativeFrequency < (U32) uTotalCumulativeCount4) {
      U32 uLow = 0;
      U32 uHigh = (m_uNumSymbols>>2);
      U16 *pu16Temp = m_pu16CumulativeCount4;
      while ((uHigh - uLow) > 4) {
        //U32 mid = (low + high) / 2;
        U32 mid = (uLow + uLow + uLow + uHigh) >> 2;
        //U32 mid = (((low + high)<< 2) + low - high) >> 3;
        if(uCumulativeFrequency >= (uTotalCumulativeCount4 - (U32) pu16Temp[mid])) {
          uLow = mid;
        } else {
          uHigh = mid;
        }
      }

      uLow <<=2;
      uHigh <<=2;
      uHigh += 3;

      while ((uHigh - uLow) > 4) {
        U32 mid = (uLow + uHigh) / 2;
        //U32 mid = (low + low + low + high) >> 2;
        //U32 mid = (((low + high)<< 2) + low - high) >> 3;
        if(uCumulativeFrequency >= IFXHistogramDynamic::GetCumSymbolFreq(mid) ) {
          uLow = mid;
        } else {
          uHigh = mid;
        }
      }

      U32 i;
      for(i=uLow;i<=uHigh;i++) {
        if(uCumulativeFrequency >= IFXHistogramDynamic::GetCumSymbolFreq(i) ) {
          uSymbol4 = i;
        } else {
          break;
        }
      }
    }
  }

  return uSymbol4;
}

// AddSymbol - Updates the model to include an occurence of the symbol
void IFXHistogramDynamic::AddSymbolRef(U32 symbol)
{
  U32 i=0;
  try
  {
    if(symbol <= m_uMaximumSymbolInHistogram) {

      // if necessary, scale down the counts
      if(m_pu16SymbolCount && m_pu16CumulativeCount4) {
        if(m_pu16CumulativeCount4[0] >= m_uElephant) {
          memset(m_pu16CumulativeCount4,0,sizeof(U16)*((m_uNumSymbols>>2)+1));
          for(i=m_uNumSymbols;i>0;i--) {
            m_pu16SymbolCount[i-1] >>= 1;
            m_pu16CumulativeCount4[(i-1)/4] += m_pu16SymbolCount[i-1];
          }
          for(i=(m_uNumSymbols>>2);i>0;i--) {
            m_pu16CumulativeCount4[i-1] += m_pu16CumulativeCount4[i];
          }

          // but don't lose the escape
          m_pu16SymbolCount[0] += 1;
          m_pu16CumulativeCount4[0] += 1;
        }
      }

      // if necessary, reallocate the arrays
      if(symbol >= m_uNumSymbols) {
        U16 *pu16OldSymbolCount = m_pu16SymbolCount;
        U16 *pu16OldCumulativeCount4 = m_pu16CumulativeCount4;
        U16 *pu16OldRawSymbolCount = m_pu16RawSymbolCount;
        U16 *pu16OldRawCumulativeCount4 = m_pu16RawCumulativeCount4;
        U32 uOldNumSymbols = m_uNumSymbols;

        m_uNumSymbols = symbol + 100;
        m_pu16RawSymbolCount = new U16[m_uNumSymbols+8];
        m_pu16RawCumulativeCount4 = new U16[(m_uNumSymbols>>2)+9];
        m_pu16SymbolCount = m_pu16RawSymbolCount;
        while((UPTR)m_pu16SymbolCount & (UPTR)0x0000000Fu) {
          m_pu16SymbolCount+=2;
        }
        m_pu16CumulativeCount4 = m_pu16RawCumulativeCount4;
        while((UPTR)m_pu16CumulativeCount4 & (UPTR)0x0000000Fu) {
          m_pu16CumulativeCount4+=2;
        }

        IFXASSERT(m_pu16SymbolCount);
        IFXASSERT(m_pu16CumulativeCount4);
        if(m_pu16SymbolCount && m_pu16CumulativeCount4) {
          memset(m_pu16SymbolCount,0,sizeof(U16)*m_uNumSymbols);
          memset(m_pu16CumulativeCount4,0,sizeof(U16)*((m_uNumSymbols>>2)+1));
          if(pu16OldSymbolCount && pu16OldCumulativeCount4) {
            memcpy(m_pu16SymbolCount,pu16OldSymbolCount,sizeof(U16)*uOldNumSymbols);
            memcpy(m_pu16CumulativeCount4,pu16OldCumulativeCount4,sizeof(U16)*((uOldNumSymbols>>2)+1));
          }
        }
        IFXDELETE_ARRAY(pu16OldRawSymbolCount );
        IFXDELETE_ARRAY(pu16OldRawCumulativeCount4);
      }

      if(m_pu16SymbolCount && m_pu16CumulativeCount4) {
        m_pu16SymbolCount[symbol] += 1;

        // This is the C version
        U32 i;
        for(i=0; i <= (symbol>>2); i++) {
          m_pu16CumulativeCount4[i] += 1;
        }

      } else {
        throw IFXException(IFX_E_OUT_OF_MEMORY);
      }
    }
  }

  catch(...)
  {
    throw;
  }
}
