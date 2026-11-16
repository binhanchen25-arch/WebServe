#pragma once
#include <string>
namespace webserve {
struct Config {
    std::string bind = "127.0.0.1", root = "resources", log = "webserve.log";
    int port = 1316, threads = 4, timeout_ms = 60000, max_connections = 10000;
    bool edge = true, database = false;
    std::string db_host = "localhost", db_user, db_password, db_name = "webserve";
    int db_port = 3306, db_pool = 4;
    static Config load(int argc, char** argv);
    void validate() const;
};
}
