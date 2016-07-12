/*************************************************************************************************/
/*!
 *  \file   bstream.h
 *
 *  \brief  Byte stream to integer conversion macros.
 *
 *          $Date: 2015-10-17 10:29:30 -0400 (Sat, 17 Oct 2015) $
 *          $Revision: 4235 $
 *
 * Copyright (c) 2009-2016, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: LicenseRef-PBL
 *
 * This file and the related binary are licensed under the
 * Permissive Binary License, Version 1.0 (the "License");
 * you may not use these files except in compliance with the License.
 *
 * You may obtain a copy of the License here:
 * LICENSE-permissive-binary-license-1.0.txt and at
 * https://www.mbed.com/licenses/PBL-1.0
 *
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*************************************************************************************************/
#ifndef BSTREAM_H
#define BSTREAM_H

#include "bda.h"

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************************************
  Macros
**************************************************************************************************/

/*!
 * Macros for converting a little endian byte buffer to integers.
 */
#define BYTES_TO_UINT16(n, p)     {n = ((uint16_t)(p)[0] + ((uint16_t)(p)[1] << 8));}

#define BYTES_TO_UINT24(n, p)     {n = ((uint16_t)(p)[0] + ((uint16_t)(p)[1] << 8) + \
                                        ((uint16_t)(p)[2] << 16));}

#define BYTES_TO_UINT32(n, p)     {n = ((uint32_t)(p)[0] + ((uint32_t)(p)[1] << 8) + \
                                        ((uint32_t)(p)[2] << 16) + ((uint32_t)(p)[3] << 24));}

#define BYTES_TO_UINT40(n, p)     {n = ((uint64_t)(p)[0] + ((uint64_t)(p)[1] << 8) + \
                                        ((uint64_t)(p)[2] << 16) + ((uint64_t)(p)[3] << 24) + \
                                        ((uint64_t)(p)[4] << 32));}

#define BYTES_TO_UINT64(n, p)     {n = ((uint64_t)(p)[0] + ((uint64_t)(p)[1] << 8) + \
                                        ((uint64_t)(p)[2] << 16) + ((uint64_t)(p)[3] << 24) + \
                                        ((uint64_t)(p)[4] << 32) + ((uint64_t)(p)[5] << 40) + \
                                        ((uint64_t)(p)[6] << 48) + ((uint64_t)(p)[7] << 56));}

/*!
 * Macros for converting little endian integers to array of bytes
 */
#define UINT16_TO_BYTES(n)        ((uint8_t) (n)), ((uint8_t)((n) >> 8))

/*!
 * Macros for converting little endian integers to single bytes
 */
#define UINT16_TO_BYTE0(n)        ((uint8_t) (n))
#define UINT16_TO_BYTE1(n)        ((uint8_t) ((n) >> 8))

#define UINT32_TO_BYTE0(n)        ((uint8_t) (n))
#define UINT32_TO_BYTE1(n)        ((uint8_t) ((n) >> 8))
#define UINT32_TO_BYTE2(n)        ((uint8_t) ((n) >> 16))
#define UINT32_TO_BYTE3(n)        ((uint8_t) ((n) >> 24))

/*!
 * Macros for converting a little endian byte stream to integers, with increment.
 */
#define BSTREAM_TO_INT8(n, p)     {n = (int8_t)(*(p)++);}
#define BSTREAM_TO_UINT8(n, p)    {n = (uint8_t)(*(p)++);}
#define BSTREAM_TO_UINT16(n, p)   {BYTES_TO_UINT16(n, p); p += 2;}
#define BSTREAM_TO_UINT24(n, p)   {BYTES_TO_UINT24(n, p); p += 3;}
#define BSTREAM_TO_UINT32(n, p)   {BYTES_TO_UINT32(n, p); p += 4;}
#define BSTREAM_TO_UINT40(n, p)   {BYTES_TO_UINT40(n, p); p += 5;}
#define BSTREAM_TO_UINT64(n, p)   {n = BstreamToUint64(p); p += 8;}
#define BSTREAM_TO_BDA(bda, p)    {BdaCpy(bda, p); p += BDA_ADDR_LEN;}
#define BSTREAM_TO_BDA64(bda, p)  {bda = BstreamToBda64(p); p += BDA_ADDR_LEN;}

