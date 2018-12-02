cmake_minimum_required(VERSION 3.5)
set(MODULE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/.cmake/Modules")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${MODULE_DIR})
include(msvc)
include(gcc)

set(CMAKE_CXX_STANDARD 17)
project(aoc2018 LANGUAGES CXX)

macro(set_output_dir dir)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${dir}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${dir}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir}/bin)
endmacro(set_output_dir)

set_output_dir("${CMAKE_BINARY_DIR}/dist")

msvc_remove_warning_level()
msvc_set_flags_if("/utf-8 /W4 /std:c++17")
gcc_set_flags_if("-Wall -Wextra")

###########################
# SRC
##########################
add_subdirectory("day_1/")
add_subdirectory("day_2/")
