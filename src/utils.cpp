#include <jm/utils.h>

#include <algorithm>
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
        throw std::runtime_error{"[ERR] file open"};

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

auto remove_colon(const std::string& s) -> std::string
{
    return replace(s, ':', ' ');
}

} // namespace jm
