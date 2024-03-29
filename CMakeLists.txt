cmake_minimum_required(VERSION 3.10)
project(jm)

find_package(nlohmann_json REQUIRED)

option(JM_TESTS "Enable Tests" OFF)
option(JM_EXAMPLES "Enable Examples" OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build Type" FORCE)
endif()

add_library(${PROJECT_NAME} "")

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_sources(${PROJECT_NAME} PRIVATE
    include/jm/files.h
    include/jm/jm.h
    include/jm/json.h
    include/jm/oom.h
    include/jm/parsers/cgroup_memory_pressure.h
    include/jm/parsers/proc_meminfo.h
    include/jm/parsers/proc_vmstat.h
    include/jm/types.h
    include/jm/utils.h

    src/cgroup_memory_pressure.cpp
    src/json.cpp
    src/oom.cpp
    src/proc_meminfo.cpp
    src/proc_vmstat.cpp
    src/utils.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME} PUBLIC
    nlohmann_json::nlohmann_json
)

if (JM_TESTS)
    enable_testing()

    if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
        add_compile_options(-Wall -Wextra -pedantic)
    endif ()

    add_subdirectory(test)
endif()

if (JM_EXAMPLES)
    add_subdirectory(example)
endif()
