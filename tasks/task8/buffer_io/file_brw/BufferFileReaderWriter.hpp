#pragma once

#include "../BufferReaderWriter.hpp"

class BufferFileReaderWriter: virtual public BufferReaderWriter {
    FILE* file_;
    size_t pos_ = 0;

    bool upload_to_src() override;
    bool upload_from_src() override;

public:
    BufferFileReaderWriter(std::string src_name, size_t buffer_size) :
                        BufferReaderWriter(buffer_size)
                        { file_ = std::fopen(src_name.c_str(), "w+");
                          if (!file_) throw "Could not open file!";
                        }

    ~BufferFileReaderWriter() { close(); }

    bool is_open() const override;
    bool eof() const override;
    void close() override;

    bool read(int& src) override;
    bool read(char& src) override;
    bool read(std::string& src) override;

    bool write(int& src) override;
    bool write(char& src) override;
    bool write(std::string& src) override;

};