#include <jm/utils.h>

#include <cstdio>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <sstream>
#include <utility>

namespace jm {

auto read_lines(const Path& path) -> std::vector<std::string>
{
    std::ifstream file{path, std::ios::in};

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

auto split(const std::string& words) -> std::vector<std::string>
{
    std::istringstream s{words};

    return {std::istream_iterator<std::string>{s},
            std::istream_iterator<std::string>()};
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

auto parse_kv(const std::string& s) -> Json
{
    char key[256] = {};
    std::uint64_t value{0};
    std::sscanf(s.c_str(), "%255s %u", key, &value);

    return {{key, value}};
}

auto dir_name(const DirEntry& e) -> std::string
{
    return e.path().filename().string();
}

} // namespace jm
