#include <jm/oom.h>

auto main() -> int
{
    const auto l = jm::oom::hitlist_cgroup("user.slice");
    jm::pprint(l);

    return 0;
}
