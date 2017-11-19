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

namespace Impl {

    const bool checkValidHeader(BMPFileHeader const * fHeader);

    BMPStructure::BMPStructure(const String file) :
        bitmap(readFile(file)) {
    }

    BMPStructure::~BMPStructure() {
        if(bitmap != NULL) {
            delete bitmap;
        }
    }

    const Bitmap *const BMPStructure::readFile(const String file) {
        std::ifstream ifs;
        // try to open the given file
        ifs.open(file.c_str(), std::ifstream::in | std::ifstream::binary);
        if(!ifs.is_open()) {
            Error << "File "<< file << " Cannot be opened.";
            ifs.close();
            return NULL;
        }
        // read the header of the file
        BMPFileHeader * fHeader = new BMPFileHeader;
        BMPInfoHeader * iHeader = new BMPInfoHeader;

        ifs.read(reinterpret_cast<byte*>(fHeader), sizeof(BMPFileHeader));
        // Check if the header is a valid one
        if(checkValidHeader(fHeader)) {
            Info << "Reading Valid Bitmap file...";
        } else {
            Error << file << " is an Invalid Bitmap File.";
            delete fHeader;
            ifs.close();
            return NULL;
        }

        ifs.read(reinterpret_cast<byte*>(iHeader), sizeof(BMPInfoHeader));

        const unsigned int size = *reinterpret_cast<unsigned int*>(fHeader->bfSize);
        const unsigned int offset = *reinterpret_cast<unsigned int*>(fHeader->bfOffBits);

        Info << "File size : " << size ;
        Info << "Goto offset : " << offset;
        
        ifs.seekg(offset);

        const unsigned int block = size - offset;
        const unsigned int nbquads = block / sizeof(RGBTRIPLE);
        Info << "reading " << block << " bytes into "<< nbquads << " RGBA" ;
       
        
        
        const unsigned int width = *reinterpret_cast<unsigned int*>(iHeader->biWidth);
        const unsigned int height = *reinterpret_cast<unsigned int*>(iHeader->biHeight);
        const unsigned int bitCount = *reinterpret_cast<unsigned int*>(iHeader->biBitCount);
        Info << "Printing " << width << " x " << height << " Image";
        Info << "With " << bitCount << " Bits";
       


        RGBTRIPLE * quads = new RGBTRIPLE[nbquads];
        ifs.read(reinterpret_cast<byte*>(quads), block);

        char ch[] = {' ','.','-','+','X','B', '#'};
        for (int i = height - 1; i >= 0; i--)
        {
            std::cout << "->";
            for (int j = 0; j < width; j++) { 
                int idx = i * width + j +i;

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
    const bool checkValidHeader(BMPFileHeader const * fHeader) {
        return  fHeader->bfType[0] == 'B' &&
                fHeader->bfType[1] =='M';
    }
}
