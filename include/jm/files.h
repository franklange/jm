#pragma once

#include <jm/types.h>

namespace jm::proc {

constexpr auto kRoot{"/proc"};
constexpr auto kMemInfo{"/proc/meminfo"};
constexpr auto kVmStat{"/proc/vmstat"};

} // namespace jm

namespace jm::cgroup {

constexpr auto kRoot{"/sys/fs/cgroup"};
constexpr auto kProcs{"cgroup.procs"};
constexpr auto kMemoryPressure{"memory.pressure"};

} // namespace jm::cgroup

namespace jm::oom {

constexpr auto kOomScore{"oom_score"};
constexpr auto kExecutable{"exe"};

} // namespace jm::oom
