/*
* The MIT License
*
* Copyright 2018 yacinehaoues.
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
* File:   ModuleFactory.cpp
* Author: yacinehaoues
*
* Created on January 14, 2017, 20:00 PM
*/

#include <DynamicLibrary.h>
#include <Module.h>
#include <ModuleFactory.h>
#include <Logger.h>

using namespace std;


namespace API {

    typedef MODULE_IMPORT Module * (*Instance)();
    typedef MODULE_IMPORT void(*Destroy)(Module*);

    struct CleanLibraryCallBack : public Callback {
        CleanLibraryCallBack(void * libPtr, Destroy d) 
            : lib(libPtr), destruct(d) {};
        void operator()(Module * m) {
            destruct(m);
            FreeSharedLibrary(lib); 
        };
        void * lib;
        Destroy destruct;
    };



    Module * ModuleFactory::createModule(const char * path) const {
        Info << "Loading " << path;
        void *hDLL;
        //do not add extension. It is handled by LoadSharedLibrary.
        hDLL = LoadSharedLibrary(path);
        if (hDLL == 0)
            return NULL;
        Instance instanciate = (Instance)GetFunction(hDLL, "create");
        Destroy destroy = (Destroy)GetFunction(hDLL, "destroy");
        if (instanciate == 0 || destroy == 0)
            return NULL;

        Module * module = instanciate();
        module->setCleanLibraryCallback(new CleanLibraryCallBack(hDLL, destroy));

        return module;
    }

}

