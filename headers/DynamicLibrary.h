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
* File:   DynamicLibrary.h
* Author: yacinehaoues
*
* Created on Januray 20, 2017, 7:29 PM
*/

#ifndef DYNAMICLIB_H
#define DYNAMICLIB_H
#if defined(_MSC_VER) // Microsoft compiler
#include <windows.h>
#elif defined(__GNUC__) // GNU compiler
#include <dlfcn.h>
#else
#error define your compiler
#endif

void *LoadSharedLibrary(const char *pcDllname, int iMode = 2)
{
#if defined(_MSC_VER) // Microsoft compiler
    return (void *)LoadLibrary(pcDllname);
#elif defined(__GNUC__) // GNU compiler
    return dlopen(pcDllname, iMode);
#endif
}
void *GetFunction(void *Lib, char *Fnname)
{
#if defined(_MSC_VER) // Microsoft compiler
    return (void *)GetProcAddress((HINSTANCE)Lib, Fnname);
#elif defined(__GNUC__) // GNU compiler
    return dlsym(Lib, Fnname);
#endif
}

bool FreeSharedLibrary(void *hDLL)
{
#if defined(_MSC_VER) // Microsoft compiler
    return FreeLibrary((HINSTANCE)hDLL);
#elif defined(__GNUC__) // GNU compiler
    return dlclose(hDLL);
#endif
}
#endif /* DYNAMICLIB_H */
