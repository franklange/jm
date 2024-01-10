#pragma once

#include <jm/types.h>

#include <istream>
#include <string>

namespace jm::cgroup {

auto memory_pressure_all() -> Json;
auto memory_pressure_root() -> Json;

auto memory_pressue(std::istream&) -> Json;
auto memory_pressure(const std::string&) -> Json;

} // namespace jm::cgroup
