#include <jm/parsers/cgroup_memory_pressure.h>

#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <stdexcept>

namespace jm::test {

TEST(MemoryPressureTest, success)
{
    std::stringstream stream;
    stream << "some avg10=0.50 avg60=1.00 avg300=0.50 total=2\n";
    stream << "full avg10=0.10 avg60=0.99 avg300=0.01 total=0\n";

    const Json expected{
        {"some", {
            {"avg10", 0.5},
            {"avg60", 1.0},
            {"avg300", 0.5},
            {"total", 2},
        }},
        {"full", {
            {"avg10", 0.1},
            {"avg60", 0.99},
            {"avg300", 0.01},
            {"total", 0},
        }},
    };

    EXPECT_EQ(expected, jm::cgroup::memory_pressure(stream));
}

TEST(MemoryPressureTest, empty)
{
    std::stringstream stream;
    EXPECT_THROW(jm::cgroup::memory_pressure(stream), std::runtime_error);
}

TEST(MemoryPressureTest, wrong_format)
{
    std::stringstream stream;
    stream << "some foo avg10_0.50 avg60_1.00 avg300_0.50 total=0\n";

    EXPECT_THROW(jm::cgroup::memory_pressure(stream), std::runtime_error);
}

TEST(MemoryPressureTest, entry_missing)
{
    std::stringstream stream;
    stream << "some avg10=0.50 avg60=1.00 avg300=0.50\n";

    EXPECT_THROW(jm::cgroup::memory_pressure(stream), std::runtime_error);
}

} // namespace jm::test
