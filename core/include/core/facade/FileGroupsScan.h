#pragma once 

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "core/duplicate_search/DuplicateSearch.h"

namespace core {

class FileGroupsScan {
public:
    FileGroupsScan(std::ostream & logStream, const std::vector<std::string> & algorithms);

    DuplicateSearch::Groups scan(const std::filesystem::path & deirectoryPath);

private:
    DuplicateSearch::Groups initialScan(const std::filesystem::path & deirectoryPath);
    DuplicateSearch::Groups groupScan(int32_t algorithmIndex, const DuplicateSearch::Groups & groups);

    std::vector<std::unique_ptr<DuplicateSearch>> _searchAlgorithms;
    std::ostream & _logStream;
};

}
