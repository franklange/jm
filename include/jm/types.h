#pragma once

#include <jm/json.h>

#include <filesystem>

namespace jm {

using Path = std::filesystem::path;
using DirIter = std::filesystem::directory_iterator;
using DirEntry = std::filesystem::directory_entry;

} // namespace jm
