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

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

namespace API
{

//------------------------------------------------------------------------//
// registerModule : Method used to register a modules in the manager, the //
// registered mosules can be retrieved by commands.                       //
//                                                                        //
// argumments   : module  Module *const   I   Module to be registered     //
// return       : bool    if the module has been registered successfully  //
//------------------------------------------------------------------------//
bool ModulesManager::registerModule(Module *const module)
{
    // Register commands
    const StringVector commands = module->getCommands();
    for (size_t i = 0; i < commands.size(); i++) {
        this->commands->emplace(commands.at(i), module);
    }

    // register module
    this->modules->push_back(module);

    // for the moment let's return true
    return true;
}

//------------------------------------------------------------------------//
// unregisterModule : Method used to unregister a modules from the        //
// manager.                                                               //
//                                                                        //
// argumments   : module Module *const   I   Module to be unregistered    //
// return       : bool   if the module has been unregistered successfully //
//------------------------------------------------------------------------//
bool ModulesManager::unregisterModule(Module *const module)
{
    return true;
}

//------------------------------------------------------------------------//
// getModuleForCommand : Retrieves The module that handles the given      //
// command as input (if it exists)                                        //
// argumments : I   cmd     Command *const  Command to be looked          //
// return     : Module *const   The module that handles the command. if   //
//                              no modules are found then NULL            //
//------------------------------------------------------------------------//
Module *const ModulesManager::getModuleForCommand(const Command *const cmd)
    const
{
    ModulesMap::iterator found = this->commands->find(cmd->getCommandString());
    if (found != this->commands->end()) {
        return found->second;
    }
    return NULL;
}

//------------------------------------------------------------------------//
// findModulesInDir : scans the given folder for modules and loads them   //
// argumments : I   dir     const String : folder to be scanned           //
// return     : ModulesArray List of the found modules                    //
//------------------------------------------------------------------------//
ModulesManager::ModulesArray * 
                ModulesManager::findModulesInDir(const String dir) const
{
    Info << "Searching for modules in " << dir << "/";
    ModulesArray * modules = new ModulesArray();

    fs::path path(dir.c_str());
    if (!fs::exists(path)) {
        Error << dir << " is not found in " << fs::current_path().c_str();
        return modules;
    }

    fs::directory_iterator end_iter;
    const ModuleFactory * factory = new ModuleFactory();

    for (fs::directory_iterator dir_itr(path); dir_itr != end_iter; ++dir_itr) {
        if (fs::is_regular_file(dir_itr->status())) {
            Module * module = factory->createModule(dir_itr->path().string().c_str());
            if (module)
            {
                modules->push_back(module);
            } 
        }
    }
    delete factory;
    return modules;
}

//------------------------------------------------------------------------//
// initializeModules : Initializes the manager and registers mocules into //
// it with some logic (for the momen in a static way).                    //
// return     : int     : the number of registered modules                //
//------------------------------------------------------------------------//
const int ModulesManager::initializeModules()
{
    // read modules from directory
    const String libDir = String("libs");
    ModulesArray *modules = findModulesInDir(libDir);
    for (ModulesArray::iterator it = modules->begin(); it != modules->end(); it++)
        registerModule(*it);

    return modules->size();
}

//------------------------------------------------------------------------//
// Constructor                                                            //
//------------------------------------------------------------------------//
ModulesManager::ModulesManager()
    : commands(new std::map<String, Module *const>()),
      modules(new ModulesArray()) {
}

//------------------------------------------------------------------------//
// Desctructor                                                            //
//------------------------------------------------------------------------//
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