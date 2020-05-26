cmake_minimum_required(VERSION 3.3)
project(Algorithms_in_C
    LANGUAGES C CXX
    VERSION 1.0.0
    DESCRIPTION "Set of algorithms implemented in C."
)

option(USE_OPENMP "flag to use OpenMP for multithreading" ON)

cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0057 NEW)
find_package(Doxygen OPTIONAL_COMPONENTS dot dia)
if(DOXYGEN_FOUND)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_USE_MATHJAX YES)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_INLINE_SOURCES YES)
    set(DOXYGEN_CREATE_SUBDIRS YES)
    set(DOCYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_STRIP_CODE_COMMENTS NO)
    set(DOXYGEN_OPTIMIZE_OUTPUT_FOR_C YES)
    set(DOXYGEN_MATHJAX_RELPATH "https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.7/MathJax.js?config=TeX-MML-AM_CHTML")
    if(Doxygen_dot_FOUND)
        set(DOXYGEN_HAVE_DOT YES)
        set(DOXYGEN_CALL_GRAPH YES)
        set(DOXYGEN_INTERACTIVE_SVG YES)
        set(DOXYGEN_DOT_IMAGE_FORMAT "svg")
    endif()

    doxygen_add_docs(
        doc
        ${PROJECT_SOURCE_DIR}
        COMMENT "Generate documentation"
    )
endif()

function(function_timer)
    set(CMAKE_BUILD_TYPE "Release")         # This is local to function
    add_subdirectory(function_timer EXCLUDE_FROM_ALL)
endfunction()

function_timer()

include_directories(function_timer/include)
# link_libraries(function_timer)
# include_directories(${CMAKE_BINARY_DIR}/include)
# link_directories(${CMAKE_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE})

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
    add_compile_options(/Za)
endif(MSVC)

add_subdirectory(conversions)
add_subdirectory(misc)
add_subdirectory(project_euler)
add_subdirectory(sorting)
add_subdirectory(searching)
add_subdirectory(numerical_methods)

if(USE_OPENMP)
    find_package(OpenMP)
    if (OpenMP_C_FOUND)
        message(STATUS "Building with OpenMP Multithreading.")
    else()
        message(STATUS "No OpenMP found, no multithreading.")
    endif()
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
