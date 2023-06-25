#pragma once

#include <fstream>
#include <string>

#include <xxhash.h>

#include "core/file_api/FileApi.h"
#include "core/duplicate_search/IndexedSearch.h"

namespace core
{

class HeadSearch : public IndexedSearch<int64_t> {
public:
    HeadSearch(uint64_t headSize, std::unique_ptr<FileApi> && fileApi)
    : _headSize(headSize)
    , _fileApi(std::move(fileApi))
    {
    }

    void process(const std::filesystem::path & filePath) override {
        _fileApi->open(filePath);
        auto buffer = _fileApi->read(_headSize);

        auto hash = XXH3_64bits(reinterpret_cast<void*>(buffer.data()), buffer.size());
        this->add(hash, filePath);
    }

protected:
    uint64_t _headSize = 0;
    std::unique_ptr<FileApi> _fileApi;
};

}
