cmake_minimum_required(VERSION 3.3)
project(Algorithms_in_C++
    LANGUAGES CXX
    VERSION 1.0.0
    DESCRIPTION "Set of algorithms implemented in C++."
)

# set(CMAKE_CXX_CPPLINT "~/anaconda3/bin/cpplint --filter=-legal/copyright --std=c++11")
# find_program(CLANG_FORMAT "clang-format")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    # set(CMAKE_CXX_STANDARD 14)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif(MSVC)

option(USE_OPENMP "flag to use OpenMP for multithreading" ON)

cmake_policy(SET CMP0054 NEW)
cmake_policy(SET CMP0057 NEW)
find_package(Doxygen OPTIONAL_COMPONENTS dot dia)
if(DOXYGEN_FOUND)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_USE_MATHJAX YES)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_EXTRACT_STATIC YES)
    set(DOXYGEN_INLINE_SOURCES YES)
    set(DOXYGEN_CREATE_SUBDIRS YES)
    set(DOXYGEN_EXTRACT_PRIVATE YES)
    set(DOCYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_STRIP_CODE_COMMENTS NO)
    set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
    set(DOXYGEN_FILE_PATTERNS *.cpp *.h *.hpp *.md)
    set(DOXYGEN_TAGFILES "doc/cppreference-doxygen-web.tag.xml=http://en.cppreference.com/w/")
    if(MSVC)
        set(DOXYGEN_CPP_CLI_SUPPORT YES)
    endif()
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

add_subdirectory(math)
add_subdirectory(others)
add_subdirectory(search)
add_subdirectory(strings)
add_subdirectory(sorting)
add_subdirectory(computer_oriented_statistical_methods)

if(USE_OPENMP)
    find_package(OpenMP)
    if (OpenMP_CXX_FOUND)
        message(STATUS "Building with OpenMP Multithreading.")
    else()
        message(STATUS "No OpenMP found, no multithreading.")
    endif()
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
