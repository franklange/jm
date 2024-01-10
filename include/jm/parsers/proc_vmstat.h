#pragma once

#include <jm/files.h>
#include <jm/types.h>

#include <istream>

namespace jm::proc {

auto vmstat(std::istream&) -> Json;
auto vmstat(const Path& = kVmStat) -> Json;

} // namespace jm::proc
