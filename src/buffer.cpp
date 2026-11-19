#include "webserve/buffer.h"
#include <stdexcept>
namespace webserve {
void Buffer::append(const char* data, size_t size) {
    if (offset_ && offset_ >= data_.size() / 2) {
        data_.erase(0, offset_); offset_ = 0;
    }
    data_.append(data, size);
}
void Buffer::consume(size_t size) {
    if (size > this->size()) throw std::out_of_range("buffer consume");
    offset_ += size;
    if (offset_ == data_.size()) clear();
}
}
