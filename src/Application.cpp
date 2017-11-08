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

#include <Application.h>
#include <ModulesManagers.h>
#include <CommandFactory.h>
#include <CommandChain.h>
#include <CommandContext.h>
#include <Module.h>

// Included Modules 
#include <Steganifyer.h>

// Included libs
#include <string>

namespace Global {

    //------------------------------------------------------------------------//
    // Constructor                                                            //
    //------------------------------------------------------------------------//

    Application::Application()
    : modulesManager(new Impl::ModulesManager()) {

    }

    //------------------------------------------------------------------------//
    // Desctructor                                                            //
    //------------------------------------------------------------------------//

    Application::~Application() {
        delete modulesManager;
    }

    //------------------------------------------------------------------------//
    // Start Method : method called to start the application                  //
    //                                                                        //
    // argumments : argc    int         I   numberof arguments                //
    //              av      const* []   I   command line params	              //
    //------------------------------------------------------------------------//

    void Application::start(int argc, char const* av[]) {
        // Create Command factory instance
        Impl::CommandFactory * const factory = new Impl::CommandFactory();
        // Parsing and creating command chain
        Impl::CommandChain * const chain = &factory->createCommandChain(argc, av);

        // Following code should be moved to some command handler
        Impl::Steganifyer * const steganifyer = new Impl::Steganifyer();
        modulesManager->registerModule(*steganifyer);

        API::CommandContext * cmdCtx = new API::CommandContext();
        const std::string command = "command";
        steganifyer->handle(command, *cmdCtx);

        // Cleaning Memory
        delete steganifyer;
        delete factory;
        delete cmdCtx;
        delete chain;
    }

    //------------------------------------------------------------------------//
    // getExecutionResult : Returms the results of the execution of the       //
    // Application                                                            //
    //------------------------------------------------------------------------//

    int Application::getExecutionResult() {
        return execResult;
    }
}