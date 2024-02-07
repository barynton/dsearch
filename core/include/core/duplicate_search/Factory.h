#pragma once

#include <memory>

#include "core/duplicate_search/DuplicateSearch.h"

namespace core {
    std::unique_ptr<DuplicateSearch> createDuplicateSearch(const std::string & algorithm);
}
