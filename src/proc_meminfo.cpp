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
    const auto lines = util::read_lines(stream);

    if (lines.empty())
        throw std::runtime_error{"[ERR] meminfo empty"};

    for (auto entry : lines | transform(util::rm_colon) | transform(util::parse_kv))
        res.merge_patch(std::move(entry));

    return res;
}

} // namespace jm::proc
