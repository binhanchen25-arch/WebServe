#pragma once
#include "webserve/buffer.h"
#include <map>
#include <string>
namespace webserve {
enum class ParseResult { incomplete, complete, invalid, too_large };
struct Request {
    std::string method, path, version, body;
    std::map<std::string, std::string> headers;
    bool keep_alive = false;
    static ParseResult parse(Buffer& buffer, Request& request);
    static bool decode(const std::string& input, std::string& output, bool form = false);
    bool form(std::map<std::string, std::string>& fields) const;
};
}
