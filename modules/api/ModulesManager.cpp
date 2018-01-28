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



#include <ModulesManagers.h>
#include <ModuleFactory.h>
#include <Module.h>
#include <Command.h>
#include <Logger.h>

namespace API
{

///-------------------------------------------------------------------------------------------------
/// @fn bool ModulesManager::registerModule(Module *const module)
///
/// @brief  Registers the module described by module
///
/// @author Yacine Haoues
/// @date   1/22/2018
///
/// @param [in,out] module  If non-null, the module.
///
/// @return True if it succeeds, false if it fails.
///-------------------------------------------------------------------------------------------------

bool ModulesManager::registerModule(Module *const module)
{
    // Register commands
    const StringVector& commands = module->getCommands();
    for (size_t i = 0; i < commands.size(); i++) {
        this->commands->emplace(commands.at(i), module);
    }

    // register module
    this->modules->push_back(module);

    // for the moment let's return true
    return true;
}

///-------------------------------------------------------------------------------------------------
/// @fn bool ModulesManager::unregisterModule(Module *const module)
///
/// @brief  Unregisters the module described by module
///
/// @author Yacine Haoues
/// @date   1/22/2018
///
/// @param [in,out] module  If non-null, the module.
///
/// @return True if it succeeds, false if it fails.
///-------------------------------------------------------------------------------------------------

bool ModulesManager::unregisterModule(Module *const module)
{
    return true;
}

///-------------------------------------------------------------------------------------------------
/// @fn Module *const ModulesManager::getModuleForCommand(const Command *const cmd) const
///
/// @brief  Gets module for command
///
/// @author Yacine Haoues
/// @date   1/22/2018
///
/// @param  cmd The command.
///
/// @return The module for command.
///-------------------------------------------------------------------------------------------------

Module *const ModulesManager::getModuleForCommand(const Command *const cmd)
    const
{
    ModulesMap::iterator found = this->commands->find(cmd->getCommandString());
    if (found != this->commands->end()) {
        return found->second;
    }
    return NULL;
}

///-------------------------------------------------------------------------------------------------
/// @fn ModulesManager::ModulesManager() : commands(new std::map<String, Module *const>()), modules(new ModulesArray())
///
/// @brief  Default constructor
///
/// @author Yacine Haoues
/// @date   1/22/2018
///-------------------------------------------------------------------------------------------------

ModulesManager::ModulesManager()
    : commands(new std::map<String, Module *const>()),
      modules(new ModulesArray()) {
}

///-------------------------------------------------------------------------------------------------
/// @fn ModulesManager::~ModulesManager()
///
/// @brief  Destructor
///
/// @author Yacine Haoues
/// @date   1/22/2018
///-------------------------------------------------------------------------------------------------

ModulesManager::~ModulesManager()
{
    for (Module * module : *(this->modules)) {
        Callback * clean = module->getCleanCallback();
        if (clean) {
            (*clean)(module);
            delete clean;
        }
        else {
            Error << "Module Could not be cleaned. Memory leaks may occur.";
        }
    }
    delete this->modules;
    delete this->commands;
}
}