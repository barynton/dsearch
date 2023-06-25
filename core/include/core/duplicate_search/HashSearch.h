#pragma once

#include <fstream>
#include <string>

#include "core/HashXxh3.h"
#include "core/file_api/FileApi.h"
#include "core/duplicate_search/IndexedSearch.h"

namespace core
{

class HashSearch : public IndexedSearch<int64_t> {
public:
    HashSearch(uint64_t blockSize, uint64_t ignoreSize, std::unique_ptr<FileApi> && fileApi)
    : _blockSize(blockSize)
    , _ignoreSize(ignoreSize)
    , _fileApi(std::move(fileApi))
    {
    }

    void process(const std::filesystem::path & filePath) override {
        if (std::filesystem::file_size(filePath) <= _ignoreSize) {
            _ignored.push_back(filePath);
            return;
        }

        HashXxh3 hash;

        _fileApi->open(filePath);

        while (!_fileApi->eof()) {
            auto buffer = _fileApi->read(_blockSize);
            hash.update(buffer);
        }

        this->add(hash.digest(), filePath);
    }

    Groups duplicates() const override {
        auto duplicates = IndexedSearch<int64_t>::duplicates();
        duplicates.push_back(_ignored);
        return duplicates;
    }

    void reset() override {
        IndexedSearch<int64_t>::reset();
        _ignored.clear();
    }

protected:
    uint64_t _blockSize = 0;
    uint64_t _ignoreSize = 0;
    std::unique_ptr<FileApi> _fileApi;
    std::vector<std::filesystem::path> _ignored;
};

}
