#include <jm/oom.h>
#include <jm/utils.h>
#include <jm/files.h>

#include <algorithm>
#include <iterator>
#include <ranges>
#include <stdexcept>
#include <string>

namespace jm::oom {

static auto parse_score(const Path& path) -> Json
{
    const auto lines = read_lines(path);
    if (lines.size() != 1)
        throw std::runtime_error{"[ERR] oom_score format"};

    return parse_v(lines.at(0));
}

static auto read_pids(const std::string& cgroup) -> std::vector<std::string>
{
    Path path = (cgroup == "/")
        ? Path{cgroup::kRoot} / cgroup::kProcs
        : Path{cgroup::kRoot} / cgroup / cgroup::kProcs;

    return read_lines(std::move(path));
}

static auto is_dir(const DirEntry& d) -> bool
{
    return d.is_directory();
}

auto hitlist() -> Json
{
    Json res;

    for (const auto& e : DirIter{proc::kRoot} | std::views::filter(is_dir))
    {
        const auto dirName = dir_name(e);

        if (!is_num(dirName))
            continue;

        res.push_back({
            {"pid", std::stoull(dirName)},
            {"score", parse_score(e.path() / kOomScore)},
        });
    }

    std::sort(res.begin(), res.end(), [](const auto& a, const auto& b){
        return (a.at("score") > b.at("score"));
    });

    return res;
}

auto hitlist(const std::string& cgroup) -> Json
{
    Json res;
    const auto pids = read_pids(cgroup);

    for (const auto& pid : pids)
    {
        res.push_back({
            {"pid", parse_v(pid)},
            {"score", parse_score(Path{proc::kRoot} / pid / kOomScore)}}
        );
    }

    std::sort(res.begin(), res.end(), [](const auto& a, const auto& b){
        return (a.at("score") > b.at("score"));
    });

    return res;
}

} // namespace jm::oom
