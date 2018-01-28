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

#include <CommandFactory.h>
#include <CommandChain.h>
#include <Command.h>
#include <Logger.h>

#include <Types.h>
#include <iostream>
#include <algorithm>
#include <array>

namespace API {

    ///-------------------------------------------------------------------------------------------------
    /// @fn CommandFactory::CommandFactory()
    ///
    /// @brief  Default constructor
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///-------------------------------------------------------------------------------------------------

    CommandFactory::CommandFactory() {
        Info << "New Command Factory Created ...";
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn CommandFactory::~CommandFactory()
    ///
    /// @brief  Destructor
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///-------------------------------------------------------------------------------------------------

    CommandFactory::~CommandFactory() {

    }

    void func(int i) {

    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn CommandChain *const CommandFactory::createCommandChain(int argc, char const* argv[])
    ///
    /// @brief  Creates command chain
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param  argc    The argc.
    /// @param  argv    The argv.
    ///
    /// @return The new command chain.
    ///-------------------------------------------------------------------------------------------------

    CommandChain *const CommandFactory::createCommandChain(int argc, char const* argv[]) {
        CommandChain *const chain = new CommandChain();
        chain->addCommand(new Command("configure"));
        chain->addCommand(new Command("module_scan"));

        for(int i = 1; i < argc; i++) {
            String cmd = String(argv[i]);
            if(cmd.size()<= 1) {
                return chain;
            }
            
            if('-' == *cmd.begin()) { 
                size_t found = cmd.find('=');
                if(found != String::npos){
                    String value = cmd.substr(found + 1, cmd.size() - 1);
                    if(value.size() > 0) {
                        chain->addParameter(cmd.substr(1, found - 1), value);
                    }
                } else {
                    chain->addParameter(cmd.substr(1, cmd.size()));
                }
            }else {
                chain->addCommand(new Command(cmd));
            }
        }
        
        return chain;
    }

}