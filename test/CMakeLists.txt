# CMakeLists.txt for StringExtensions
#
# © 2018-2019 by Richard Walters

cmake_minimum_required(VERSION 3.8)
set(This StringExtensionsTests)

set(Sources
    src/StringExtensionsTests.cpp
)

add_executable(${This} ${Sources})
set_target_properties(${This} PROPERTIES
    FOLDER Tests
)

target_include_directories(${This} PRIVATE ../src)

target_link_libraries(${This} PUBLIC
    gtest_main
    StringExtensions
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
