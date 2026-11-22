#pragma once
#include <condition_variable>
#include <deque>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>
namespace webserve {
class Logger {
    std::ofstream output_;
    std::mutex mutex_;
    std::condition_variable ready_;
    std::deque<std::string> messages_;
    bool stopping_ = false;
    size_t dropped_ = 0;
    std::thread worker_;
    void run();
public:
    explicit Logger(const std::string& path);
    ~Logger();
    void write(const std::string& message);
};
}
