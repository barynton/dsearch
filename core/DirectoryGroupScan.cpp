#include <algorithm>

#include <iostream>
#include "core/DirectoryGroupScan.h"

#include "core/HashXxh3.h"

namespace core {

std::ostream & operator<<(std::ostream & stream, const DirectoryGroup & group) {
    stream << group.names.front();
    
    for (auto i = 1; i < group.names.size(); ++i) {
        stream << ", " << group.names[i];
    }    

    stream << ":\n";

    for (const auto & directory : group.directories) {
        stream << "\t" << directory << "\n";
    }

    return stream;
}

void DirectoryGroupScan::scan(const std::vector<std::filesystem::path> & fileGroup) {
    HashXxh3 hash;
    std::vector<std::filesystem::path> directories;

    for (auto & path : fileGroup) {
        directories.push_back(path.parent_path());
    }

    std::sort(std::begin(directories), std::end(directories));
    
    for (auto & path : directories) {
        hash.update(path.string().data());
    }

    int64_t digest = hash.digest();

    auto & group = _directoryGroups[digest];
    if (group.directories.empty()) {
        group.directories = directories;
    } 
    std::cout << "group " << fileGroup.front().filename().string() << " digest = " << digest << std::endl;
    
    group.names.push_back(fileGroup.front().filename().string());
}

std::vector<DirectoryGroup> DirectoryGroupScan::groups() const {
    std::vector<DirectoryGroup> result;
    
    for (auto & group : _directoryGroups) {
        result.emplace_back(std::move(group.second));
        std::sort(std::begin(result.back().names), std::end(result.back().names));
    }

    std::sort(std::begin(result), std::end(result), [](auto & l, auto & r) {
        auto & left = l.names.front();
        auto & right = r.names.front();
        
        if (left.size() ==  right.size()) {
            return left < right;
        }

        return left.size() < right.size();
    });

    return result;
}

}