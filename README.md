# jm
C++23 library to parse Linux proc and cgroup data as JSON.

### Dependencies
* nlohmann::json
* Linux `/proc` and `/sys/fs/cgroup` mounted

### proc example
```c++
#include <jm/parsers/proc_meminfo.h>

auto main() -> int
{
    const auto json = jm::proc::meminfo();
    jm::pprint(json);

    return 0;
}
/* prints:
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

### cgroups example
```c++
#include <jm/parsers/cgroup_memory_pressure.h>

auto main() -> int
{
    const auto json = jm::cgroup::memory_pressure_all();
    jm::pprint(json);

    return 0;
}
/* prints:
{
  "/": {
    "full": {
      "avg10": 0.0,
      "avg300": 0.0,
      "avg60": 0.0,
      "total": 1
    },
    "some": {
      "avg10": 0.0,
      "avg300": 0.0,
      "avg60": 0.0,
      "total": 1
    }
  },
  "user.slice": {
    "full": {
      "avg10": 0.0,
      "avg300": 0.0,
      "avg60": 0.0,
      "total": 0
    },
...
*/

```
