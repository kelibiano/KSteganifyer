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
* File:   SimpleModule.h
* Author: yacinehaoues
*
* Created on November 4, 2017, 5:28 PM
*/

#ifndef SIMPLEMODULE_H
#define SIMPLEMODULE_H

#include <functional>

#include <Types.h>
#include <Module.h>

namespace API {

    typedef std::function<void(const API::Command *const, API::CommandContext *const)> CommandHandler;
    typedef std::map<String, CommandHandler> CommandHandlersMap;
    class SimpleModule : public Module {
    public:
        SimpleModule(const String &);
        void handle(const Command *const, CommandContext *const);
        const StringVector& getCommands() const;
        const String & getID() const;
        virtual ~SimpleModule();
    protected :
        void registerCommandHandler(const String &, CommandHandler);
    private :
        CommandHandler getCommandHandler(const String &);  
        CommandHandlersMap handlers;
    };

}

#endif /* MODULE_H */

