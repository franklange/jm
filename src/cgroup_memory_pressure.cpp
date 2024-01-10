#include <jm/parsers/cgroup_memory_pressure.h>
#include <jm/files.h>
#include <jm/utils.h>

#include <fstream>
#include <ranges>

#include <iostream>

namespace jm::cgroup {

static auto parse(const std::string& s) -> Json
{
    char window[8] = {};
    char avg10[8]  = {};
    char avg60[8]  = {};
    char avg300[8] = {};
    char total[8]  = {};

    double a10 {0.0};
    double a60 {0.0};
    double a300{0.0};
    std::uint64_t tcount{0};

    std::sscanf(s.c_str(), "%8s %8s %lf %8s %lf %8s %lf %8s %u",
        window, avg10, &a10, avg60, &a60, avg300, &a300, total, &tcount);

    return {
        {window, {
            {avg10,  a10},
            {avg60,  a60},
            {avg300, a300},
            {total, tcount},
        }},
    };
}

auto memory_pressure(std::istream& stream) -> Json
{
    using namespace std::views;

    Json res;
    auto lines = read_lines(stream);

    for (auto e : lines | transform(rm_equal) | transform(parse))
        res.merge_patch(std::move(e));

    return res;
}

static auto memory_pressure(const Path& path) -> Json
{
    std::ifstream file{path};

    if (!file.is_open())
        throw std::runtime_error{"[ERR] mem pressure open " + path.string()};

    return memory_pressure(file);
}

auto memory_pressure_root() -> Json
{
    const Path root{cgroup::kRoot};
    return memory_pressure(root / kMemoryPressure);
}

auto memory_pressure(const std::string& cgroup) -> Json
{
    if (cgroup == "/")
        return memory_pressure_root();

    const Path root{cgroup::kRoot};
    return memory_pressure(root / cgroup / kMemoryPressure);
}

auto memory_pressure_all() -> Json
{
    Json res;
    res.merge_patch({{"/", memory_pressure_root()}});

    for (const auto& e : DirIter{cgroup::kRoot})
    {
        if (!e.is_directory())
            continue;

        res.merge_patch({{dir_name(e), memory_pressure(e.path() / kMemoryPressure)}});
    }

    return res;
}

} // namespace jm::cgroup
