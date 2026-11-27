#include "webserve/epoller.h"
#include <cerrno>
#include <system_error>
#include <unistd.h>
namespace webserve {
Epoller::Epoller(): fd_(epoll_create1(EPOLL_CLOEXEC)), events_(256) {
    if (fd_ < 0) throw std::system_error(errno, std::generic_category(), "epoll_create1");
}
Epoller::~Epoller() { close(fd_); }
void Epoller::control(int operation, int fd, uint32_t events, uint64_t token) {
    epoll_event event{}; event.events = events; event.data.u64 = token;
    if (epoll_ctl(fd_, operation, fd, &event) < 0)
        throw std::system_error(errno, std::generic_category(), "epoll_ctl");
}
void Epoller::add(int fd, uint32_t events, uint64_t token) { control(EPOLL_CTL_ADD, fd, events, token); }
void Epoller::modify(int fd, uint32_t events, uint64_t token) { control(EPOLL_CTL_MOD, fd, events, token); }
void Epoller::remove(int fd) { epoll_ctl(fd_, EPOLL_CTL_DEL, fd, nullptr); }
int Epoller::wait(int timeout) {
    int result = epoll_wait(fd_, events_.data(), events_.size(), timeout);
    if (result < 0 && errno != EINTR) throw std::system_error(errno, std::generic_category(), "epoll_wait");
    return result < 0 ? 0 : result;
}
}
