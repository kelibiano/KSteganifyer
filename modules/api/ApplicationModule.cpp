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

#include <ApplicationModule.h>
#include <CommandContext.h>
#include <Application.h>
#include <ModulesManagers.h>
#include <ModuleFactory.h>
#include <Command.h>
#include <Logger.h>


#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

void readConfiguration(const API::Command *const cmd, API::CommandContext *const ctx) {
    Info << "Configuring...";
    // HERE READ THE CONFIGURATION FILE AND UPDATE THE CONFIGURATION
    // ctx->getConfiguration();
}


///-------------------------------------------------------------------------------------------------
/// @fn ModulesManager::ModulesArray * ModulesManager::findModulesInDir(const String dir) const
///
/// @brief  Searches for the first modules in dir
///
/// @author Yacine Haoues
/// @date   1/22/2018
///
/// @param  dir The dir.
///
/// @return Null if it fails, else the found modules in dir.
///-------------------------------------------------------------------------------------------------

API::ModulesArray * findModulesInDir(const String dir) 
{
    Info << "Searching for modules in " << dir << "/";
    API::ModulesArray * modules = new API::ModulesArray();

    fs::path path(dir.c_str());
    if (!fs::exists(path)) {
        Error << dir << " is not found in " << fs::current_path().c_str();
        return modules;
    }

    fs::directory_iterator end_iter;
    const API::ModuleFactory * factory = new API::ModuleFactory();

    for (fs::directory_iterator dir_itr(path); dir_itr != end_iter; ++dir_itr) {
        if (fs::is_regular_file(dir_itr->status())) {
            API::Module * module = factory->createModule(dir_itr->path().string().c_str());
            if (module)
            {
                modules->push_back(module);
            }
        }
    }
    delete factory;
    return modules;
}


void checkForModules(const API::Command *const cmd, API::CommandContext *const ctx) {
    Info << "Scanning for Modules...";
    // read modules from directory (config)
    const String libDir = String("libs");
    API::ModulesArray *modules = findModulesInDir(libDir);
    for (API::ModulesArray::iterator it = modules->begin(); it != modules->end(); it++)
        ctx->getApplication()->getModulesManager()->registerModule(*it);
}

API::ApplicationModule::ApplicationModule() : SimpleModule("ApplicationModule") {
    registerCommandHandler("configure", readConfiguration);
    registerCommandHandler("module_scan", checkForModules);
}