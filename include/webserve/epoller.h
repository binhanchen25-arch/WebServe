#pragma once
#include <cstdint>
#include <sys/epoll.h>
#include <vector>
namespace webserve {
class Epoller {
    int fd_;
    std::vector<epoll_event> events_;
    void control(int operation, int fd, uint32_t events, uint64_t token);
public:
    Epoller();
    ~Epoller();
    Epoller(const Epoller&) = delete;
    Epoller& operator=(const Epoller&) = delete;
    void add(int fd, uint32_t events, uint64_t token);
    void modify(int fd, uint32_t events, uint64_t token);
    void remove(int fd);
    int wait(int timeout);
    const epoll_event& event(int index) const { return events_.at(index); }
};
}
