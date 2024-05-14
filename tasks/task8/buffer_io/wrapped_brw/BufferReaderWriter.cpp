// #include "BufferReaderWriter.hpp"
// #include <string>

// bool BufferReaderWriter::is_open() const { return reader_writer_->is_open(); }
// bool BufferReaderWriter::eof() const { return reader_writer_->eof() && pos_ >= end_; }
// void BufferReaderWriter::close() { 
//     std::string src(buffer_.begin(), buffer_.end());
//     if (pos_ > 0) { reader_writer_->write(src); }
//     reader_writer_->close();
// }

// template <typename T>
// bool BufferReaderWriter::read_(T& src, const char* format) {
//     if (pos_ >= end_) {
//         pos_ = end_ = 0;
//         return reader_writer_->read(src);
//     }
//     std::string str(buffer_.begin(), buffer_.end());
//     return std::sscanf(str.c_str(), format, &src);
// } 

// bool BufferReaderWriter::read(int& src) {
//     return read_(src, "%c");
// }

// bool BufferReaderWriter::read(char& src) {
//     return read_(src, "%c");
// };

// bool BufferReaderWriter::read(std::string& src) {
//     if (pos_ >= end_) {
//         pos_ = end_ = 0;
//         if (!reader_writer_->read(src)) {
//             return false;
//         }
//         end_ = buffer_.size();
//     }
//     src = std::string(buffer_.data() + pos_, end_ - pos_);
//     pos_ = end_;
//     return true;
// }

// bool BufferReaderWriter::write(int& src) {
//     return write(src);
// }

// bool BufferReaderWriter::write(char& src) {
//     return write(src);
// }

// bool BufferReaderWriter::write(std::string& src) {
//     if (pos_ + src.size() > buffer_.size()) {
//         if (pos_ > 0) {
//             std::string str_buf(buffer_.begin(), buffer_.end());
//             reader_writer_->write(str_buf);
//             reader_writer_->write(src);
//         }
//         pos_ = 0;
//         return true;
//     }
//     std::memcpy(buffer_.data() + pos_, src.data(), src.size());
//     pos_ += src.size();
//     return true;
// }