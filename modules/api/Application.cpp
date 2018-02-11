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
#include <ApplicationModule.h>
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
#include <iostream>

namespace API {

    ///-------------------------------------------------------------------------------------------------
    /// @fn Application::Application()
    ///
    /// @brief  Default constructor
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///-------------------------------------------------------------------------------------------------

    Application::Application(): 
        modulesManager(new ModulesManager()), 
        execResult(0) {
        modulesManager->registerModule(new ApplicationModule());
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn Application::~Application()
    ///
    /// @brief  Destructor
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///-------------------------------------------------------------------------------------------------

    Application::~Application() {
        delete modulesManager;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn void Application::start(int argc, char const* av[])
    ///
    /// @brief  Starts
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param  argc    The argc.
    /// @param  av      The av.
    ///-------------------------------------------------------------------------------------------------

    void Application::start(int argc, char const* av[]) {

        if(execResult < 0){
            return;
        }
        // Create Command factory instance
        CommandFactory *const factory = new CommandFactory();
        // Parsing and creating command chain
        CommandChain *const chain = factory->createCommandChain(argc, av);
        // initializing context
        CommandContext *const cmdCtx = new CommandContext(this, chain);
        
        // Processing commands
        while(chain->hasCommands()) {
            Command const* cmd = chain->nextCommand();
            runCommand(cmd, cmdCtx);
            delete cmd;
        }

        // Cleaning Memory
        Info << "Cleaning...";
        delete factory;
        delete cmdCtx;
        delete chain;
        Info << "Done.";
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn void Application::runCommand(Command const* cmd, CommandContext *const ctx)
    ///
    /// @brief  Executes the command operation
    ///
    /// @author Yacine Haoues
    /// @date   1/30/2018
    ///
    /// @param          cmd The command.
    /// @param [in,out] ctx If non-null, the context.
    ///-------------------------------------------------------------------------------------------------

    void Application::runCommand(Command const*  cmd, CommandContext *const ctx) {
        Module *const module = modulesManager->getModuleForCommand(cmd);
        if (module != NULL) {
            module->handle(cmd, ctx);
        }
        else {
            Error << "None of the known Modules handles the command " << *cmd;
        }
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn const int Application::getExecutionResult()
    ///
    /// @brief  Gets execution result
    /// 
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @return The execution result.
    ///-------------------------------------------------------------------------------------------------

    const int Application::getExecutionResult() {
        return execResult;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn const int Application::getModulesManager()
    ///
    /// @brief  Gets Module Manager
    /// 
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @return the Modules Manager
    ///-------------------------------------------------------------------------------------------------

    ModulesManager *const Application::getModulesManager() const {
        return this->modulesManager;
    }
}