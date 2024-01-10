#pragma once

#include <jm/types.h>

namespace jm::oom {

auto hitlist() -> Json;
auto hitlist(const std::string& cgroup) -> Json;

} // namespace jm::oom
