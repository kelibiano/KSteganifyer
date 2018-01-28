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

#include <CommandContext.h>
#include <CommandChain.h>
#include <Application.h>

#include <Logger.h>
#include <Types.h>
#include <iostream>
namespace API {

    ///-------------------------------------------------------------------------------------------------
    /// @fn CommandContext::CommandContext(CommandChain * const mChain)
    ///
    /// @brief  Constructor
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param [in,out] mChain  If non-null, the chain.
    ///-------------------------------------------------------------------------------------------------

    CommandContext::CommandContext(Application *const app, CommandChain * const mChain):
        application(app),
        chain(mChain),
        dataMap(new DataMap()) {
        
        Info << "New Command Context Created ...";
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn CommandContext::~CommandContext()
    ///
    /// @brief  Destructor
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///-------------------------------------------------------------------------------------------------

    CommandContext::~CommandContext() {
        delete dataMap;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn Application *const CommandContext::getApplication() const
    ///
    /// @brief  Gets the Application
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @return The chain.
    ///-------------------------------------------------------------------------------------------------

    Application *const CommandContext::getApplication() const {
        return this->application;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn CommandChain *const CommandContext::getChain() const
    ///
    /// @brief  Gets the chain
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @return The chain.
    ///-------------------------------------------------------------------------------------------------

    CommandChain *const CommandContext::getChain() const {
        return this->chain;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn DataDescriptor *const CommandContext::get(String key) const
    ///
    /// @brief  Gets a constant using the given key
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param  key The key to get.
    ///
    /// @return A const.
    ///-------------------------------------------------------------------------------------------------

    DataDescriptor *const CommandContext::get(String key) const {
        DataMap::iterator ptr = dataMap->find(key);
        return ptr != dataMap->end() ? ptr->second : NULL;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn bool CommandContext::put(String key, DataDescriptor *const data)
    ///
    /// @brief  Puts
    ///
    /// @author Yacine Haoues
    /// @date   1/22/2018
    ///
    /// @param          key     The key.
    /// @param [in,out] data    If non-null, the data.
    ///
    /// @return True if it succeeds, false if it fails.
    ///-------------------------------------------------------------------------------------------------

    bool CommandContext::put(String key, DataDescriptor *const data) {
        dataMap->emplace(key, data);
        return true;
    }
}