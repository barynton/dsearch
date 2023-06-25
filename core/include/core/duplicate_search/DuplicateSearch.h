#pragma once

#include <filesystem>
#include <vector>

namespace core {

class DuplicateSearch {
public:
    typedef std::vector<std::vector<std::filesystem::path>> Groups;

    virtual ~DuplicateSearch() = default;
    virtual Groups duplicates() const = 0;
    virtual void process(const std::filesystem::path & filePath) = 0;
    virtual void reset() = 0;
};

}
