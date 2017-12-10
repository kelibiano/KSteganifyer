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
 * File:   BMPIO.cpp
 * Author: yacinehaoues
 * 
 * Created on November 14, 2017, 7:59 PM
 */

#include <BMPIO.h>
#include <BMPStructure.h>
#include <CommandContext.h>
#include <CommandChain.h>
#include <Command.h>
#include <Logger.h>
#include <Types.h>
#include <vector>

namespace Impl {

    const String STR_PARAM_INPUTFILE = "input-file";

    BMPIO::BMPIO() : ID(new String("BMPIO-")), cmds(new StringVector()) {
        cmds->push_back("read");
        cmds->push_back("write");
    }

    BMPIO::~BMPIO() {
        Info << "Cleaning BMPIO";
        delete ID;
        delete cmds;
    }
    
    const String & BMPIO::getID() const {
        return *ID;
    }
    
    const StringVector& BMPIO::getCommands() const {
        return *cmds;
    }
    
    void BMPIO::handle(const API::Command *const cmd, API::CommandContext *const cmdCtx) {

        // Checking the command (Another way is to found later, Strategy pattern maybe)
        if(cmd->getCommandString() != "read") {
            Error << "Command " << *cmd << " Not handled yet.";
            return;
        }

        // Searching the relevant parameters for the command
        API::CommandChain *const chain = cmdCtx->getChain();
        const String *const fname = chain->getParameter(STR_PARAM_INPUTFILE);
        if(fname == NULL) {
            Error << "No input BMP file found !";
            return;
        }

        // read the BMP
        Info << "Reading " << *fname << " ...";
        BMPStructure *const bmpStrcut = new BMPStructure(*fname);
        delete bmpStrcut;
    }
}

extern "C" API::Module * create() {
    return new Impl::BMPIO();
}

extern "C" void destroy(API::Module * m) {
    delete m;
}
