#pragma once

#include <jm/types.h>

#include <istream>
#include <vector>
#include <string>

namespace jm {

auto split(const std::string&) -> std::vector<std::string>;
auto replace(const std::string&, char o, char n) -> std::string;
auto remove_colon(const std::string&) -> std::string;

auto read_lines(const Path&) -> std::vector<std::string>;
auto read_lines(std::istream&) -> std::vector<std::string>;

auto parse_kv(const std::string&) -> Json;

} // namespace jm
