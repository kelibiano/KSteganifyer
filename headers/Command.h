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
* File:   Command.h
* Author: yacinehaoues
*
* Created on November 9, 2017, 7:29 PM
*/

#ifndef COMMAND_H
#define COMMAND_H

#include <Types.h>

namespace API {

    ///-------------------------------------------------------------------------------------------------
    /// @class  Command
    ///
    /// @brief  A command.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///-------------------------------------------------------------------------------------------------

    class Command {
    public:
        const String getCommandString() const;
        void put(const String, const String);
        const String get(const String) const;
        bool conatin(const String) const;

        Command(const String);
        virtual ~Command();
        friend std::ostream & operator<<(std::ostream&, const Command&);
        friend std::ostream & operator<<(std::ostream&, const Command*);

    private:
        const String strCommand;
        Dictionnary *const dict;
    };
}


#endif /* COMMANDCONTEXT_H */