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
 * File:   BMPStructure.cpp
 * Author: yacinehaoues
 * 
 * Created on November 15, 2017, 7:59 PM
 */

// Module's include
#include "BMPStructure.h"
// Common API
#include <Logger.h>
#include <iostream>
#include <iomanip>
#include <fstream>

// disable memory optimisation for structures reading


namespace Impl {

    // forward declaration
    const bool checkValidHeader (BMPFileHeader const * fHeader);
    RGBA * readDataCompression00(const BMPImageHeader*, const BGRA *, std::ifstream *);
    RGBA * readDataCompression01(const BMPImageHeader*, const BGRA *, std::ifstream *);
    RGBA * readDataCompression02(const BMPImageHeader*, const BGRA *, std::ifstream *);
    RGBA * readDataCompression03(const BMPImageHeader*, const BGRA *, std::ifstream *);
    ///-------------------------------------------------------------------------------------------------
    /// @fn BMPStructure::BMPStructure(const String file)
    ///
    /// @summary    Constructor.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @param  file    The file.
    ///
    /// ### remarks Yacine Haoues, 1/18/2018.
    ///-------------------------------------------------------------------------------------------------

    BMPStructure::BMPStructure(const String file) :
        bitmap(readFile(file)) {
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn BMPStructure::~BMPStructure()
    ///
    /// @summary    Destructor.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// ### remarks Yacine Haoues, 1/18/2018.
    ///-------------------------------------------------------------------------------------------------

    BMPStructure::~BMPStructure() {
        if(bitmap != NULL) {
            delete bitmap;
        }
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn const Bitmap *const BMPStructure::readFile(const String file)
    ///
    /// @summary    Reads a file.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @param  file    The file.
    ///
    /// @return The file.
    ///
    /// ### remarks Yacine Haoues, 1/18/2018.
    ///-------------------------------------------------------------------------------------------------

    const Bitmap *const BMPStructure::readFile(const String file) {
        std::ifstream ifs;

        // try to open the given file
        ifs.open(file.c_str(), std::ios::binary | std::ios::in);
        if(!ifs.is_open()) {
            Error << "File "<< file << " Cannot be opened.";
            ifs.close();
            return NULL;
        }

        // starting from the beginneing
        ifs.seekg(0, std::ios::beg);

        // read the header of the file
        BMPFileHeader * fHeader = new BMPFileHeader;
        ifs.read(reinterpret_cast<char*>(fHeader), sizeof(BMPFileHeader));

        // Check if the header is a valid one
        if(checkValidHeader(fHeader)) {
            Info << "Reading Valid Bitmap file...";
        } else {
            Error << file << " is an Invalid Bitmap File.";
            delete fHeader;
            ifs.close();
            return NULL;
        }
        
        // Read image header
        BMPImageHeader * iHeader = new BMPImageHeader;
        ifs.read(reinterpret_cast<char*>(iHeader), sizeof(BMPImageHeader));

        Info << "File size : " << fHeader->Size;
        Info << "Data offset : " << fHeader->BitsOffset;
        Info << "Width : " << iHeader->Width;
        Info << "Height : " << iHeader->Height;

        // Read color table
        unsigned int colTableSize = 0;
        switch(iHeader->BitCount) {
            case 1: colTableSize = 2; break;
            case 4: colTableSize = 16; break;
            case 8: colTableSize = 256; break;
        }
        BGRA * colTable = new BGRA[colTableSize];
        ifs.seekg(BITMAP_FILEHEADER_SIZE + iHeader->HeaderSize, std::ios::beg);
        ifs.read(reinterpret_cast<char*>(colTable), sizeof(BGRA) * iHeader->ClrUsed);

        typedef RGBA * (*DataLoader)(const BMPImageHeader*, const BGRA *, std::ifstream *);
        DataLoader readDataCompression = NULL;
        switch(iHeader->Compression) {
            case 0: readDataCompression = readDataCompression00; break;
            case 1: readDataCompression = readDataCompression01; break;
            case 2: readDataCompression = readDataCompression02; break;
            case 3: readDataCompression = readDataCompression03; break;
        }
        
        RGBA * data = readDataCompression(iHeader, colTable, &ifs);
        if(data == NULL) {
            Error << "File Could Not Be Read.";
        }

        delete iHeader;
        delete fHeader;
        ifs.close();
        // On error

        Bitmap * bmp = new Bitmap;
        bmp->bitmapBits = data;
        return bmp;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn const bool checkValidHeader(BMPFileHeader const * fHeader)
    ///
    /// @summary    Check if the file has a valid header.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @param  fHeader The header.
    ///
    /// @return A const bool. true if the header starts with 'BM', false otherwise.
    ///-------------------------------------------------------------------------------------------------
    /// 
    const bool checkValidHeader(BMPFileHeader const * fHeader) {
        return  fHeader->Signature == BITMAP_SIGNATURE;
    }

    void readDataComp01BC01(RGBA * data, const BGRA * cTbl, int * idx, uint8_t * lPtr, unsigned int * j) {
        uint32_t Color = *((uint8_t*) lPtr);
        for (int k = 0; k < 8; k++) {
            data[*idx].Red = cTbl[Color & 0x80 ? 1 : 0].Red;
            data[*idx].Green = cTbl[Color & 0x80 ? 1 : 0].Green;
            data[*idx].Blue = cTbl[Color & 0x80 ? 1 : 0].Blue;
            data[*idx].Alpha = cTbl[Color & 0x80 ? 1 : 0].Alpha;
            (*idx)= (*idx) + 1;
            Color <<= 1;
        }
        lPtr++;
        *j += 7;
    }

    void readDataComp01BC08(RGBA * data, const BGRA * cTbl, int * idx, uint8_t * lPtr, unsigned int * j) {
        uint32_t color = *((uint8_t*) lPtr);
        data[*idx].Red = cTbl[color].Red;
        data[*idx].Green = cTbl[color].Green;
        data[*idx].Blue = cTbl[color].Blue;
        data[*idx].Alpha = cTbl[color].Alpha;
        (*idx)= (*idx) + 1;
        lPtr++;
    }

    RGBA * readDataCompression00(const BMPImageHeader* ihdr, const BGRA * cTbl, std::ifstream * ifs) {

        typedef void (*LineReader)(RGBA *, const BGRA *, int *, uint8_t *, unsigned int *);
        LineReader readLine = NULL;

        switch(ihdr->BitCount){
            case 1: readLine = readDataComp01BC01; break;
            case 4:break;
            case 8: readLine = readDataComp01BC08; break;
            case 16:break;
            case 24:break;
            case 32:break;
        }

        if(readLine == NULL) {
            Error << "Unsupported BitCount " << ihdr->BitCount;
            return NULL;
        }

        const unsigned long iSize = ihdr->Width * ihdr->Height;
        RGBA * data = new RGBA[iSize];
        
        unsigned int lSize = ((ihdr->Width * ihdr->BitCount / 8) + 3) & ~3;
		uint8_t * line = new uint8_t[lSize];

        int * idx = new int; *idx=0; // create and initialize index
        for (unsigned int i = 0; i < ihdr->Height; i++) {
            // red full line
            ifs->read(reinterpret_cast<char*>(line), lSize);
            uint8_t * lPtr = line;

            for (unsigned int j = 0; j < ihdr->Width; j++) {
                readLine(data, cTbl, idx, lPtr, &j);
            }
        }

        return data;
    }

    RGBA * readDataCompression01(const BMPImageHeader*, const BGRA *, std::ifstream *) {
        return NULL;
    }

    RGBA * readDataCompression02(const BMPImageHeader*, const BGRA *, std::ifstream *) {
        return NULL;
    }

    RGBA * readDataCompression03(const BMPImageHeader*, const BGRA *, std::ifstream *) {
        return NULL;
    }
    
}
