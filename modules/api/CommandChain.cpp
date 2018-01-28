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
#include <Logger.h>
namespace API {

    const String STR_EMPTY = "";

    ///-------------------------------------------------------------------------------------------------
    /// @fn CommandChain::CommandChain()
    ///
    /// @brief  Default constructor
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///-------------------------------------------------------------------------------------------------

    CommandChain::CommandChain() : 
        commands(new CommandsQueue()),
        parameters(new StringMap()) {

        Info << "New Command Chain Created ...";
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn CommandChain::~CommandChain()
    ///
    /// @brief  Destructor
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///-------------------------------------------------------------------------------------------------

    CommandChain::~CommandChain() {

    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn void CommandChain::addCommand(Command *const cmd)
    ///
    /// @brief  Adds a command
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param [in,out] cmd If non-null, the command.
    ///-------------------------------------------------------------------------------------------------

    void CommandChain::addCommand(Command *const cmd) {
        commands->push(cmd);
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn void CommandChain::addParameter(const String param)
    ///
    /// @brief  Adds a parameter
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param  param   The parameter.
    ///-------------------------------------------------------------------------------------------------

    void CommandChain::addParameter(const String param) {
        Info << "Parameter : " << param;
        parameters->emplace(param, STR_EMPTY);
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn void CommandChain::addParameter(const String param, const String value)
    ///
    /// @brief  Adds a parameter to 'value'
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param  param   The parameter.
    /// @param  value   The value.
    ///-------------------------------------------------------------------------------------------------

    void CommandChain::addParameter(const String param, const String value) {
        Info << "Parameter : " << param <<'\t'<<"Value : "<< value;
        parameters->emplace(param, value);
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn String *const CommandChain::getParameter(const String param) const
    ///
    /// @brief  Gets a parameter
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param  param   The parameter.
    ///
    /// @return The parameter.
    ///-------------------------------------------------------------------------------------------------

    String *const CommandChain::getParameter(const String param) const {
        StringMap::iterator it = parameters->find(param);
        return it != parameters->end() ? new String(it->second) : NULL;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn bool CommandChain::hasParamerter(const String param) const
    ///
    /// @brief  Query if 'param' has paramerter
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param  param   The parameter.
    ///
    /// @return True if paramerter, false if not.
    ///-------------------------------------------------------------------------------------------------

    bool CommandChain::hasParamerter(const String param) const {
        return parameters->find(param) != parameters->end();
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn bool CommandChain::hasCommands()
    ///
    /// @brief  Query if this object has commands
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @return True if commands, false if not.
    ///-------------------------------------------------------------------------------------------------

    bool CommandChain::hasCommands() {
        return !commands->empty();
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn Command const* CommandChain::nextCommand()
    ///
    /// @brief  Next command
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @return Null if it fails, else a pointer to a const.
    ///-------------------------------------------------------------------------------------------------

    Command const* CommandChain::nextCommand() {
        Command  const* cmd = commands->front();
        commands->pop();
        return cmd;
    }
}