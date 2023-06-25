#include <algorithm>

#include "core/DirectoryGroupScan.h"

#include "core/HashXxh3.h"

namespace core {

void DirectoryGroupScan::scan(const std::vector<std::filesystem::path> & fileGroup) {
    HashXxh3 hash;
    std::vector<std::filesystem::path> directories;

    for (auto & path : fileGroup) {
        directories.push_back(path.parent_path());
    }
    
    for (auto & path : directories) {
        hash.update(path.string().data());
    }

    auto digest = hash.digest();

    auto & group = _directoryGroups[digest];
    if (group.directories.empty()) {
        group.directories = directories;
        group.names = fileGroup.front().filename();
    } else {
        group.names += ", " + fileGroup.front().filename().string();
    }
}

std::vector<DirectoryGroup> DirectoryGroupScan::groups() const {
    std::vector<DirectoryGroup> result;
    
    for (auto & group : _directoryGroups) {
        result.emplace_back(std::move(group.second));
    }

    std::sort(std::begin(result), std::end(result), [](auto & l, auto & r) {return l.names > r.names;});

    return result;
}

}