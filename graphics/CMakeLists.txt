find_package(OpenGL)
if(OpenGL_FOUND)
    find_package(GLUT)
    if(NOT GLUT_FOUND)
        message("FreeGLUT library will be downloaded and built.")
        include(ExternalProject)
        ExternalProject_Add (
            FREEGLUT-PRJ
            URL https://github.com/FreeGLUTProject/freeglut/releases/download/v3.2.2/freeglut-3.2.2.tar.gz
            URL_MD5 485c1976165315fc42c0b0a1802816d9
            CMAKE_GENERATOR ${CMAKE_GENERATOR}
            CMAKE_GENERATOR_TOOLSET ${CMAKE_GENERATOR_TOOLSET}
            CMAKE_GENERATOR_PLATFORM ${CMAKE_GENERATOR_PLATFORM}
            CMAKE_ARGS  -DCMAKE_BUILD_TYPE=Release
                        -DFREEGLUT_BUILD_SHARED_LIBS=OFF
                        -DFREEGLUT_BUILD_STATIC_LIBS=ON
                        -DFREEGLUT_BUILD_DEMOS=OFF
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}/freeglut
            # BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/freeglut-build
            # BUILD_IN_SOURCE ON
            # UPDATE_COMMAND ""
            INSTALL_COMMAND ""
            # CONFIGURE_COMMAND ""
            # BUILD_COMMAND ""
        )
        ExternalProject_Get_Property(FREEGLUT-PRJ SOURCE_DIR)
        ExternalProject_Get_Property(FREEGLUT-PRJ BINARY_DIR)
        set(FREEGLUT_BIN_DIR ${BINARY_DIR})
        set(FREEGLUT_SRC_DIR ${SOURCE_DIR})
        # add_library(libfreeglut STATIC IMPORTED)
        # set_target_properties(libfreeglut PROPERTIES IMPORTED_LOCATION ${FREEGLUT_BIN_DIR})

        # set(FREEGLUT_BUILD_DEMOS OFF CACHE BOOL "")
        # set(FREEGLUT_BUILD_SHARED_LIBS OFF CACHE BOOL "")
        # set(FREEGLUT_BUILD_STATIC_LIBS ON CACHE BOOL "")
        # add_subdirectory(${FREEGLUT_SRC_DIR} ${FREEGLUT_BIN_DIR} EXCLUDE_FROM_ALL)
        # add_subdirectory(${BINARY_DIR})
        # find_package(FreeGLUT)
    endif(NOT GLUT_FOUND)
else(OpenGL_FOUND)
    message(WARNING "OPENGL not found. Will not build graphical outputs.")
endif(OpenGL_FOUND)

# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
file( GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp )
# file( GLOB APP_SOURCES ${CMAKE_SOURCE_DIR}/*.c )
# AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} APP_SOURCES)
foreach( testsourcefile ${APP_SOURCES} )
    # I used a simple string replace, to cut off .cpp.
    string( REPLACE ".cpp" "" testname ${testsourcefile} )
    add_executable( ${testname} ${testsourcefile} )

    set_target_properties(${testname} PROPERTIES LINKER_LANGUAGE CXX)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${testname} PRIVATE OpenMP::OpenMP_CXX)
    endif()
    
    if(OpenGL_FOUND)
        if(NOT GLUT_FOUND)
            add_dependencies(${testname} FREEGLUT-PRJ)
            target_compile_definitions(${testname} PRIVATE FREEGLUT_STATIC)
            target_include_directories(${testname} PRIVATE ${FREEGLUT_SRC_DIR}/include)
            target_link_directories(${testname} PRIVATE ${FREEGLUT_BIN_DIR}/lib)
            target_link_libraries(${testname} PRIVATE OpenGL::GL)
            target_link_libraries(${testname} INTERFACE FREEGLUT-PRJ)
            # target_include_directories(${testname} PRIVATE ${FREEGLUT_INCLUDE_DIRS})
            # target_link_libraries(${testname} INTERFACE freeglut_static)
        else()
            target_include_directories(${testname} PRIVATE ${GLUT_INCLUDE_DIRS})
            target_link_libraries(${testname} PRIVATE OpenGL::GL ${GLUT_LIBRARIES})
        endif()
        target_compile_definitions(${testname} PRIVATE USE_GLUT)
    endif(OpenGL_FOUND)
    
    if(APPLE)
        target_compile_options(${testname} PRIVATE -Wno-deprecated)
    endif(APPLE)
    
    install(TARGETS ${testname} DESTINATION "bin/graphics")

endforeach( testsourcefile ${APP_SOURCES} )
