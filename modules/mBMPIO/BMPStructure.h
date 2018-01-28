/*
 * The MIT License
 *
 * Copyright 2017 yacinehaoues.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * 
 */

/* 
 * File:   BMPIO.h
 * Author: yacinehaoues
 *
 * Created on November 14, 2017, 7:59 PM
 * 
 * References : 
 * Benjamin Kalytta
 * Windows Bitmap File Loader
 * Version 1.2.5 (20120929)
 * http://www.kalytta.com/bitmap.h
 * 
 */

#ifndef BMPSTRUCTURE_H
#define BMPSTRUCTURE_H

#include <Types.h>
namespace Impl
{

#ifndef __LITTLE_ENDIAN__
#ifndef __BIG_ENDIAN__
#define __LITTLE_ENDIAN__
#endif /* __BIG_ENDIAN__ */
#endif /* __LITTLE_ENDIAN__ */

#ifdef __LITTLE_ENDIAN__
#define BITMAP_SIGNATURE 0x4d42
#else
#define BITMAP_SIGNATURE 0x424d
#endif /* __LITTLE_ENDIAN__ */

#if defined(_MSC_VER) || defined(__INTEL_COMPILER)
typedef unsigned __int32 uint32_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int8 uint8_t;
typedef __int32 int32_t;
#elif defined(__GNUC__) || defined(__CYGWIN__) || defined(__MWERKS__) || defined(__WATCOMC__) || defined(__PGI) || defined(__LCC__)
#include <stdint.h>
#else
typedef unsigned int uint32_t;
typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;
typedef int int32_t;
#endif

#pragma pack(push, 1)

///-------------------------------------------------------------------------------------------------
/// @struct BMPFileHeader
///
/// @brief  A bitmap file header.
///
/// @author Yacine Haoues
/// @date   1/22/2018
///-------------------------------------------------------------------------------------------------

typedef struct BMPFileHeader
{
    uint16_t signature;
    uint32_t size;
    uint32_t reserved;
    uint32_t bitsOffset;
} BITMAP_FILEHEADER;

#define BITMAP_FILEHEADER_SIZE 14

///-------------------------------------------------------------------------------------------------
/// @struct BMPImageHeader
///
/// @brief  A bitmap image header.
///
/// @author Yacine Haoues
/// @date   1/22/2018
///-------------------------------------------------------------------------------------------------

typedef struct BMPImageHeader
{
    uint32_t headerSize;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitcount;
    uint32_t compression;
    uint32_t sizeImage;
    int32_t xResolution;
    int32_t yResolution;
    uint32_t clrUsed;
    uint32_t clrImportant;
    uint32_t redMask;
    uint32_t greenMask;
    uint32_t blueMask;
    uint32_t alphaMask;
    uint32_t csType;
    uint32_t endpoints[9]; // see http://msdn2.microsoft.com/en-us/library/ms536569.aspx
    uint32_t gammaRed;
    uint32_t gammaGreen;
    uint32_t gammaBlue;
} BITMAP_HEADER;

///-------------------------------------------------------------------------------------------------
/// @struct _RGBA
///
/// @brief  A rgba.
///
/// @author Yacine Haoues
/// @date   1/22/2018
///-------------------------------------------------------------------------------------------------

typedef struct _RGBA
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
} RGBA;

///-------------------------------------------------------------------------------------------------
/// @struct _BGRA
///
/// @brief  A bgra.
///
/// @author Yacine Haoues
/// @date   1/22/2018
///-------------------------------------------------------------------------------------------------

typedef struct _BGRA
{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
} BGRA;

///-------------------------------------------------------------------------------------------------
/// @struct Bitmap
///
/// @brief  A bitmap.
///
/// @author Yacine Haoues
/// @date   1/22/2018
///-------------------------------------------------------------------------------------------------

struct Bitmap
{
    RGBA * bitmapBits;
};

#pragma pack(pop)

///-------------------------------------------------------------------------------------------------
/// @class  BMPStructure
///
/// @brief  A bitmap structure.
///
/// @author Yacine Haoues
/// @date   1/22/2018
///-------------------------------------------------------------------------------------------------

class BMPStructure
{
  public:

    BMPStructure(const String);
    virtual ~BMPStructure();

  private:
    const Bitmap *const readFile(const String);
    const Bitmap *const bitmap;
};
}

#endif /* BMPIO_H */
