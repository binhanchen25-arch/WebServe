#include "webserve/thread_pool.h"
#include <stdexcept>
namespace webserve {
ThreadPool::ThreadPool(size_t count, size_t capacity): capacity_(capacity) {
    if (!count || !capacity) throw std::invalid_argument("invalid pool size");
    try {
        for (size_t i = 0; i < count; ++i) workers_.emplace_back([this] {
            for (;;) {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(mutex_);
                    ready_.wait(lock, [this] { return stopping_ || !tasks_.empty(); });
                    if (tasks_.empty() && stopping_) return;
                    task = std::move(tasks_.front()); tasks_.pop();
                }
                try { task(); } catch (...) { /* One failed task must not kill the pool. */ }
            }
        });
    } catch (...) { stop(); throw; }
}
ThreadPool::~ThreadPool() { stop(); }
bool ThreadPool::submit(std::function<void()> task) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (stopping_ || tasks_.size() >= capacity_) return false;
    tasks_.push(std::move(task)); ready_.notify_one(); return true;
}
void ThreadPool::stop() {
    { std::lock_guard<std::mutex> lock(mutex_); stopping_ = true; }
    ready_.notify_all();
    for (auto& worker: workers_) if (worker.joinable()) worker.join();
}
}
