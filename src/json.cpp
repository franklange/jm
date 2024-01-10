#include <jm/json.h>

#include <iostream>

namespace jm {

void pprint(const Json& j)
{
    std::cout << j.dump(2) << std::endl;
}

auto to_string(const Json& j, const int indent) -> std::string
{
    return j.dump(indent);
}

} // namespace jm
