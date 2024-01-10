#pragma once

#include <jm/types.h>

#include <istream>

namespace jm::proc {

auto meminfo() -> Json;
auto meminfo(const Path&) -> Json;
auto meminfo(std::istream&) -> Json;

} // namespace jm::proc
