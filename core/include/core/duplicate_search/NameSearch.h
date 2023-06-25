#pragma once

#include <string>

#include "core/duplicate_search/IndexedSearch.h"

namespace core
{

class NameSearch : public IndexedSearch<std::string> {
public:
    void process(const std::filesystem::path & filePath) override {
        this->add(filePath.filename().string(), filePath);
    }
};

}
