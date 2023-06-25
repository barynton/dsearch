#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace core {

struct DirectoryGroup {
    std::string names;
    std::vector<std::filesystem::path> directories;
};

class DirectoryGroupScan {
public:
    void scan(const std::vector<std::filesystem::path> & fileGroup);

    std::vector<DirectoryGroup> groups() const;

private:
    std::unordered_map<int64_t, DirectoryGroup>  _directoryGroups;
};

}
