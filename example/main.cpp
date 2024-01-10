#include <jm/parsers/cgroup_memory_pressure.h>

auto main() -> int
{
    const auto json = jm::cgroup::memory_pressure_all();
    jm::pprint(json);

    return 0;
}
