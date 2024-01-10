#include <jm/parsers/proc_vmstat.h>
#include <jm/utils.h>

#include <fstream>
#include <ranges>
#include <stdexcept>

namespace jm::proc {

auto vmstat(const Path& path) -> Json
{
    std::ifstream file{path};

    if (!file.is_open())
        throw std::runtime_error{"[ERR] vmstat open"};

    return vmstat(file);
}

auto vmstat(std::istream& stream) -> Json
{
    using namespace std::views;

    Json res;
    const auto lines = util::read_lines(stream);

    for (auto entry : lines | transform(util::rm_colon) | transform(util::parse_kv))
        res.merge_patch(std::move(entry));

    return res;
}

} // namespace jm::proc
