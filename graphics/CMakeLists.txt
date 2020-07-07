find_package(OpenGL)
if(OpenGL_FOUND)
    find_package(GLUT)
    if(NOT GLUT_FOUND)
        message("FreeGLUT library will be downloaded and built.")
        include(ExternalProject)
        # Include GLFW
        ExternalProject_Add (
            FREEGLUT
            URL https://sourceforge.net/projects/freeglut/files/freeglut/3.2.1/freeglut-3.2.1.tar.gz
            URL_MD5 cd5c670c1086358598a6d4a9d166949d
            CMAKE_ARGS  -DCMAKE_BUILD_TYPE=RelWithDebInfo
                        -DFREEGLUT_BUILD_SHARED_LIBS=ON
                        -DFREEGLUT_BUILD_STATIC_LIBS=ON
                        -DFREEGLUT_BUILD_DEMOS=OFF
            PREFIX ${CMAKE_CURRENT_BINARY_DIR}/freeglut
            BUILD_IN_SOURCE ON
            INSTALL_COMMAND ""
        )
        ExternalProject_Get_Property(FREEGLUT SOURCE_DIR)
        set(FREEGLUT_DIR ${SOURCE_DIR})
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

    # set_target_properties(${testname} PROPERTIES LINKER_LANGUAGE CXX)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${testname} PRIVATE OpenMP::OpenMP_CXX)
    endif()
    
    if(OpenGL_FOUND)
        if(NOT GLUT_FOUND)
            add_dependencies(${testname} FREEGLUT)
            target_include_directories(${testname} PRIVATE ${FREEGLUT_DIR}/include)
            target_link_directories(${testname} PRIVATE ${FREEGLUT_DIR}/lib)
            target_link_libraries(${testname} PRIVATE freeglut OpenGL::GL)
        else()
            target_include_directories(${testname} PRIVATE ${GLUT_INCLUDE_DIRS})
            target_link_libraries(${testname} PRIVATE OpenGL::GL ${GLUT_LIBRARIES})
        endif()
    else(OpenGL_FOUND)
        target_compile_options(${testname} NO_OPENGL)
    endif(OpenGL_FOUND)
    
    if(APPLE)
        target_compile_options(${testname} PRIVATE -Wno-deprecated)
    endif(APPLE)
    
    install(TARGETS ${testname} DESTINATION "bin/graphics")

endforeach( testsourcefile ${APP_SOURCES} )
