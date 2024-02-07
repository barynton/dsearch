#include "core/facade/FileGroupsScan.h"

#include <algorithm>

#include "core/duplicate_search/Factory.h"

namespace core {

FileGroupsScan::FileGroupsScan(std::ostream & logStream, const std::vector<std::string> & algorithms)
: _logStream(logStream)
{
    for (auto & algorithm : algorithms) {
        auto duplicateSearch = createDuplicateSearch(algorithm);
        if (duplicateSearch) {
            _searchAlgorithms.push_back(std::move(duplicateSearch));
        } else {
            logStream << "error: algorithm not found - " << algorithm;
        }
    }
}

DuplicateSearch::Groups FileGroupsScan::scan(const std::filesystem::path & deirectoryPath) {
    auto duplicates = initialScan(deirectoryPath);
    
    for (auto i = 1; i < _searchAlgorithms.size(); ++i) {
        duplicates = groupScan(i, duplicates);
    }

    for (auto & group : duplicates) {
        std::sort(std::begin(group), std::end(group));
    }

    std::sort(std::begin(duplicates), std::end(duplicates), [] (auto & l, auto & r) {
        return l.front() < r.front();
    });

    return duplicates;
}

DuplicateSearch::Groups FileGroupsScan::initialScan(const std::filesystem::path & deirectoryPath) {
    auto & algorithm = _searchAlgorithms.front();
    for (auto entry : std::filesystem::recursive_directory_iterator(deirectoryPath)) {
        try {
            if (!entry.is_regular_file()) {
                continue;
            }

            algorithm->process(entry.path());
        } catch (std::exception & exception) {
            _logStream << "error: initial scan - " << exception.what() << "\n";
        }
    }

    return algorithm->duplicates();
}

DuplicateSearch::Groups FileGroupsScan::groupScan(int32_t algorithmIndex, const DuplicateSearch::Groups & groups) {
    DuplicateSearch::Groups newDuplicates;
    auto & search = _searchAlgorithms[algorithmIndex];
    for (const auto & group : groups) {
        for (const auto & duplicate : group) {
            try {
                search->process(duplicate);
            } catch (std::exception & exception) {
                _logStream << "error: algorithm " << algorithmIndex << ":" << exception.what() << "\n";
            }
        }
        auto groupDuplicates = search->duplicates();
        newDuplicates.insert(std::end(newDuplicates), std::begin(groupDuplicates), std::end(groupDuplicates));
        search->reset();
    }

    return newDuplicates;
}

}
