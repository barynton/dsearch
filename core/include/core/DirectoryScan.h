#pragma once 

#include <memory>
#include <ostream>
#include <vector>

#include "core/DirectoryGroupScan.h"
#include "core/duplicate_search/DuplicateSearch.h"

namespace core {

class DirectoryScan {
public:
    DirectoryScan(std::ostream & logStream);

    DuplicateSearch::Groups scan(const std::filesystem::path & deirectoryPath);

private:
    DuplicateSearch::Groups initialScan(const std::filesystem::path & deirectoryPath);
    DuplicateSearch::Groups groupScan(int32_t algorithmIndex, const DuplicateSearch::Groups & groups);

    std::vector<std::unique_ptr<DuplicateSearch>> _searchAlgorithms;
    std::ostream & _logStream;
};

}
