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

typedef struct BMPFileHeader
{
    uint16_t Signature;
    uint32_t Size;
    uint32_t Reserved;
    uint32_t BitsOffset;
} BITMAP_FILEHEADER;

#define BITMAP_FILEHEADER_SIZE 14

typedef struct BMPImageHeader
{
    uint32_t HeaderSize;
    int32_t Width;
    int32_t Height;
    uint16_t Planes;
    uint16_t BitCount;
    uint32_t Compression;
    uint32_t SizeImage;
    int32_t PelsPerMeterX;
    int32_t PelsPerMeterY;
    uint32_t ClrUsed;
    uint32_t ClrImportant;
    uint32_t RedMask;
    uint32_t GreenMask;
    uint32_t BlueMask;
    uint32_t AlphaMask;
    uint32_t CsType;
    uint32_t Endpoints[9]; // see http://msdn2.microsoft.com/en-us/library/ms536569.aspx
    uint32_t GammaRed;
    uint32_t GammaGreen;
    uint32_t GammaBlue;
} BITMAP_HEADER;

typedef struct _RGBA
{
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
    uint8_t Alpha;
} RGBA;

typedef struct _BGRA
{
    uint8_t Blue;
    uint8_t Green;
    uint8_t Red;
    uint8_t Alpha;
} BGRA;

struct Bitmap
{
    RGBA * bitmapBits;
};

#pragma pack(pop)

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
