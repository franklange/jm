#include <jm/json.h>

namespace jm {

auto to_string(const Json& j, const int indent) -> std::string
{
    return j.dump(indent);
}

} // namespace jm
