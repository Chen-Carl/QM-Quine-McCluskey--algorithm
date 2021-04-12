cmake_minimum_required(VERSION 2.8)
project(QM_alg)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -O0 -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function")

include_directories(.)

set(LIB_SRC
    src/util.cpp
    src/logicalExpr.cpp
    src/simplify.cpp
)

add_library(QM_alg ${LIB_SRC})

add_executable(test tests/test.cpp)
add_dependencies(test QM_alg)
target_link_libraries(test QM_alg)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
