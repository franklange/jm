# jm
C++20 library to parse Linux proc and cgroup data as JSON.

### Dependencies
* nlohmann::json
* Linux `/proc` and `/sys/fs/cgroup` readable

### Proc Example
`jm::proc` contains a collection of parsers for specific `/proc` files  
(see `include/jm/parsers/proc_*`).
```c++
#include <jm/jm.h>

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
#include <jm/jm.h>

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

`jm::oom::hitlist_*` collects a sorted list of pids based on ` /proc/<pid>/oom_score`,  
either system-wide or per cgroup if specified. Higher score means the process is more likely  
to be killed by the kernel in an OOM scenario.

```c++
#include <jm/jm.h>

auto main() -> int
{
    const auto l = jm::oom::hitlist_cgroup("user.slice");
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

### Build
```bash
cd jm
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DJM_TESTS=ON -DJM_EXAMPLES=ON ..
cmake --build . -j

# run tests
ctest -n # or ./bin/tests

# run example
./bin/example
```
