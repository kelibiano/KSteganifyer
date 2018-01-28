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
 * File:   CommandContext.h
 * Author: yacinehaoues
 *
 * Created on November 6, 2017, 7:29 PM
 */

#ifndef COMMANDCONTEXT_H
#define COMMANDCONTEXT_H

#include <Types.h>
#include <map>

namespace API {

    class CommandChain;
    class Application;

    struct DataDescriptor {
        const String type;
        void *const raw;
        DataDescriptor(String etype, void * const data) : type(etype), raw(data) {}
        DataDescriptor(const DataDescriptor & dsc) : type(dsc.type), raw(dsc.raw){}
    };

    inline DataDescriptor * const describe(String type, void * const data) {
        return new DataDescriptor(type, data);
    }

    class CommandContext {
    public:
        bool put(String, DataDescriptor *const);
        DataDescriptor *const get(String) const;
        CommandChain *const getChain() const;
        Application *const getApplication() const;
        CommandContext(Application *const, CommandChain *const);
        virtual ~CommandContext();
    private:
        typedef std::map<String, DataDescriptor *const> DataMap;
        DataMap * dataMap;
        CommandChain *const chain;
        Application *const application;
    };

}


#endif /* COMMANDCONTEXT_H */

