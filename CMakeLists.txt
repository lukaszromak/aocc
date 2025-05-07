cmake_minimum_required(VERSION 3.10)
project(AOCC C)

# Include utils directory
include_directories(utils)

# Include all day* directories
file(GLOB DAY_SOURCES day*/day*.c)

# Utils source
set(UTILS_SOURCE utils/utils.c)

# Main file
set(MAIN_SOURCE aoc.c)

# Define the executable
add_executable(aocc ${MAIN_SOURCE} ${DAY_SOURCES} ${UTILS_SOURCE})