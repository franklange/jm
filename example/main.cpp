#include <jm/jm.h>

auto main() -> int
{
    const auto l = jm::proc::meminfo();
    jm::pprint(l);

    return 0;
}
