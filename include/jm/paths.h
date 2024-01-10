#pragma once

#include <string_view>

namespace jm::proc {

constexpr auto kMemInfo{"/proc/meminfo"};

} // namespace jm

namespace jm::cgroup {

constexpr auto kMemoryPressure{"memory.pressure"};

} // namespace jm::cgroup
