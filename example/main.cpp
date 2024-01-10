#include <jm/oom.h>

auto main() -> int
{
    const auto l = jm::oom::hitlist();
    jm::pprint(l);

    return 0;
}
