cmake_minimum_required(VERSION 3.10)
project(aoc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Shared helpers source and header
set(HELPERS_SRC
    helpers.cpp
)

# Copy input files if they have changed
file(GLOB INPUT_FILES "day*/day*-input.txt.out")

add_custom_target(copy_inputs ALL
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${INPUT_FILES}
            ${CMAKE_BINARY_DIR}
    COMMENT "Copying input files to build directory"
)


# Create a static library target for helper methods
add_library(utils STATIC
  utils/helpers.cpp
)
target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/utils)


# Add executables
add_executable(utilscmdline
  utilsCmdLine.cpp
)
target_link_libraries(utilscmdline PRIVATE utils)


# Function to add a day's executable
function(add_day_exec day_name)
    add_executable(${day_name}
        ${day_name}/${day_name}.cpp
    )
    target_link_libraries(${day_name} PRIVATE utils)
endfunction()

# Add executables for each day
add_day_exec(day1)
add_day_exec(day2)

