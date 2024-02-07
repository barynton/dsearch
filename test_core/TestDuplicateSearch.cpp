#include <filesystem>
#include <fstream>
#include <iostream>

#include <catch2/catch_test_macros.hpp>

#include "core/facade/FileGroupsScan.h"

namespace {
    void createFile(const std::filesystem::path & path, const std::string & data) {
        std::ofstream(path.c_str()) << data;
    }

    std::filesystem::path createDir(const std::filesystem::path & path) {
        std::filesystem::create_directory(path);
        return path;
    }
}

TEST_CASE ("Name") {
    auto temp = createDir(std::filesystem::temp_directory_path() / "dsearchName");
    auto dirA = createDir(temp / "dirA");
    auto dirB = createDir(temp / "dirB");

    createFile(dirA / "B", "fabcd");
    createFile(dirA / "C", "afbed");
    createFile(dirB / "B", "abcd");
    createFile(dirB / "A", "adbcd");
    createFile(dirB / "C", "avbcd");

    core::FileGroupsScan fileGroupsScan(std::cout, {"name"});
    auto groups = fileGroupsScan.scan(temp);

    CHECK(groups.size() == 2);

    core::DuplicateSearch::Groups expectedGroups = {
        {
            dirA / "B",
            dirB / "B"
        },
        {
            dirA / "C",
            dirB / "C"
        }
    };

    CHECK(groups == expectedGroups);

    std::error_code ec;
    std::filesystem::remove_all(temp, ec);
}

TEST_CASE ("Size") {
    auto temp = createDir(std::filesystem::temp_directory_path() / "dsearchSize");
    auto dirA = createDir(temp / "dirA");
    auto dirB = createDir(temp / "dirB");

    createFile(dirA / "A", "fadfabdcd");
    createFile(dirA / "B", "afasbed");
    createFile(dirB / "B", "adbcd");
    createFile(dirB / "A", "avbcd");

    core::FileGroupsScan fileGroupsScan(std::cout, {"size"});
    auto groups = fileGroupsScan.scan(temp);

    CHECK(groups.size() == 1);

    core::DuplicateSearch::Groups expectedGroups = {
        {
            dirB / "A",
            dirB / "B"
        }
    };

    CHECK(groups == expectedGroups);

    std::error_code ec;
    std::filesystem::remove_all(temp, ec);
}

TEST_CASE ("Head") {
    auto temp = createDir(std::filesystem::temp_directory_path() / "dsearchHead");
    auto dirA = createDir(temp / "dirA");

    createFile(dirA / "A", "abcd");
    createFile(dirA / "B", "abed");
    createFile(dirA / "C", "abcd");

    core::FileGroupsScan fileGroupsScan(std::cout, {"head"});
    auto groups = fileGroupsScan.scan(temp);

    CHECK(groups.size() == 1);

    core::DuplicateSearch::Groups expectedGroups = {
        {
            dirA / "A",
            dirA / "C",
        }
    };

    CHECK(groups == expectedGroups);

    std::error_code ec;
    std::filesystem::remove_all(temp, ec);
}

TEST_CASE ("Hash") {
    auto temp = createDir(std::filesystem::temp_directory_path() / "dsearchHash");
    auto dirA = createDir(temp / "dirA");
    auto dirB = createDir(temp / "dirB");
    auto dirC = createDir(temp / "dirC");

    createFile(dirA / "A", "abcd");
    createFile(dirA / "B", "abed");
    createFile(dirA / "C", "abcd");
    createFile(dirB / "A", "abcd");
    createFile(dirB / "B", "abcd");
    createFile(dirB / "C", "abcd");
    createFile(dirC / "C", "abcd");

    core::FileGroupsScan fileGroupsScan(std::cout, {"hash"});
    auto groups = fileGroupsScan.scan(temp);

    CHECK(groups.size() == 1);

    core::DuplicateSearch::Groups expectedGroups = {
        {
            dirA / "A",
            dirA / "C",
            dirB / "A",
            dirB / "B",
            dirB / "C",
            dirC / "C"
        }
    };

    CHECK(groups == expectedGroups);

    std::error_code ec;
    std::filesystem::remove_all(temp, ec);
}

TEST_CASE ("StandardAlgorithmsRecurrent") {
    auto temp =     createDir(std::filesystem::temp_directory_path() / "dsearchStandardAlgorithmsRecurrent");
    auto dirA =     createDir(temp / "dirA");
    auto dirB =     createDir(temp / "dirB");
    auto dirBB =    createDir(dirB / "dirBB");
    auto dirC =     createDir(temp / "dirC");
    auto dirCC =    createDir(dirC / "dirCC");

    createFile(dirA / "A", "abcd");
    createFile(dirA / "B", "abcd");
    createFile(dirA / "C", "abcde");
    createFile(dirB / "A", "abcd");
    createFile(dirB / "B", "abcd");
    createFile(dirB / "C", "abcd");
    createFile(dirBB / "A", "abcd");
    createFile(dirBB / "B", "abcd");
    createFile(dirBB / "BB", "abcd");
    createFile(dirC / "C", "abcd");
    createFile(dirCC / "A", "abcd");
    createFile(dirCC / "B", "abcd");
    createFile(dirCC / "BB", "abcd");
    createFile(dirCC / "CC", "abcd");

    core::FileGroupsScan fileGroupsScan(std::cout, {"name", "size", "head", "hash"});
    auto groups = fileGroupsScan.scan(temp);

    CHECK(groups.size() == 4);

    core::DuplicateSearch::Groups expectedGroups = {
        {
            dirA / "A",
            dirB / "A",
            dirBB / "A",
            dirCC / "A"
        },
        {
            dirA / "B",
            dirB / "B",
            dirBB / "B",
            dirCC / "B"
        },
        {
            dirB / "C",
            dirC / "C",
        },
        {
            dirBB / "BB",
            dirCC / "BB"
        }
    };

    CHECK(groups == expectedGroups);

    std::error_code ec;
    std::filesystem::remove_all(temp, ec);
}