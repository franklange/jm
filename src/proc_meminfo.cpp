#include <jm/parsers/proc_meminfo.h>
#include <jm/types.h>
#include <jm/utils.h>

#include <cstdio>
#include <fstream>
#include <ranges>
#include <stdexcept>
#include <string>
#include <tuple>

namespace jm::proc {

static auto parse(const std::string& s) -> Json
{
    char key[256] = {};
    std::uint64_t value{0};

    std::sscanf(s.c_str(), "%255s %u", key, &value);
    return {{key, value}};
}

static auto trim(const std::string& s) -> std::string
{
    return remove_colon(s);
}

auto meminfo(std::istream& stream) -> Json
{
    using namespace std::views;

    Json res;
    const auto lines = read_lines(stream);

    for (auto entry : lines | transform(trim) | transform(parse))
        res.merge_patch(std::move(entry));

    return res;
}

auto meminfo(const Path& path) -> Json
{
    std::ifstream file{path};

    if (!file.is_open())
        throw std::runtime_error{"[ERR] meminfo open"};

    return meminfo(file);
}

} // namespace jm::proc
