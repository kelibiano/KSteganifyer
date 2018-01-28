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

        Info << "File size : " << fHeader->size;
        Info << "Data offset : " << fHeader->bitsOffset;
        Info << "Width : " << iHeader->width;
        Info << "Height : " << iHeader->height;

        // Read color table
        unsigned int colTableSize = 0;
        switch(iHeader->bitcount) {
            case 1: colTableSize = 2; break;
            case 4: colTableSize = 16; break;
            case 8: colTableSize = 256; break;
        }
        Info << "Bit-count : " << iHeader->bitcount;
        Info << "Color table size : " << colTableSize;

        BGRA * colTable = new BGRA[colTableSize];
        ifs.seekg(BITMAP_FILEHEADER_SIZE + iHeader->headerSize, std::ios::beg);
        ifs.read(reinterpret_cast<char*>(colTable), sizeof(BGRA) * iHeader->clrUsed);

        typedef RGBA * (*DataLoader)(const BMPImageHeader*, const BGRA *, std::ifstream *);
        DataLoader readDataCompression = NULL;
        switch(iHeader->compression) {
            case 0: readDataCompression = readDataCompression00; break;
            case 1: readDataCompression = readDataCompression01; break;
            case 2: readDataCompression = readDataCompression02; break;
            case 3: readDataCompression = readDataCompression03; break;
        }
        Info << "Compression : " << iHeader->compression;
        
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
    const bool checkValidHeader(BMPFileHeader const * fHeader) {
        return  fHeader->signature == BITMAP_SIGNATURE;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn void readDataComp01BC01(RGBA * data, const BGRA * cTbl, int * idx, uint8_t * lPtr, unsigned int * j)
    ///
    /// @brief  Reads data component 01 bc 01
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param [in,out] data    If non-null, the data.
    /// @param          cTbl    The table.
    /// @param [in,out] idx     If non-null, zero-based index of the.
    /// @param [in,out] lPtr    If non-null, the pointer.
    /// @param [in,out] j       If non-null, an int to process.
    ///-------------------------------------------------------------------------------------------------
    void readDataComp01BC01(RGBA * data, const BGRA * cTbl, int * idx, uint8_t * lPtr, unsigned int * j) {
        uint32_t color = *((uint8_t*) lPtr);
        for (int k = 0; k < 8; k++) {
            data[*idx].red = cTbl[color & 0x80 ? 1 : 0].red;
            data[*idx].green = cTbl[color & 0x80 ? 1 : 0].green;
            data[*idx].blue = cTbl[color & 0x80 ? 1 : 0].blue;
            data[*idx].alpha = cTbl[color & 0x80 ? 1 : 0].alpha;
            (*idx)= (*idx) + 1;
            color <<= 1;
        }
        lPtr++;
        *j += 7;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn void readDataComp01BC08(RGBA * data, const BGRA * cTbl, int * idx, uint8_t * lPtr, unsigned int * j)
    ///
    /// @brief  Reads data component 01 bc 08
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param [in,out] data    If non-null, the data.
    /// @param          cTbl    The table.
    /// @param [in,out] idx     If non-null, zero-based index of the.
    /// @param [in,out] lPtr    If non-null, the pointer.
    /// @param [in,out] j       If non-null, an int to process.
    ///-------------------------------------------------------------------------------------------------

    void readDataComp01BC08(RGBA * data, const BGRA * cTbl, int * idx, uint8_t * lPtr, unsigned int * j) {
        uint32_t color = *((uint8_t*) lPtr);
        data[*idx].red = cTbl[color].red;
        data[*idx].green = cTbl[color].green;
        data[*idx].blue = cTbl[color].blue;
        data[*idx].alpha = cTbl[color].alpha;
        (*idx)= (*idx) + 1;
        lPtr++;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn RGBA * readDataCompression00(const BMPImageHeader* ihdr, const BGRA * cTbl, std::ifstream * ifs)
    ///
    /// @brief  Reads data compression 00
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param          ihdr    The ihdr.
    /// @param          cTbl    The table.
    /// @param [in,out] ifs     If non-null, the ifs.
    ///
    /// @return Null if it fails, else the data compression 00.
    ///-------------------------------------------------------------------------------------------------

    RGBA * readDataCompression00(const BMPImageHeader* ihdr, const BGRA * cTbl, std::ifstream * ifs) {

        typedef void (*LineReader)(RGBA *, const BGRA *, int *, uint8_t *, unsigned int *);
        LineReader readLine = NULL;

        switch(ihdr->bitcount){
            case 1: readLine = readDataComp01BC01; break;
            case 4: break;
            case 8: readLine = readDataComp01BC08; break;
            case 16: break;
            case 24: break;
            case 32: break;
        }

        if(readLine == NULL) {
            Error << "Unsupported BitCount " << ihdr->bitcount;
            return NULL;
        }

        const unsigned long iSize = ihdr->width * ihdr->height;
        RGBA * data = new RGBA[iSize];
        
        unsigned int lSize = ((ihdr->width * ihdr->bitcount / 8) + 3) & ~3;
		uint8_t * line = new uint8_t[lSize];

        int * idx = new int; *idx=0; // create and initialize index
        for (unsigned int i = 0; i < ihdr->height; i++) {
            // red full line
            ifs->read(reinterpret_cast<char*>(line), lSize);
            uint8_t * lPtr = line;

            for (unsigned int j = 0; j < ihdr->width; j++) {
                readLine(data, cTbl, idx, lPtr, &j);
            }
        }

        return data;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn RGBA * readDataCompression01(const BMPImageHeader*, const BGRA *, std::ifstream *)
    ///
    /// @brief  Reads data compression 01
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param          parameter1  The first parameter.
    /// @param          parameter2  The second parameter.
    /// @param [in,out] parameter3  If non-null, the third parameter.
    ///
    /// @return Null if it fails, else the data compression 01.
    ///-------------------------------------------------------------------------------------------------

    RGBA * readDataCompression01(const BMPImageHeader*, const BGRA *, std::ifstream *) {
        return NULL;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn RGBA * readDataCompression02(const BMPImageHeader*, const BGRA *, std::ifstream *)
    ///
    /// @brief  Reads data compression 02
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param          parameter1  The first parameter.
    /// @param          parameter2  The second parameter.
    /// @param [in,out] parameter3  If non-null, the third parameter.
    ///
    /// @return Null if it fails, else the data compression 02.
    ///-------------------------------------------------------------------------------------------------

    RGBA * readDataCompression02(const BMPImageHeader*, const BGRA *, std::ifstream *) {
        return NULL;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn RGBA * readDataCompression03(const BMPImageHeader*, const BGRA *, std::ifstream *)
    ///
    /// @brief  Reads data compression 03
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param          parameter1  The first parameter.
    /// @param          parameter2  The second parameter.
    /// @param [in,out] parameter3  If non-null, the third parameter.
    ///
    /// @return Null if it fails, else the data compression 03.
    ///-------------------------------------------------------------------------------------------------

    RGBA * readDataCompression03(const BMPImageHeader*, const BGRA *, std::ifstream *) {
        return NULL;
    }
    
}
