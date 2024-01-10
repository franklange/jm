#pragma once

namespace jm::proc {

constexpr auto kMemInfo{"/proc/meminfo"};
constexpr auto kVmStat{"/proc/vmstat"};

} // namespace jm

namespace jm::cgroup {

constexpr auto kRoot{"/sys/fs/cgroup/"};
constexpr auto kMemoryPressure{"memory.pressure"};

} // namespace jm::cgroup
