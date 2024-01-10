# jm
C++20 library to parse Linux proc and cgroup data as JSON.

### Dependencies
* nlohmann::json
* Linux `/proc` and `/sys/fs/cgroup` mounted

### Example
```c++
#include <jm/parsers/proc_meminfo.h>

auto main() -> int
{
    const auto json = jm::proc::meminfo();
    jm::pprint(json);

    return 0;
}
/* output:
{
  "Active": 2981984,
  "Active(anon)": 1960176,
  "Active(file)": 1021808,
  "AnonHugePages": 403456,
  "AnonPages": 1783632,
  "Bounce": 0,
  "Buffers": 56712,
  "Cached": 1557324,
  ...
*/
```
