#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include <iostream>
#include <fstream>

#include "core/DirectoryScan.h"
#include "core/DirectoryGroupScan.h"

namespace {
    void createFile(const std::filesystem::path & path, const std::string & data) {
        std::ofstream(path.c_str()) << data;
    }
}

TEST_CASE ("TestDuplicates1") {
    auto temp = std::filesystem::temp_directory_path() / "dsearch1";
    auto dirA = temp / "DirA";
    auto dirB = temp / "DirB";
    auto dirBB = dirB / "DirBB";
    auto dirC = temp / "DirC";
    auto dirCC = dirC / "DirCC";

    std::filesystem::create_directory(temp);
    std::filesystem::create_directory(dirA);
    std::filesystem::create_directory(dirB);
    std::filesystem::create_directory(dirC);
    std::filesystem::create_directory(dirBB);
    std::filesystem::create_directory(dirCC);

    createFile(dirA / "X", "abcd");
    createFile(dirA / "Y", "abcd");
    createFile(dirA / "Z", "abcd");

    createFile(dirB / "X", "abcd");
    createFile(dirB / "Y", "abcd");
    createFile(dirB / "Z", "abcd");

    createFile(dirBB / "X", "abcd");
    createFile(dirBB / "Y", "abcd");
    createFile(dirBB / "YY", "abcd");

    createFile(dirC / "Z", "abcd");

    createFile(dirCC / "X", "abcd");
    createFile(dirCC / "Y", "abcd");
    createFile(dirCC / "YY", "abcd");
    createFile(dirCC / "ZZ", "abcd");

    core::DirectoryScan directoryScan(std::cout);
    auto duplicates = directoryScan.scan(temp);

    core::DirectoryGroupScan directoryGroupScan;
    for (const auto & group : duplicates) {
        directoryGroupScan.scan(group);
    }

    auto groups = directoryGroupScan.groups();
    
    for (auto & group : groups) {
        std::cout <<  group;
    }

    CHECK(groups.size() == 3);

    // std::filesystem::remove_all(temp);
}
