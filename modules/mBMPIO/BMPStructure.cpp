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

#include <fstream>

namespace Impl {
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
        ifs.open(file, std::ifstream::in | std::ifstream::binary);
        if(!ifs.is_open()) {
            Error << "File "<< file << " Cannot be opened.";
            ifs.close();
            return NULL;
        }

        BMPFileHeader * fHeader = new BMPFileHeader;
        ifs.read(reinterpret_cast<byte*>(fHeader), sizeof(*fHeader));

        if(fHeader->bfType[0] == 'B' && 
           fHeader->bfType[1] == 'M') {
            Info << "Reading Valid Bitmap file...";
        } else {
            Error << file << " is an Invalid Bitmap File.";
        }



        delete fHeader;
        ifs.close();
        // On error
        return NULL;
    }
    
}
