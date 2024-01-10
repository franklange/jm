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
    const auto lines = util::read_lines(path);
    if (lines.size() != 1)
        throw std::runtime_error{"[ERR] oom_score format"};

    return util::parse_v(lines.at(0));
}

static auto read_pids(const std::string& cgroup) -> std::vector<std::string>
{
    Path path = (cgroup == "/")
        ? Path{cgroup::kRoot} / cgroup::kProcs
        : Path{cgroup::kRoot} / cgroup / cgroup::kProcs;

    return util::read_lines(std::move(path));
}

static auto is_dir(const DirEntry& d) -> bool
{
    return d.is_directory();
}

auto hitlist_global() -> Json
{
    Json res = Json::array();
    for (const auto& e : DirIter{proc::kRoot} | std::views::filter(is_dir))
    {
        const auto dirName = util::dir_name(e);

        if (!util::is_num(dirName))
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

auto hitlist_cgroup(const std::string& cgroup) -> Json
{
    Json res = Json::array();
    const auto pids = read_pids(cgroup);

    for (const auto& pid : pids)
    {
        res.push_back({
            {"pid", util::parse_v(pid)},
            {"score", parse_score(Path{proc::kRoot} / pid / kOomScore)}}
        );
    }
    std::sort(res.begin(), res.end(), [](const auto& a, const auto& b){
        return (a.at("score") > b.at("score"));
    });

    return res;
}

} // namespace jm::oom
