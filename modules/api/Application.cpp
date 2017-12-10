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
 * File:   Application.cpp
 * Author: yacinehaoues
 *
 * Created on November 8, 2017, 20 PM
 */
#include <Types.h>
#include <Application.h>
#include <ModulesManagers.h>
#include <CommandFactory.h>
#include <CommandChain.h>
#include <CommandContext.h>
#include <Command.h>
#include <Module.h>
#include <Logger.h>

// Included Modules 
#include <Steganifyer.h>
// Included libs
#include<iostream>

namespace API {

    //------------------------------------------------------------------------//
    // Constructor                                                            //
    //------------------------------------------------------------------------//
    Application::Application()
    : modulesManager(new ModulesManager()) {

    }

    //------------------------------------------------------------------------//
    // Desctructor                                                            //
    //------------------------------------------------------------------------//
    Application::~Application() {
        delete modulesManager;
    }

    const int Application::initializeModules() {
        // Check and update modules cache here
        const int nbModules = modulesManager->initializeModules();
        if(nbModules < 1) {
            Error << "No Modules has been found!";
            execResult = -1;
        }
        return nbModules;
    }

    //------------------------------------------------------------------------//
    // Start Method : method called to start the application                  //
    //                                                                        //
    // argumments : argc    int         I   numberof arguments                //
    //              av      const* []   I   command line params	              //
    //------------------------------------------------------------------------//
    void Application::start(int argc, char const* av[]) {

        if(execResult < 0){
            return;
        }
        // Create Command factory instance
        CommandFactory *const factory = new CommandFactory();
        // Parsing and creating command chain
        CommandChain *const chain = factory->createCommandChain(argc, av);
        // initializing context
        CommandContext *const cmdCtx = new CommandContext(chain);
        
        // Processing commands
        while(chain->hasCommands()) {
            Command const* cmd = chain->nextCommand();
            Module *const module = modulesManager->getModuleForCommand(cmd);
            if(module != NULL) {
                module->handle(cmd, cmdCtx);
            } else {
                Error << "None of the known Modules handles the command " << *cmd;
            }
            delete cmd;
        }

        // Cleaning Memory
        Info << "Cleaning...";
        delete factory;
        delete cmdCtx;
        delete chain;
        Info << "Done.";
    }

    //------------------------------------------------------------------------//
    // getExecutionResult : Returms the results of the execution of the       //
    // Application                                                            //
    //------------------------------------------------------------------------//
    const int Application::getExecutionResult() {
        return execResult;
    }
}