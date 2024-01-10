#pragma once

#include <nlohmann/json.hpp>

#include <ostream>
#include <string>

namespace jm {

using Json = nlohmann::json;

void pprint(const Json&);
auto to_string(const Json&, int indent = 2) -> std::string;

} // namespace jm
