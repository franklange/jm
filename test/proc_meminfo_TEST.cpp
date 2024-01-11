#include <jm/parsers/proc_meminfo.h>
#include <jm/json.h>

#include <gtest/gtest.h>

#include <string>
#include <sstream>
#include <stdexcept>

namespace jm::test {

TEST(MemInfoTest, success)
{
    std::stringstream stream;
    stream << "MemTotal:       28511624 kB\n";
    stream << "HugePages_Total:       0\n";
    stream << "Hugepagesize:       2048 kB\n";

    const Json expected{
        {"MemTotal", 28511624},
        {"HugePages_Total", 0},
        {"Hugepagesize", 2048},
    };

    EXPECT_EQ(expected, jm::proc::meminfo(stream));
}

TEST(MemInfoTest, empty)
{
    std::stringstream stream;
    EXPECT_THROW(jm::proc::meminfo(stream), std::runtime_error);
}

TEST(MemInfoTest, wrong_format)
{
    std::stringstream stream;
    stream << "MemTotal:       foo kB\n";
    stream << "HugePages_Total:       _\n";

    EXPECT_THROW(jm::proc::meminfo(stream), std::runtime_error);
}

} // namespace Template::test
