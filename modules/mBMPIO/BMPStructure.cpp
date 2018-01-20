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

#include <BMPStructure.h>
#include <Logger.h>
#include <iostream>
#include <iomanip>
#include <fstream>

#pragma pack(1)

namespace Impl {

    const bool checkValidHeader(BMPFileHeader const * fHeader);

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
        ifs.open(file.c_str(), std::ios::binary);
        if(!ifs.is_open()) {
            Error << "File "<< file << " Cannot be opened.";
            ifs.close();
            return NULL;
        }
        // read the header of the file
        BMPFileHeader * fHeader = new BMPFileHeader;
        BMPInfoHeader * iHeader = new BMPInfoHeader;
        ifs.seekg(0, std::ios::beg);
        ifs.read((char*)fHeader, sizeof(BMPFileHeader));
        // Check if the header is a valid one
        if(checkValidHeader(fHeader)) {
            Info << "Reading Valid Bitmap file...";
        } else {
            Error << file << " is an Invalid Bitmap File.";
            delete fHeader;
            ifs.close();
            return NULL;
        }

        ifs.read(reinterpret_cast<char*>(iHeader), sizeof(BMPInfoHeader));

        Info << "File size : " << fHeader->bfSize;
        Info << "Goto offset : " << fHeader->bfOffBits;
        
        ifs.seekg(fHeader->bfOffBits);

        const unsigned int nbquads = iHeader->biSizeImage / sizeof(RGBTRIPLE);
        Info << "reading " << iHeader->biSizeImage << " bytes into "<< nbquads << " RGBA" ;
       

        Info << "Printing " << iHeader->biWidth << " x " << iHeader->biHeight << " Image";
        Info << "With " << iHeader->biBitCount << " Bits";
       


        RGBTRIPLE * quads = new RGBTRIPLE[nbquads];
        ifs.read(reinterpret_cast<char*>(quads), iHeader->biSizeImage);

        char ch[] = {' ','.','-','+','X','B', '#'};
        for (size_t i = iHeader->biHeight - 1; i >= 0; i--)
        {
            std::cout << "->";
            for (size_t j = 0; j < iHeader->biWidth; j++) {
                int idx = i * iHeader->biWidth + j +i;

                int x = ((((unsigned char)quads[idx].rgbBlue) +
                ((unsigned char)quads[idx].rgbGreen) +
                ((unsigned char)quads[idx].rgbRed)) )/3/37;
                std::cout << ch[x];
            }
            std::cout << "<-" << std::endl;
        }

        // clean
        delete[] quads;
        delete fHeader;
        ifs.close();
        // On error
        return NULL;
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
        return  fHeader->bfType1 == 'B' &&
                fHeader->bfType2 =='M';
    }
}
