#pragma once

#include <algorithm>
#include <unordered_map>

#include "core/duplicate_search/DuplicateSearch.h"

namespace core {

template <class KeyT>
class IndexedSearch : public DuplicateSearch {
public:
    Groups duplicates() const override {
        Groups result;
        std::for_each(std::begin(_duplicatesIndex), std::end(_duplicatesIndex), [&](const auto & pair) {
            // result.emplace_back(std::move(pair.second));
            result.push_back(pair.second);

        });

        return result;
    }

    void reset() override {
        _uniquesIndex.clear();
        _duplicatesIndex.clear();
    }

protected:
    void add(const KeyT & key, const std::filesystem::path & filePath) {
        auto uniqueIt = _uniquesIndex.find(key);
        
        if (std::end(_uniquesIndex) != uniqueIt) {
            //use move?
            _duplicatesIndex[key].push_back(uniqueIt->second);
            _duplicatesIndex[key].push_back(filePath);

            _uniquesIndex.erase(uniqueIt);

            return;
        }

        auto duplicateIt = _duplicatesIndex.find(key); 

        if (std::end(_duplicatesIndex) != duplicateIt) {
            _duplicatesIndex[key].push_back(filePath);
            
            return;
        }

        _uniquesIndex[key] = filePath;
    }

    std::unordered_map<KeyT, std::filesystem::path> _uniquesIndex;
    std::unordered_map<KeyT, std::vector<std::filesystem::path>> _duplicatesIndex;
};

}
