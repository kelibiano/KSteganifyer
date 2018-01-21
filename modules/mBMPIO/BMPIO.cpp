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
 * File:   BMPIO.cpp
 * Author: yacinehaoues
 * 
 * Created on November 14, 2017, 7:59 PM
 */

#include "BMPIO.h"
#include "BMPStructure.h"
#include <CommandContext.h>
#include <CommandChain.h>
#include <Command.h>
#include <Logger.h>
#include <Types.h>
#include <vector>

namespace Impl {

    const String STR_PARAM_INPUTFILE = "input-file";

    ///-------------------------------------------------------------------------------------------------
    /// @fn BMPIO::BMPIO()
    ///
    /// @brief  Default constructor.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///-------------------------------------------------------------------------------------------------

    BMPIO::BMPIO() : ID(new String("BMPIO-")), cmds(new StringVector()) {
        cmds->push_back("read");
        cmds->push_back("write");
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn BMPIO::~BMPIO()
    ///
    /// @brief  Destructor.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///-------------------------------------------------------------------------------------------------

    BMPIO::~BMPIO() {
        Info << "Cleaning BMPIO";
        delete ID;
        delete cmds;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn const String & BMPIO::getID() const
    ///
    /// @brief  Gets the identifier.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @return The identifier.
    ///-------------------------------------------------------------------------------------------------

    const String & BMPIO::getID() const {
        return *ID;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn const StringVector& BMPIO::getCommands() const
    ///
    /// @brief  Gets the commands.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @return The commands.
    ///-------------------------------------------------------------------------------------------------

    const StringVector& BMPIO::getCommands() const {
        return *cmds;
    }

    ///-------------------------------------------------------------------------------------------------
    /// @fn void BMPIO::handle(const API::Command *const cmd, API::CommandContext *const cmdCtx)
    ///
    /// @brief  Handles.
    ///
    /// @author Yacine Haoues
    /// @date   1/18/2018
    ///
    /// @param          cmd     The command.
    /// @param [in,out] cmdCtx  If non-null, context for the command.
    ///-------------------------------------------------------------------------------------------------

    void BMPIO::handle(const API::Command *const cmd, API::CommandContext *const cmdCtx) {

        // Checking the command (Another way is to found later, Strategy pattern maybe)
        if(cmd->getCommandString() != "read") {
            Error << "Command " << *cmd << " Not handled yet.";
            return;
        }

        // Searching the relevant parameters for the command
        API::CommandChain *const chain = cmdCtx->getChain();
        const String *const fname = chain->getParameter(STR_PARAM_INPUTFILE);
        if(fname == NULL) {
            Error << "No input BMP file found !";
            return;
        }

        // read the BMP
        Info << "Reading " << *fname << " ...";
        BMPStructure *const bmpStrcut = new BMPStructure(*fname);

        // Save BMP in the command context
        cmdCtx->put("IMAGE_DATA_ITERATOR", new API::DataDescriptor("RGB_IIERATOR", bmpStrcut));
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
    return new Impl::BMPIO();
}

///-------------------------------------------------------------------------------------------------
/// @fn MODULE_EXPORT void destroy(API::Module * m)
///
/// @brief  Destroys the given m.
///
/// @author Yacine Haoues
/// @date   1/18/2018
///
/// @param [in,out] m   If non-null, the m to destroy.
///-------------------------------------------------------------------------------------------------

MODULE_EXPORT void destroy(const API::Module *const m) {
    delete m;
}

