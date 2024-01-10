#pragma once

#include <jm/types.h>

namespace jm::oom {

auto hitlist_global() -> Json;
auto hitlist_cgroup(const std::string&) -> Json;

} // namespace jm::oom
