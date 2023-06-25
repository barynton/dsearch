#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

namespace core {

class FileApi {
public:
    virtual ~FileApi() = default;

    virtual void open(const std::filesystem::path & filePath) = 0;
    virtual std::vector<int8_t> read(int64_t size) = 0;
    virtual bool eof() const = 0;
};

}
