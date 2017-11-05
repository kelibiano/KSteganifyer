
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


/*****************************************************+* Third party includes */
#include <boost/program_options.hpp>
#include <iostream>

/***************************************************** Project party includes */
#include <Module.h>


using namespace boost::program_options;


struct myclass {           // function object type:
  void operator() (variables_map::value_type & i) {std::cout << i.first << std::endl;}
} myobject;


int main(int ac, char const *av[]) {
    options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
                ("compression", value<int>(), "set compression level");

    variables_map vm;
    store(parse_command_line(ac, av, desc), vm);
    notify(vm);

    
    std::for_each(vm.begin(), vm.end(), myobject);
    std::cout << "params : " <<vm.size() << std::endl;
    
    if (vm.count("compression")) {
        std::cout << "Compression level was set to "
                << vm["compression"].as<int>() << ".\n";
    } else {
        std::cout << "Compression level was not set.\n";
    }
    /* We are still Building ...*/
    std::cout << "/* We are still Building ... */" << '\n';
    return 0;
}

