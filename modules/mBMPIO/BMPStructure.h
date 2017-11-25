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
 */

/* 
 * File:   BMPIO.h
 * Author: yacinehaoues
 *
 * Created on November 14, 2017, 7:59 PM
 */

#ifndef BMPSTRUCTURE_H
#define BMPSTRUCTURE_H
#include <Types.h>
namespace Impl {

    typedef char byte;
    const size_t COLORS_24 = 24;

    struct BMPFileHeader {
        byte bfType[2]; // standard type 
        byte bfSize[4]; // file size
        byte bfReserved1[2]; // reserved 2
        byte bfReserved2[2]; // reserved 1
        byte bfOffBits[4]; // offset to the pixels data
    };

    struct BMPInfoHeader {
        byte biSize [4];
        byte biWidth [4];
        byte biHeight [4];
        byte biPlanes [2];
        byte biBitCount [2];
        byte biCompression [4];
        byte biSizeImage [4];
        byte biXPelsPerMeter [4];
        byte biYPelsPerMeter [4];
        byte biClrUsed [4];
        byte biClrImportant [4];
    };

    struct RGBQUAD {
        byte rgbBlue;
        byte rgbGreen;
        byte rgbRed;
        byte rgbReserved;
    };
    struct RGBTRIPLE {
        byte rgbBlue;
        byte rgbGreen;
        byte rgbRed;
    };

    struct Bitmap {
        BMPFileHeader fileHeader;
        BMPInfoHeader infoHeader;
        RGBQUAD * colors;
        byte * bitmapBits;
    };

    
    class BMPStructure  {
    public :
        BMPStructure(const String);
        virtual ~BMPStructure();
    private :
        const Bitmap *const readFile(const String);
        const Bitmap *const bitmap;
    };
}

#endif /* BMPIO_H */

