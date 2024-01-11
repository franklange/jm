#pragma once

#include <jm/types.h>

#include <istream>
#include <string>

namespace jm::cgroup {

auto memory_pressure_all() -> Json;
auto memory_pressure_root() -> Json;

auto memory_pressure(std::istream&) -> Json;
auto memory_pressure(const std::string& cgroup) -> Json;

} // namespace jm::cgroup
