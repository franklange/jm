#pragma once

#include <nlohmann/json.hpp>

#include <ostream>
#include <string>

namespace jm {

using Json = nlohmann::json;

auto to_string(const Json&, int indent = 2) -> std::string;

} // namespace jm
