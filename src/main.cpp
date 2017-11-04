
#include <boost/program_options.hpp>
#include <iostream>

/* Program Options name space*/
using namespace boost::program_options;

int main(int ac, char const *av[]) {
    options_description desc("Allowed options");
    desc.add_options()
            ("help", "produce help message")
            ("compression", value<int>(), "set compression level");

    variables_map vm;
    store(parse_command_line(ac, av, desc), vm);
    notify(vm);

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
