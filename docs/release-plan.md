# 46 天逐步发布计划

代码提前准备，按以下顺序每天发布一个实际提交。日期代表发布时间。

| 天 | 提交内容 |
|---|---|
| 1 | chore: initialize WebServe with license and reproduction plan |
| 2 | build: add incremental C++14 Makefile |
| 3 | feat(config): define server and database options |
| 4 | feat(config): parse CLI flags and environment settings |
| 5 | feat(buffer): define consumable byte buffer |
| 6 | feat(buffer): preserve unread bytes during compaction |
| 7 | feat(pool): define bounded worker queue interface |
| 8 | feat(pool): implement draining worker lifecycle |
| 9 | feat(log): define asynchronous logger queue |
| 10 | feat(log): flush log batches and track queue overflow |
| 11 | feat(timer): define generation-aware idle deadlines |
| 12 | feat(timer): expire connections and compact stale deadlines |
| 13 | feat(epoll): define descriptor polling wrapper |
| 14 | feat(epoll): implement event registration and EINTR handling |
| 15 | feat(http): define request parsing and form interfaces |
| 16 | feat(http): parse fragmented requests and reject ambiguous framing |
| 17 | feat(http): define mapped response ownership |
| 18 | feat(http): serve files with openat mmap and MIME headers |
| 19 | feat(auth): implement salted PBKDF2 password storage |
| 20 | feat(db): define pooled database authentication interface |
| 21 | feat(db): use prepared statements and scoped connection return |
| 22 | feat(server): define reactor-owned connection state |
| 23 | feat(server): integrate epoll workers completions and timeouts |
| 24 | feat(cli): add server entry point and signal shutdown |
| 25 | feat(web): add original home page and shared stylesheet |
| 26 | feat(web): add registration and login forms |
| 27 | feat(web): add error and empty resource fixtures |
| 28 | feat(db): add unique-user database schema |
| 29 | test: add lightweight unit test registry |
| 30 | test(buffer): cover compaction and consumption bounds |
| 31 | test(http): cover framing limits pipelining and form decoding |
| 32 | test(timer): cover renewals cancellation and heap compaction |
| 33 | test(pool): cover task failures shutdown and backpressure |
| 34 | test(auth): cover random salts and password verification |
| 35 | test(files): cover mappings empty files and forbidden symlinks |
| 36 | test(config): cover invalid numeric arguments and ranges |
| 37 | test(server): add real-socket LT and ET integration scenarios |
| 38 | test(db): cover registration races injection and pool reuse |
| 39 | build: add CMake targets and CTest entry point |
| 40 | build(container): add Docker and database compose deployment |
| 41 | ci: add build unit socket and database checks |
| 42 | perf: add reproducible HTTP benchmark script |
| 43 | docs: explain reactor ownership and module boundaries |
| 44 | docs: document startup database and deployment operations |
| 45 | feat(release): add transactional scheduled publication and tests |
| 46 | docs: complete project usage and publication guide |
