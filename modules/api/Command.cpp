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

#include <Command.h>
#include <Logger.h>

#include <iostream>
namespace API {

    ///-------------------------------------------------------------------------------------------------
    /// @fn Command::Command(const String cmd )
    ///
    /// @brief  Constructor.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @param  cmd The command.
    ///-------------------------------------------------------------------------------------------------
    Command::Command(const String cmd)
        : strCommand(cmd), dict(new Dictionnary()) {
        Info << "New Command : " << getCommandString();
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn Command::~Command()
    ///
    /// @brief  Destructor.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///-------------------------------------------------------------------------------------------------

    Command::~Command() {
        delete dict;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn const String Command::getCommandString() const
    ///
    /// @brief  Gets command string.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @return The command string.
    ///-------------------------------------------------------------------------------------------------

    const String Command::getCommandString() const {
        return strCommand;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn const String Command::get(const String key) const
    ///
    /// @brief  Gets a constant string using the given key.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @param  key The key to get.
    ///
    /// @return A const String.
    ///-------------------------------------------------------------------------------------------------

    const String Command::get(const String key) const {
        Dictionnary::const_iterator it = dict->find(key);
        return it != dict->end() ? it->second : String("");
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn void Command::put(const String key, const String val)
    ///
    /// @brief  Puts.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @param  key The key.
    /// @param  val The value.
    ///-------------------------------------------------------------------------------------------------

    void Command::put(const String key, const String val) {
        dict->emplace(key, val);
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn bool Command::conatin(const String key) const
    ///
    /// @brief  Conatins the given key.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @param  key The key.
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------

    bool Command::conatin(const String key) const {
        Dictionnary::const_iterator it = dict->find(key);
        return it != dict->end();
    }

    std::ostream& operator<<(std::ostream& stream, const Command& cmd) {
        return stream << cmd.getCommandString();
    }

    std::ostream& operator<<(std::ostream& stream, const Command* cmd) {
        return stream << cmd->getCommandString();
    }
}