#include "BufferReaderWriter.hpp"
#include <string>

bool BufferReaderWriter::is_open() const { return reader_writer_->is_open(); }
bool BufferReaderWriter::eof() const { return reader_writer_->eof() && pos_ >= end_; }
void BufferReaderWriter::close() { 
    std::string str(buffer_.begin(), buffer_.end());
    if (pos_ > 0) { reader_writer_->write(str); }
    reader_writer_->close();
}

template <typename T>
bool BufferReaderWriter::write_(T& src) {
    std::string str = std::to_string(src);
    if (pos_ + str.size() > buffer_.size()) {
        if (pos_ > 0) {
            std::string str_buf(buffer_.begin(), buffer_.end());
            reader_writer_->write(str_buf);
            reader_writer_->write(str);
        }
        pos_ = 0;
        return true;
    }
    std::memcpy(buffer_.data() + pos_, str.data(), str.size());
    pos_ += str.size();
    return true;
}

template <typename T>
bool BufferReaderWriter::read_(T& src, const char* format) {
    if (pos_ >= end_) {
        pos_ = end_ = 0;
        return reader_writer_->read(src);
    }
    std::string str(buffer_.begin(), buffer_.end());
    return std::sscanf(str.c_str(), format, &src);
} 

bool BufferReaderWriter::read(int& buf) {
    return read_(buf, "%c");
}

bool BufferReaderWriter::read(char& buf) {
    return read_(buf, "%c");
};

bool BufferReaderWriter::read(std::string& str) {
    if (pos_ >= end_) {
        pos_ = end_ = 0;
        if (!reader_writer_->read(str)) {
            return false;
        }
        end_ = buffer_.size();
    }
    str = std::string(buffer_.data() + pos_, end_ - pos_);
    pos_ = end_;
    return true;
}

bool BufferReaderWriter::write(int& buf) {
    write_(buf);
}

bool BufferReaderWriter::write(char& buf) {
    write_(buf);
}

bool BufferReaderWriter::write(std::string& str) {
    write_(str);
}