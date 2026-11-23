#include "webserve/logger.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <stdexcept>
namespace webserve {
Logger::Logger(const std::string& path): output_(path, std::ios::app) {
    if (!output_) throw std::runtime_error("cannot open log: " + path);
    worker_ = std::thread(&Logger::run, this);
}
Logger::~Logger() {
    { std::lock_guard<std::mutex> lock(mutex_); stopping_ = true; }
    ready_.notify_one(); worker_.join();
}
void Logger::write(const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (messages_.size() >= 4096) { ++dropped_; return; }
    messages_.push_back(message); ready_.notify_one();
}
void Logger::run() {
    for (;;) {
        std::deque<std::string> batch;
        size_t dropped;
        {
            std::unique_lock<std::mutex> lock(mutex_);
            ready_.wait(lock, [this] { return stopping_ || !messages_.empty(); });
            if (messages_.empty() && stopping_) break;
            batch.swap(messages_); dropped = dropped_; dropped_ = 0;
        }
        auto now = std::time(nullptr); std::tm stamp{}; localtime_r(&now, &stamp);
        for (const auto& line: batch)
            output_ << std::put_time(&stamp, "%Y-%m-%d %H:%M:%S") << " " << line << '\n';
        if (dropped) output_ << "log queue dropped " << dropped << " messages\n";
        output_.flush();
    }
}
}
