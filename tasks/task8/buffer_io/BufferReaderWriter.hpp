#pragma once

#include "../ReaderWriter.hpp"



class BufferReaderWriter: public ReaderWriter {

    ReaderWriter* reader_writer_;
    std::vector<char> buffer_;
    size_t pos_, end_;

    template <typename T>
    bool read_(T& src, const char* format);


public:
    BufferReaderWriter(ReaderWriter* rw, size_t buffer_size) :
                        reader_writer_(rw), 
                        buffer_(buffer_size), 
                        pos_(0), end_(0) { }

    ~BufferReaderWriter() { delete reader_writer_; }

    bool is_open() const override;
    bool eof() const override;
    void close() override;

    bool read(int& buf) override;
    bool read(char& buf) override;
    bool read(std::string& str) override;

    bool write(int& buf) override;
    bool write(char& buf) override;
    bool write(std::string& str) override;

};
