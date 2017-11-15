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
#include <Module.h>
#include <Command.h>

#include <Steganifyer.h>
#include <BMPIO.h>

namespace API {

    //------------------------------------------------------------------------//
    // registerModule : Method used to register a modules in the manager, the //
    // registered mosules can be retrieved by commands.                       //
    //                                                                        //
    // argumments   : module  Module *const   I   Module to be registered     //
    // return       : bool    if the module has been registered successfully  //
    //------------------------------------------------------------------------//
    bool ModulesManager::registerModule(Module *const module) {
        const StringVector commands = module->getCommands();
        for(int i = 0; i < commands.size(); i++) {
            modules->emplace(commands.at(i), module);
        }
        // for the moment let's retutn true
        return true;
    }

    //------------------------------------------------------------------------//
    // unregisterModule : Method used to unregister a modules from the        //
    // manager.                                                               //
    //                                                                        //
    // argumments   : module Module *const   I   Module to be unregistered    //
    // return       : bool   if the module has been unregistered successfully //
    //------------------------------------------------------------------------//
    bool ModulesManager::unregisterModule(Module *const module) {
        
        return true;
    }

    //------------------------------------------------------------------------//
    // getModuleForCommand : Retrieves The module that handles the given      //                                                               //
    // command as input (if it exists)                                        //
    // argumments : I   cmd     Command *const  Command to be looked          //
    // return     : Module *const   The module that handles the command. if   //
    //                              no modules are found then NULL            //
    //------------------------------------------------------------------------//
    Module *const ModulesManager::getModuleForCommand(const Command *const cmd) 
    const {
        ModulesMap::iterator found = modules->find(cmd->getCommandString());
        if(found != modules->end()) {
            return found->second;
        } else {
            return NULL;
        }
    }

    //------------------------------------------------------------------------//
    // initializeModules : Initializes the manager and registers mocules into //
    // it with some logic (for the momen in a static way).                    //
    // return     : int     : the number of registered modules                //
    //------------------------------------------------------------------------//
    const int ModulesManager::initializeModules() {
        registerModule(new Impl::Steganifyer());
        registerModule(new Impl::BMPIO());
        return modules->size();
    }

    //------------------------------------------------------------------------//
    // Constructor                                                            //
    //------------------------------------------------------------------------//
    ModulesManager::ModulesManager()
    : modules(new std::map<String, Module *const>()){
        
    }

    //------------------------------------------------------------------------//
    // Desctructor                                                            //
    //------------------------------------------------------------------------//
    ModulesManager::~ModulesManager() {
        for(ModulesMap::iterator it = modules->begin(); it != modules->end(); ++it) {
            // TODO : review here "delete it->second";
        }
        delete modules;
    }
}