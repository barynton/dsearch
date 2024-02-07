#include <iostream>

#include <CLI/CLI.hpp>

#include "core/facade/FileGroupsScan.h"

namespace {
    const std::vector<std::string> standardAlgorithms = {"name", "size", "head", "hash"};
}

void duplicatesSearch(const std::string & directoryPath, const std::vector<std::string> & algorithms) {
    std::cout << "Search duplicates in " << directoryPath << std::endl;

    core::FileGroupsScan fileGroupsScan(std::cout, algorithms);
    auto duplicates = fileGroupsScan.scan(directoryPath);

    for (const auto & group : duplicates) {
        for (const auto & file : group) {
            std::cout << file << "\n";
        }
        std::cout << "\n";
    }
}

int main(int argc, char **argv) {
    CLI::App app{"dsearch"};

    std::string directory = std::filesystem::current_path().string();
    std::vector<std::string> algorithms = standardAlgorithms;
    app.add_option("-d,--directory", directory);
    app.add_option("-als,--algorithms", algorithms);

    CLI11_PARSE(app, argc, argv);

    duplicatesSearch(directory, algorithms);
}
