#include <iostream>

#include <CLI/CLI.hpp>

#include "core/DirectoryScan.h"
#include "core/DirectoryGroupScan.h"

void duplicatesSearch(const std::string & directoryPath) {
    std::cout << "Search duplicates in " << directoryPath << std::endl;

    core::DirectoryScan directoryScan(std::cout);
    auto duplicates = directoryScan.scan(directoryPath);

    core::DirectoryGroupScan directoryGroupScan;
    for (const auto & group : duplicates) {
        directoryGroupScan.scan(group);
    }

    for (auto & group : directoryGroupScan.groups()) {
        std::cout << group;
    }
}

int main(int argc, char **argv) {
    CLI::App app{"dsearch"};

    std::string directory = std::filesystem::current_path().string();
    auto duplicates = app.add_option("-d,--directory", directory);
    CLI11_PARSE(app, argc, argv);

    duplicatesSearch(directory);
}
