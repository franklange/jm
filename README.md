# jm
C++20 library to parse Linux proc and cgroup data as JSON.

### Dependencies
* nlohmann::json
* Linux `/proc` and `/sys/fs/cgroup` mounted

### Proc Example
`jm::proc` contains a collection of parsers for specific `/proc` files  
(see `include/jm/parsers/proc_*`).
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

### Cgroups Example
`jm::cgroup` contains a collection of parsers for specific cgroup files under `/sys/fs/cgroup`  
(see `include/jm/parsers/cgroup_*`).
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
  "user.slice": {
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
  "/": {
    "full": {
      "avg10": 0.0,
      "avg300": 0.0,
      "avg60": 0.0,
      "total": 0
    },
...
*/

```

### OOM Hitlist Example

The `jm::oom::hitlist()` collects a descending list of pids based on ` /proc/<pid>/oom_score`,  
either system-wide (no arg) or per cgroup if specified.

```c++
#include <jm/oom.h>

auto main() -> int
{
    const auto l = jm::oom::hitlist();
    jm::pprint(l);

    return 0;
}
/* prints:
[
  {
    "pid": 1172,
    "score": 880
  },

    "pid": 945,
    "score": 870
  },
  {
    "pid": 1101,
    "score": 869
  },
  ...
*/

```
