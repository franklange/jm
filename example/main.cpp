#include <jm/parsers/proc_meminfo.h>
#include <jm/types.h>
#include <jm/paths.h>

#include <iostream>
#include <string>

using namespace jm;

auto main() -> int
{
    const auto j = proc::meminfo(proc::kMemInfo);
    std::cout << to_string(j) << std::endl;

    return 0;
}
