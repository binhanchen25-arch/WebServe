#include "webserve/timer.h"
namespace webserve {
void Timer::touch(uint64_t id, int milliseconds) {
    Entry entry{Clock::now() + std::chrono::milliseconds(milliseconds), id, ++generation_};
    live_[id] = entry; heap_.push(entry);
    // Compact stale deadlines: frequent traffic must not grow memory indefinitely.
    if (heap_.size() > live_.size() * 4 + 128) {
        decltype(heap_) replacement;
        for (const auto& pair: live_) replacement.push(pair.second);
        heap_.swap(replacement);
    }
}
std::vector<uint64_t> Timer::expired() {
    std::vector<uint64_t> result; auto now = Clock::now();
    while (!heap_.empty() && heap_.top().deadline <= now) {
        auto entry = heap_.top(); heap_.pop();
        auto found = live_.find(entry.id);
        if (found != live_.end() && found->second.generation == entry.generation) {
            live_.erase(found); result.push_back(entry.id);
        }
    }
    return result;
}
}
