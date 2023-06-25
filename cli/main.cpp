#include <iostream>

#include <CLI/CLI.hpp>

#include "core/DriectoryScan.h"

void duplicatesSearch(const std::string & directoryPath) {
    std::cout << "Search duplicates in " << directoryPath << std::endl;

    core::DirectoryScan directoryScan(std::cout);
    
    for (auto & duplicateGroup : directoryScan.scan(directoryPath)) {
        std::cout <<  duplicateGroup.names << ":\n";

        for (const auto & directory : duplicateGroup.directories) {
            std::cout << "\t" << directory << "\n";
        }
    }
}

int main(int argc, char **argv) {
    CLI::App app{"dsearch"};

    std::string directory = std::filesystem::current_path().string();
    auto duplicates = app.add_option("-d,--directory", directory);
    CLI11_PARSE(app, argc, argv);

    duplicatesSearch(directory);
}
