cmake_minimum_required(VERSION 3.10)
project(StonePaperScissors CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(stone_paper_scissors
    main.cpp
)

install(TARGETS stone_paper_scissors DESTINATION bin/games)
