#include <jm/parsers/proc_meminfo.h>
#include <jm/utils.h>
#include <jm/files.h>

#include <fstream>
#include <ranges>
#include <stdexcept>
#include <string>

namespace jm::proc {

auto meminfo(const Path& path) -> Json
{
    std::ifstream file{path};

    if (!file.is_open())
        throw std::runtime_error{"[ERR] meminfo open"};

    return meminfo(file);
}

auto meminfo(std::istream& stream) -> Json
{
    using namespace std::views;

    Json res;
    auto lines = read_lines(stream);

    for (auto entry : lines | transform(rm_colon) | transform(parse_kv))
        res.merge_patch(std::move(entry));

    return res;
}

} // namespace jm::proc
