cmake_minimum_required(VERSION 3.15)
project(thealgorithms)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

file(GLOB_RECURSE files "*.cpp")
foreach(file ${files})
    string(FIND ${file} "build" pos)
    if(NOT ${pos} EQUAL -1)
        continue()
    endif()

    string(REGEX REPLACE ".*/(.*)/([A-Za-z0-9 _\-]+)\.cpp" "\\1_\\2" tname ${file})
    string(REPLACE " " "_" tname ${tname})
    message(${tname} "  " ${file})    
    add_executable(${tname} ${file})
endforeach(file)
