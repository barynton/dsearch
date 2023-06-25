#pragma once

#include <string>

#include "core/duplicate_search/IndexedSearch.h"

namespace core
{

class SizeSearch : public IndexedSearch<int64_t> {
public:
    void process(const std::filesystem::path & filePath) override {
        this->add(std::filesystem::file_size(filePath), filePath);
    }
};

}
