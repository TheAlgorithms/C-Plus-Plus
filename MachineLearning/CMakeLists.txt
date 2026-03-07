cmake_minimum_required(VERSION 3.16)
project(MachineLearning CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Eigen3 QUIET)
if(Eigen3_FOUND)
  set(EIGEN_TARGET Eigen3::Eigen)
else()
  message(WARNING "Eigen3 package config not found, using /usr/include/eigen3 fallback include path")
  include_directories(/usr/include/eigen3)
endif()
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE ML_CORE_CPP
    "${CMAKE_CURRENT_SOURCE_DIR}/supervised/*/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/unsupervised/*/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/reinforcement/*/*.cpp")
list(FILTER ML_CORE_CPP EXCLUDE REGEX ".*/demo\\.cpp$")

add_library(ml_core ${ML_CORE_CPP})
if(Eigen3_FOUND)
  target_link_libraries(ml_core PUBLIC ${EIGEN_TARGET})
endif()

file(GLOB_RECURSE ML_DEMOS
    "${CMAKE_CURRENT_SOURCE_DIR}/supervised/*/demo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/unsupervised/*/demo.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/reinforcement/*/demo.cpp")

foreach(demo ${ML_DEMOS})
    get_filename_component(demo_dir ${demo} DIRECTORY)
    get_filename_component(demo_name ${demo_dir} NAME)
    get_filename_component(parent_dir ${demo_dir} DIRECTORY)
    get_filename_component(parent_name ${parent_dir} NAME)
    set(target "${parent_name}_${demo_name}_demo")
    add_executable(${target} ${demo})
    target_link_libraries(${target} PRIVATE ml_core)
    if(Eigen3_FOUND)
      target_link_libraries(${target} PRIVATE ${EIGEN_TARGET})
    endif()
endforeach()
