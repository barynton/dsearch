#pragma once

#include <stdexcept>
#include <filesystem>
#include <fstream>

#include "core/file_api/FileApi.h"

namespace core {

class FileStream : public FileApi {
public:
    void open(const std::filesystem::path & filePath) override {
        _stream = std::ifstream(filePath.c_str(), std::ios::binary); 

        if (!_stream.good()) {
            throw std::runtime_error("can't open " + filePath.string());
        }
    }

    std::vector<int8_t> read(int64_t size) override {
        std::vector<int8_t> buffer(size);
        _stream.read(reinterpret_cast<char*>(buffer.data()), size);
        buffer.resize(_stream.gcount());

        if (!_stream.good() && !eof()) {
            throw std::runtime_error("error while reading");
        }
        
        return buffer;
    }

    bool eof() const override {
        return _stream.eof();
    }

    std::ifstream _stream;
};

}
