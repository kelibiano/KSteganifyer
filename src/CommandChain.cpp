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

#include <CommandChain.h>
#include <Command.h>
#include <iostream>
namespace Impl {

    
    CommandChain::CommandChain() : commands(new std::queue<Command *const>()) {
        
        std::cout << "New Command Chain Created ..." << '\n';
    }

    CommandChain::~CommandChain() {

    }
    
    void CommandChain::addCommand(Command *const cmd) {
        commands->push(cmd);
    }
    
    void CommandChain::addParameter(const String& param) {
        std::cout << "Parameter : " << param << '\n';
    }
    
    void CommandChain::addParameter(const String& param, const String& value) {
        std::cout << "Parameter : " << param <<'\t'<<"Value : "<< value<<'\n';
    }

    bool CommandChain::hasCommands() {
        return !commands->empty();
    }

    Command * CommandChain::nextCommand() {
        Command * cmd = commands->front();
        commands->pop();
        return cmd;
    }
}