/*!
 * Macros for converting integers to a little endian byte stream, with increment.
 */
#define UINT8_TO_BSTREAM(p, n)    {*(p)++ = (uint8_t)(n);}
#define UINT16_TO_BSTREAM(p, n)   {*(p)++ = (uint8_t)(n); *(p)++ = (uint8_t)((n) >> 8);}
#define UINT24_TO_BSTREAM(p, n)   {*(p)++ = (uint8_t)(n); *(p)++ = (uint8_t)((n) >> 8); \
                                  *(p)++ = (uint8_t)((n) >> 16);}
#define UINT32_TO_BSTREAM(p, n)   {*(p)++ = (uint8_t)(n); *(p)++ = (uint8_t)((n) >> 8); \
                                  *(p)++ = (uint8_t)((n) >> 16); *(p)++ = (uint8_t)((n) >> 24);}
#define UINT40_TO_BSTREAM(p, n)   {*(p)++ = (uint8_t)(n); *(p)++ = (uint8_t)((n) >> 8); \
                                  *(p)++ = (uint8_t)((n) >> 16); *(p)++ = (uint8_t)((n) >> 24); \
                                  *(p)++ = (uint8_t)((n) >> 32);}
#define UINT64_TO_BSTREAM(p, n)   {Uint64ToBstream(p, n); p += sizeof(uint64_t);}
#define BDA_TO_BSTREAM(p, bda)    {BdaCpy(p, bda); p += BDA_ADDR_LEN;}
#define BDA64_TO_BSTREAM(p, bda)  {Bda64ToBstream(p, bda); p += BDA_ADDR_LEN;}

/*!
 * Macros for converting integers to a little endian byte stream, without increment.
 */
#define UINT16_TO_BUF(p, n)       {(p)[0] = (uint8_t)(n); (p)[1] = (uint8_t)((n) >> 8);}
#define UINT32_TO_BUF(p, n)       {(p)[0] = (uint8_t)(n); (p)[1] = (uint8_t)((n) >> 8); \
                                  (p)[2] = (uint8_t)((n) >> 16); (p)[3] = (uint8_t)((n) >> 24);}

/*!
 * Macros for comparing a little endian byte buffer to integers.
 */
#define BYTES_UINT16_CMP(p, n)    ((p)[1] == UINT16_TO_BYTE1(n) && (p)[0] == UINT16_TO_BYTE0(n))

/*!
 * Macros for IEEE FLOAT type:  exponent = byte 3, mantissa = bytes 2-0
 */
#define FLT_TO_UINT32(m, e)       ((m) | ((int32_t)(e) << 24))
#define UINT32_TO_FLT(m, e, n)    {m = UINT32_TO_FLT_M(n); e = UINT32_TO_FLT_E(n);}
#define UINT32_TO_FLT_M(n)        ((((n) & 0x00FFFFFF) >= 0x00800000) ? \
                                   ((int32_t)(((n) | 0xFF000000))) : ((int32_t)((n) & 0x00FFFFFF)))
#define UINT32_TO_FLT_E(n)        ((int8_t)(n >> 24))
/*!
 * Macros for IEEE SFLOAT type:  exponent = bits 15-12, mantissa = bits 11-0
 */
#define SFLT_TO_UINT16(m, e)      ((m) | ((int16_t)(e) << 12))
#define UINT16_TO_SFLT(m, e, n)   {m = UINT16_TO_SFLT_M(n); e = UINT16_TO_SFLT_E(n);}
#define UINT16_TO_SFLT_M(n)       ((((n) & 0x0FFF) >= 0x0800) ? \
                                   ((int16_t)(((n) | 0xF000))) : ((int16_t)((n) & 0x0FFF)))
#define UINT16_TO_SFLT_E(n)       (((n >> 12) >= 0x0008) ? \
                                   ((int8_t)(((n >> 12) | 0xF0))) : ((int8_t)(n >> 12)))

/**************************************************************************************************
  Function Declarations
**************************************************************************************************/

uint64_t BstreamToBda64(const uint8_t *p);
uint64_t BstreamToUint64(const uint8_t *p);
void Bda64ToBstream(uint8_t *p, uint64_t bda);
void Uint64ToBstream(uint8_t *p, uint64_t n);

#ifdef __cplusplus
};
#endif

#endif /* BSTREAM_H */
