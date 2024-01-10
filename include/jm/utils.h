#pragma once

#include <jm/types.h>

#include <istream>
#include <vector>
#include <string>

namespace jm {

auto split(const std::string&) -> std::vector<std::string>;
auto replace(const std::string&, char o, char n) -> std::string;
auto rm_colon(const std::string&) -> std::string;
auto rm_equal(const std::string&) -> std::string;

auto read_lines(const Path&) -> std::vector<std::string>;
auto read_lines(std::istream&) -> std::vector<std::string>;

auto parse_v(const std::string&) -> Json;
auto parse_kv(const std::string&) -> Json;

auto dir_name(const DirEntry&) -> std::string;
auto is_num(const std::string&) -> bool;

} // namespace jm
