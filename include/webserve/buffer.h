#pragma once
#include <string>
namespace webserve {
class Buffer {
    std::string data_;
    size_t offset_ = 0;
public:
    size_t size() const { return data_.size() - offset_; }
    const char* data() const { return data_.data() + offset_; }
    std::string str() const { return data_.substr(offset_); }
    void append(const char* data, size_t size);
    void append(const std::string& value) { append(value.data(), value.size()); }
    void consume(size_t size);
    void clear() { data_.clear(); offset_ = 0; }
};
}
