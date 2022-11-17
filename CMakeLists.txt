cmake_minimum_required(VERSION 3.23)
project(IniFile)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(test)

set(SOURCE_FILES main.cpp IniFileManager.cpp IniFileManager.h)
add_executable(IniFile main.cpp)
add_library(core ${SOURCE_FILES})
target_link_libraries(IniFile core)
