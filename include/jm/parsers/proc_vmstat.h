#pragma once

#include <jm/types.h>

#include <istream>

namespace jm::proc {

auto vmstat(const Path&) -> Json;
auto vmstat(std::istream&) -> Json;

} // namespace jm::proc
