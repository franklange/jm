cmake_minimum_required(VERSION 3.10)
project(proc_json)

find_package(nlohmann_json REQUIRED)

option(PROC_JSON_TESTS "Enable Tests" OFF)
option(PROC_JSON_EXAMPLES "Enable Examples" OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build Type" FORCE)
endif()

add_library(${PROJECT_NAME} "")

set_target_properties(${PROJECT_NAME} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

target_sources(${PROJECT_NAME} PRIVATE
    include/proc_json/utils.h

    src/utils.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

target_link_libraries(${PROJECT_NAME} PUBLIC
    nlohmann_json::nlohmann_json
)

if (PROC_JSON_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

if (PROC_JSON_EXAMPLES)
    add_subdirectory(example)
endif()
