#pragma once

#include "../BufferReaderWriter.hpp"

class BufferStringReaderWriter: virtual public BufferReaderWriter {
    std::string& str_;
    size_t pos_ = 0;

    bool upload_to_src() override;
    bool upload_from_src() override;

public:
    BufferStringReaderWriter(std::string& src, size_t buffer_size) :
                        BufferReaderWriter(buffer_size),
                        str_(src) { }

    ~BufferStringReaderWriter() { close(); }

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