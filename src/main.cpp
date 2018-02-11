
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

//--- Third party includes -------------------------------------------------- //
#include <iostream>
//--- Project party includes ------------------------------------------------ //
#include <Application.h>
#include <Logger.h>

//--- Forward declaration --------------------------------------------------- //
void printStrillInWorkMessage();


///-------------------------------------------------------------------------------------------------
/// @fn int main(int ac, char const *av[])
///
/// @brief  Main entry-point for this application
///
/// @author Yacine Haoues
/// @date   1/22/2018
///
/// @param  ac  The number of command-line arguments provided.
/// @param  av  An array of command-line argument strings.
///
/// @return Exit-code for the process - 0 for success, else an error code.
///-------------------------------------------------------------------------------------------------

int main(int ac, char const *av[]) {
    // Print still in work 
    printStrillInWorkMessage();

    // Initialize and start application
    API::Application * const application = new API::Application();
    application->start(ac, av);
    int result = application->getExecutionResult();

    // Cleaning Memory
    delete application;
    
    // End of program
    return result;
}

///-------------------------------------------------------------------------------------------------
/// @fn void printStrillInWorkMessage()
///
/// @brief  Prints strill in work message
///
/// @author Yacine Haoues
/// @date   1/22/2018
///-------------------------------------------------------------------------------------------------
void printStrillInWorkMessage() {
    std::cout << '\n';
    std::cout << "****************************************************" << '\n';
    std::cout << "*                                                  *" << '\n';
    std::cout << "*                  K-STEGANIFYER                   *" << '\n';
    std::cout << "*                                           v1.0.x *" << '\n';
    std::cout << "****************************************************" << '\n';
    std::cout << "* We are still Building ...                        *" << '\n';
    std::cout << "****************************************************" << '\n';
    std::cout << '\n';
}

