#include "core/DriectoryScan.h"

#include "core/file_api/FileStream.h"

#include "core/duplicate_search/HashSearch.h"
#include "core/duplicate_search/HeadSearch.h"
#include "core/duplicate_search/NameSearch.h"
#include "core/duplicate_search/SizeSearch.h"

#include "core/DirectoryGroupScan.h"


namespace {
    constexpr auto kBlockSize = 4096;
}

namespace core {

DirectoryScan::DirectoryScan(std::ostream & logStream)
: _logStream(logStream)
{
    _searchAlgorithms.push_back(std::make_unique<NameSearch>());
    _searchAlgorithms.push_back(std::make_unique<SizeSearch>());
    _searchAlgorithms.push_back(std::make_unique<HeadSearch>(kBlockSize, std::make_unique<FileStream>()));
    _searchAlgorithms.push_back(std::make_unique<HashSearch>(kBlockSize*8, std::make_unique<FileStream>()));
}

std::vector<DirectoryGroup> DirectoryScan::scan(const std::filesystem::path & deirectoryPath) {
    auto duplicates = initialScan(deirectoryPath);
    
    for (auto i = 1; i < _searchAlgorithms.size(); ++i) {
        duplicates = groupScan(i, duplicates);
    }

    DirectoryGroupScan directoryGroupScan;
    for (const auto & group : duplicates) {
        directoryGroupScan.scan(group);
    }

    return directoryGroupScan.groups();
}

DuplicateSearch::Groups DirectoryScan::initialScan(const std::filesystem::path & deirectoryPath) {
    for (auto entry : std::filesystem::recursive_directory_iterator(deirectoryPath)) {
        try {
            if (!entry.is_regular_file()) {
                continue;
            }

            _searchAlgorithms.front()->process(entry.path());
        } catch (std::exception & exception) {
            _logStream << "initial scan: " << exception.what() << "\n";
        }
    }

    return _searchAlgorithms.front()->duplicates();
}

DuplicateSearch::Groups DirectoryScan::groupScan(int32_t algorithmIndex, const DuplicateSearch::Groups & groups) {
    DuplicateSearch::Groups newDuplicates;
    auto & search = _searchAlgorithms[algorithmIndex];
    for (const auto & group : groups) {
        for (const auto & duplicate : group) {
            try {
                _logStream << "algorithm " << algorithmIndex << " scan :" << duplicate << "\n";
                search->process(duplicate);
            } catch (std::exception & exception) {
                _logStream << "algorithm " << algorithmIndex << ":" << exception.what() << "\n";
            }
        }
        auto groupDuplicates = search->duplicates();
        newDuplicates.insert(std::end(newDuplicates), std::begin(groupDuplicates), std::end(groupDuplicates));
        search->reset();
    }

    return newDuplicates;
}

}
