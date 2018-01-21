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
 * File:   Steganifyer.cpp
 * Author: yacinehaoues
 * 
 * Created on November 6, 2017, 7:59 PM
 */

#include "Steganifyer.h"
#include <CommandContext.h>
#include <CommandChain.h>
#include <Command.h>
#include <Logger.h>
#include <iostream>
#include <vector>


namespace Impl {
    StringVector & initCommands();
    String CMD_STEGANIFY = "steganify";
    String COMMANDS[] = {CMD_STEGANIFY};
    static const String & STR_MODULE_ID ="STEGANIFYER-";
    static const StringVector & LST_COMMANDS = initCommands();

    ///-------------------------------------------------------------------------------------------------
    /// @fn StringVector & initCommands()
    ///
    /// @brief  Initializes the commands.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @return A reference to a StringVector.
    ///-------------------------------------------------------------------------------------------------

    StringVector & initCommands() {
        StringVector * cmds = new StringVector();
        for( unsigned int a = 0; a < sizeof(COMMANDS)/sizeof(COMMANDS[0]); a = a + 1 )
            cmds->push_back(COMMANDS[a]);
        return *cmds;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn Steganifyer::Steganifyer()
    ///
    /// @brief  Default constructor.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///-------------------------------------------------------------------------------------------------

    Steganifyer::Steganifyer() {
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn Steganifyer::~Steganifyer()
    ///
    /// @brief  Destructor.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///-------------------------------------------------------------------------------------------------

    Steganifyer::~Steganifyer() {
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn const String & Steganifyer::getID() const
    ///
    /// @brief  Gets the identifier.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @return The identifier.
    ///-------------------------------------------------------------------------------------------------

    const String & Steganifyer::getID() const {
        return STR_MODULE_ID;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn const StringVector& Steganifyer::getCommands() const
    ///
    /// @brief  Gets the commands.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @return The commands.
    ///-------------------------------------------------------------------------------------------------

    const StringVector& Steganifyer::getCommands() const {
        return LST_COMMANDS;
    }


    // call number
    bool called = false;

    ///-------------------------------------------------------------------------------------------------
    /// @fn void Steganifyer::handle(const API::Command *const cmd, API::CommandContext *const cmdCtx)
    ///
    /// @brief  Handles.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @param          cmd     The command.
    /// @param [in,out] cmdCtx  If non-null, context for the command.
    ///-------------------------------------------------------------------------------------------------
    
    void Steganifyer::handle(const API::Command *const cmd, API::CommandContext *const cmdCtx) {

        // Getting command chain
        API::CommandChain *const chain = cmdCtx->getChain();

        // read input data
        // Here read input data file(s) (Format TBD)

        // Searching for available data
        API::DataDescriptor * dDesc = cmdCtx->get("IMAGE_DATA_ITERATOR");
        if(dDesc == NULL && !called) {
            Info << "No Data Found, Asking to read and input file " << * cmd << " ...";
            chain->addCommand(new API::Command("read"));
            chain->addCommand(new API::Command(CMD_STEGANIFY));
            called = true; // limit tries to one call (no infinite loops)
            return;
        }

        // Processing found Data
        Info << "Processing data.";
        
        // Compressing
        // Crypting

        // Writing input data

    }
}

///-------------------------------------------------------------------------------------------------
/// @fn MODULE_EXPORT API::Module * create()
///
/// @brief  Creates a new API::Module*.
///
/// @author Yacine Haoues
/// @date   1/18/2018
///
/// @return Null if it fails, else a pointer to an API::Module.
///-------------------------------------------------------------------------------------------------

MODULE_EXPORT API::Module * create() {
    return new Impl::Steganifyer();
}

///-------------------------------------------------------------------------------------------------
/// @fn MODULE_EXPORT void destroy(const API::Module *const m)
///
/// @brief  Destroys the given m.
///
/// @author Yacine Haoues
/// @date   1/18/2018
///
/// @param  m   The m to destroy.
///-------------------------------------------------------------------------------------------------

MODULE_EXPORT void destroy(const API::Module *const m) {
    delete m;
}