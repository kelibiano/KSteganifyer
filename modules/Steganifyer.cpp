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
 * File:   Steganifyer.cpp
 * Author: yacinehaoues
 * 
 * Created on November 6, 2017, 7:59 PM
 */

#include <Steganifyer.h>
#include <CommandContext.h>
#include <Command.h>
#include <Logger.h>
#include <iostream>
#include <vector>


namespace Impl {
    StringVector & initCommands();
    
    String COMMANDS[] = {"Steganify"};
    static const String & STR_MODULE_ID ="STEGANIFYER";
    static const StringVector & LST_COMMANDS = initCommands();
    
    StringVector & initCommands() {
        StringVector * cmds = new StringVector();
        for( unsigned int a = 0; a < sizeof(COMMANDS)/sizeof(COMMANDS[0]); a = a + 1 )
            cmds->push_back(COMMANDS[a]);
        return *cmds;
    }
    
    Steganifyer::Steganifyer() {
    }

    Steganifyer::~Steganifyer() {
    }
    
    const String & Steganifyer::getID() const {
        return STR_MODULE_ID;
    }
    
    const StringVector& Steganifyer::getCommands() const {
        return LST_COMMANDS;
    }
    
    void Steganifyer::handle(const API::Command *const cmd, API::CommandContext *const cmdCtx) {
        Info << "Handling " << *cmd << " ...";
    }
}
