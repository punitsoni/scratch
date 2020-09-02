# Based on tutorial at 
# https://cmake.org/cmake/help/v3.18/guide/tutorial/index.html

cmake_minimum_required(VERSION 3.18)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(
  prj
  VERSION 1.0
  LANGUAGES CXX
)
configure_file(prj_config.h.in prj_config.h)

# Add the library directory so it will be compiled.
add_subdirectory(samplelib)

add_executable(prj prj_main.cc)

target_include_directories(
  prj PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}"
)

# Link library to executable.
target_link_libraries(prj PUBLIC samplelib)

