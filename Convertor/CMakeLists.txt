# CMakeList.txt : CMake project for Convertor, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Convertor "main.c"  "parser.h"  "strings.h"  "str.h" "slice.h" "constants.h" "graph.h" "postfix.h" "variable.h" "variables.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Convertor PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
