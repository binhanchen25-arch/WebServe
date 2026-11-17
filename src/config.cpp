#include "webserve/config.h"
#include <cstdlib>
#include <stdexcept>
namespace webserve {
namespace {
std::string env(const char* key, const std::string& fallback) {
    const char* value = std::getenv(key); return value ? value : fallback;
}
int number(const std::string& value) {
    size_t used = 0; int result = std::stoi(value, &used);
    if (used != value.size()) throw std::invalid_argument("invalid number: " + value);
    return result;
}
}
Config Config::load(int argc, char** argv) {
    Config c;
    c.db_host = env("WEBSERVE_DB_HOST", c.db_host);
    c.db_user = env("WEBSERVE_DB_USER", "");
    c.db_password = env("WEBSERVE_DB_PASSWORD", "");
    c.db_name = env("WEBSERVE_DB_NAME", c.db_name);
    c.db_port = number(env("WEBSERVE_DB_PORT", "3306"));
    for (int i = 1; i < argc; ++i) {
        std::string key = argv[i];
        if (key == "--database") { c.database = true; continue; }
        if (key == "--lt") { c.edge = false; continue; }
        if (++i == argc) throw std::invalid_argument("missing value for " + key);
        std::string value = argv[i];
        if (key == "--bind") c.bind = value;
        else if (key == "--port") c.port = number(value);
        else if (key == "--threads") c.threads = number(value);
        else if (key == "--timeout-ms") c.timeout_ms = number(value);
        else if (key == "--max-connections") c.max_connections = number(value);
        else if (key == "--root") c.root = value;
        else if (key == "--log") c.log = value;
        else if (key == "--db-pool") c.db_pool = number(value);
        else throw std::invalid_argument("unknown option: " + key);
    }
    c.validate(); return c;
}
void Config::validate() const {
    if (port < 1 || port > 65535 || threads < 1 || threads > 128 ||
        timeout_ms < 10 || max_connections < 1 || max_connections > 100000 ||
        db_pool < 1 || db_pool > 128 || db_port < 1 || db_port > 65535 || root.empty())
        throw std::invalid_argument("configuration outside supported range");
    if (database && (db_user.empty() || db_name.empty()))
        throw std::invalid_argument("database user and database name are required");
}
}
