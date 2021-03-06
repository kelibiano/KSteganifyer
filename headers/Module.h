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
 * File:   Module.h
 * Author: yacinehaoues
 *
 * Created on November 4, 2017, 5:28 PM
 */

#ifndef MODULE_H
#define MODULE_H

#ifndef MODULE_EXPORT
#if defined(_MSC_VER)
#define MODULE_EXPORT extern "C" __declspec(dllexport)
#else
#define MODULE_EXPORT extern "C" 
#endif /* Compiler */
#endif /* MODULE_EXPORT */

#ifndef MODULE_IMPORT
#if defined(_MSC_VER)
#define MODULE_IMPORT __declspec(dllimport)
#else
#define MODULE_IMPORT 
#endif /* Compiler */
#endif /* MODULE_IMPORT */

#include <Types.h>


namespace API {

    /* Forward declaration */
    class CommandContext;
    class Command;
    class Module;

    /// <summary>
    /// Callback function used to clean module
    /// </summary>
    struct Callback {
        virtual void operator()(Module *) = 0;
        virtual ~Callback(){};
    };

    class Module {
    public:

        /* Returns the ID of The Module */
        virtual const String& getID() const = 0;

        /* Returns the list of the handled commands */
        virtual const StringVector& getCommands() const = 0;

        /* Handles the given commands with the given parameters */
        virtual void handle(const Command *const, CommandContext *const) = 0;

        /* Library clean callback */
        inline void setCleanLibraryCallback(Callback * call) { callback = call; };
        inline Callback * getCleanCallback() const { return callback; };

        /* Destructor */
        inline virtual ~Module() {};

    private:
        Callback * callback = NULL;
    };

}

#endif /* MODULE_H */

