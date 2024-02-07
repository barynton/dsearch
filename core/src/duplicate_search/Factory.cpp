#include "core/duplicate_search/Factory.h"

#include <functional>
#include <unordered_map>

#include "core/file_api/FileStream.h"

#include "core/duplicate_search/HashSearch.h"
#include "core/duplicate_search/HeadSearch.h"
#include "core/duplicate_search/NameSearch.h"
#include "core/duplicate_search/SizeSearch.h"

namespace {
    typedef std::function<std::unique_ptr<core::DuplicateSearch>()> AlgorithmLambda;
    constexpr auto kBlockSize = 4096;
    
    std::unordered_map<std::string, AlgorithmLambda> algorithmsByName = {
        {"name", [] { return std::make_unique<core::NameSearch>(); }},
        {"size", [] { return std::make_unique<core::SizeSearch>(); }},
        {"head", [] { return std::make_unique<core::HeadSearch>(kBlockSize, std::make_unique<core::FileStream>()); }},
        {"hash", [] { return std::make_unique<core::HashSearch>(kBlockSize*8, std::make_unique<core::FileStream>()); }}
    };
}

namespace core {
    std::unique_ptr<DuplicateSearch> createDuplicateSearch(const std::string & algorithm) {
        auto it = algorithmsByName.find(algorithm);
        if (it != algorithmsByName.end()) {
            return it->second();
        }

        return {};
    }
}
