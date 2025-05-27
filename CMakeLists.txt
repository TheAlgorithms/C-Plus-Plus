cmake_minimum_required(VERSION 3.22)
project(TheAlgorithms/C++
    LANGUAGES CXX
    VERSION 1.0.0
    DESCRIPTION "Set of algorithms implemented in C++."
)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Additional warnings and errors
if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wno-register -Werror=vla)
endif()

option(USE_OPENMP "flag to use OpenMP for multithreading" ON)
if(USE_OPENMP)
    find_package(OpenMP 3.0 COMPONENTS CXX)
    if (OpenMP_CXX_FOUND)
        message(STATUS "Building with OpenMP Multithreading.")
    else()
        message(STATUS "No OpenMP found, no multithreading.")
    endif()
endif()
    
add_subdirectory(backtracking)
add_subdirectory(bit_manipulation)
add_subdirectory(ciphers)
add_subdirectory(cpu_scheduling_algorithms)
add_subdirectory(data_structures)
add_subdirectory(divide_and_conquer)
add_subdirectory(dynamic_programming)
add_subdirectory(games)
add_subdirectory(geometry)
add_subdirectory(graph)
add_subdirectory(graphics)
add_subdirectory(greedy_algorithms)
add_subdirectory(hashing)
add_subdirectory(machine_learning)
add_subdirectory(math)
add_subdirectory(numerical_methods)
add_subdirectory(operations_on_datastructures)
add_subdirectory(others)
add_subdirectory(physics)
add_subdirectory(probability)
add_subdirectory(range_queries)
add_subdirectory(search)
add_subdirectory(sorting)
add_subdirectory(strings)

cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0057 NEW)

find_package(Doxygen OPTIONAL_COMPONENTS dot dia)
if(DOXYGEN_FOUND)  
    if(MSVC)
        set(DOXYGEN_CPP_CLI_SUPPORT YES)
    endif()

    if(Doxygen_dot_FOUND)
        set(DOXYGEN_HAVE_DOT YES)
    endif()
    
    if(OPENMP_FOUND)
        set(DOXYGEN_PREDEFINED "_OPENMP=1")
    endif()
    
    if(GLUT_FOUND)
        set(DOXYGEN_PREDEFINED ${DOXYGEN_PREDEFINED} "GLUT_FOUND=1")
    endif()

    doxygen_add_docs(
        doc
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Generate documentation"
        CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile
    )
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
