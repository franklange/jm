project(jm_test)

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(${PROJECT_NAME} "")

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "tests"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/"
)
target_sources(${PROJECT_NAME} PRIVATE
    proc_meminfo_TEST.cpp
    proc_vmstat_TEST.cpp

    cgroup_memory_pressure_TEST.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME} PRIVATE
    jm
    GTest::Main
)

gtest_discover_tests(${PROJECT_NAME})

