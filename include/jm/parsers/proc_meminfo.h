#pragma once

#include <jm/paths.h>
#include <jm/types.h>

#include <istream>

namespace jm::proc {

auto meminfo(std::istream&) -> Json;
auto meminfo(const Path& = kMemInfo) -> Json;

} // namespace jm::proc
