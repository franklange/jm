#include <jm/utils.h>

#include <algorithm>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <sstream>
#include <utility>

namespace jm::util {

auto read_lines(const Path& path) -> std::vector<std::string>
{
    std::ifstream file{path};

    if (!file.is_open())
        throw std::runtime_error{"[ERR] file open " + path.string()};

    return read_lines(file);
}

auto read_lines(std::istream& stream) -> std::vector<std::string>
{
    std::string line;
    std::vector<std::string> res;

    while (std::getline(stream, line))
        res.push_back(std::move(line));

    return res;
}

auto replace(const std::string& s, const char o, const char n) -> std::string
{
    std::string res{s};
    std::replace(res.begin(), res.end(), o, n);

    return res;
}

auto rm_colon(const std::string& s) -> std::string
{
    return replace(s, ':', ' ');
}

auto rm_equal(const std::string& s) -> std::string
{
    return replace(s, '=', ' ');
}

auto parse_v(const std::string& s) -> Json
{
    return std::stoull(s);
}

auto parse_kv(const std::string& s) -> Json
{
    char key[256] = {};
    std::uint64_t value{0};
    const auto ret = std::sscanf(s.c_str(), "%255s %u", key, &value);
    if (ret != 2)
        throw std::runtime_error{"[ERR] parse k/v"};

    return {{key, value}};
}

auto dir_name(const DirEntry& e) -> std::string
{
    return e.path().filename().string();
}

auto is_num(const std::string& s) -> bool
{
    return std::all_of(s.begin(), s.end(), isdigit);
}

} // namespace jm::util
