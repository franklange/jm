#include <jm/parsers/proc_vmstat.h>

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <stdexcept>

namespace jm::test {

TEST(VmStatTest, success)
{
    std::stringstream stream;
    stream << "oom_kill 0\n";
    stream << "numa_pte_updates 0\n";
    stream << "numa_huge_pte_updates 207\n";

    const Json expected{
        {"oom_kill", 0},
        {"numa_pte_updates", 0},
        {"numa_huge_pte_updates", 207},
    };

    EXPECT_EQ(expected, jm::proc::vmstat(stream));
}

TEST(VmStatTest, empty)
{
    std::stringstream stream;
    EXPECT_THROW(jm::proc::vmstat(stream), std::runtime_error);
}

TEST(VmStatTest, wrong_format)
{
    std::stringstream stream;
    stream << "oom_kill foo\n";
    stream << "_ 99\n";

    EXPECT_THROW(jm::proc::vmstat(stream), std::runtime_error);
}

} // namespace jm::test
