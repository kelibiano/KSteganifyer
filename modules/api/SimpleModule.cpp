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

#include <SimpleModule.h>
#include <Command.h>
#include <CommandContext.h>

///-------------------------------------------------------------------------------------------------
/// @fn API::SimpleModule::SimpleModule(const String & mName)
///
/// @brief  Constructor
///
/// @author Yacine Haoues
/// @date   1/30/2018
///
/// @param  mName   The name.
///-------------------------------------------------------------------------------------------------

API::SimpleModule::SimpleModule(const String & mName) {

}

///-------------------------------------------------------------------------------------------------
/// @fn API::SimpleModule::~SimpleModule()
///
/// @brief  Destructor
///
/// @author Yacine Haoues
/// @date   1/30/2018
///-------------------------------------------------------------------------------------------------

API::SimpleModule::~SimpleModule() {

}

///-------------------------------------------------------------------------------------------------
/// @fn const String & API::SimpleModule::getID() const
///
/// @brief  Gets the identifier
///
/// @author Yacine Haoues
/// @date   1/30/2018
///
/// @return The identifier.
///-------------------------------------------------------------------------------------------------

const String & API::SimpleModule::getID() const {
    return String("Module");
}

///-------------------------------------------------------------------------------------------------
/// @fn StringVector&  API::SimpleModule::getCommands() const
///
/// @brief  Gets the list of the commands within the current module
///
/// @author Yacine Haoues
/// @date   1/28/2018
///
///
/// @return Emplty vector of Strings, else a filled one with commands strings.
///-------------------------------------------------------------------------------------------------
const StringVector&  API::SimpleModule::getCommands() const {
    StringVector * v = new StringVector();
    for (CommandHandlersMap::const_iterator it = handlers.begin(); it != handlers.end(); ++it) {
        v->push_back(it->first);
    }
    return *v;
}

///-------------------------------------------------------------------------------------------------
/// @fn void API::SimpleModule::registerCommandHandler(const String & cmd, CommandHandler hndlr)
///
/// @brief  Registers the command handler
///
/// @author Yacine Haoues
/// @date   1/30/2018
///
/// @param  cmd     The command.
/// @param  hndlr   The hndlr.
///-------------------------------------------------------------------------------------------------

void API::SimpleModule::registerCommandHandler(const String & cmd, CommandHandler hndlr) {
    handlers[cmd] = hndlr; // register command
}

///-------------------------------------------------------------------------------------------------
/// @fn API::CommandHandler API::SimpleModule::getCommandHandler(const String& cmd)
///
/// @brief  Handler, called when the get command
///
/// @author Yacine Haoues
/// @date   1/30/2018
///
/// @param  cmd The command.
///
/// @return The command handler.
///-------------------------------------------------------------------------------------------------

API::CommandHandler API::SimpleModule::getCommandHandler(const String& cmd) {
    return handlers[cmd];
}

///-------------------------------------------------------------------------------------------------
/// @fn void API::SimpleModule::handle(const Command *const cmd, CommandContext *const ctx)
///
/// @brief  Handles
///
/// @author Yacine Haoues
/// @date   1/30/2018
///
/// @param          cmd The command.
/// @param [in,out] ctx If non-null, the context.
///-------------------------------------------------------------------------------------------------

void  API::SimpleModule::handle(const Command *const cmd, CommandContext *const ctx) {
    this->getCommandHandler(cmd->getCommandString())(cmd, ctx);

}

