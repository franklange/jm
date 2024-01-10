#pragma once

#include <string_view>

namespace jm::proc {

constexpr auto kMemInfo{"/proc/meminfo"};
constexpr auto kVmStat{"/proc/vmstat"};

} // namespace jm

namespace jm::cgroup {

constexpr auto kMemoryPressure{"memory.pressure"};

} // namespace jm::cgroup
