#pragma once
#include <chrono>
#include <cstdint>
#include <queue>
#include <unordered_map>
#include <vector>
namespace webserve {
class Timer {
    using Clock = std::chrono::steady_clock;
    struct Entry {
        Clock::time_point deadline;
        uint64_t id, generation;
        bool operator>(const Entry& other) const { return deadline > other.deadline; }
    };
    std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> heap_;
    std::unordered_map<uint64_t, Entry> live_;
    uint64_t generation_ = 0;
public:
    void touch(uint64_t id, int milliseconds);
    void erase(uint64_t id) { live_.erase(id); }
    std::vector<uint64_t> expired();
    size_t size() const { return live_.size(); }
};
}
