#include <iostream>

#include <CLI/CLI.hpp>

int main(int argc, char **argv) {
    CLI::App app{"Application"};
    app.require_subcommand(1, 1);

    auto all = app.add_subcommand("do", "description");

    all->callback([&]() {
        std::cout 
        << "Done"
        << std::endl;
    });
    
    CLI11_PARSE(app, argc, argv);
}
