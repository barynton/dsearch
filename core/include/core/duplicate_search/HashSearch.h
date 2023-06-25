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
    HashSearch(uint64_t blockSize, std::unique_ptr<FileApi> && fileApi)
    : _blockSize(blockSize)
    , _fileApi(std::move(fileApi))
    {
    }

    void process(const std::filesystem::path & filePath) override {
        HashXxh3 hash;

        _fileApi->open(filePath);

        while (!_fileApi->eof()) {
            auto buffer = _fileApi->read(_blockSize);
            hash.update(buffer);
        }

        this->add(hash.digest(), filePath);
    }

protected:
    uint64_t _blockSize = 0;
    std::unique_ptr<FileApi> _fileApi;
};

}
