# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. RELATIVE may makes it easier to extract an executable name
# automatically.
find_package(OpenGL)
if(NOT OpenGL_FOUND)
    message(WARNING "OpenGL not found, not compiling graphics programs.")

else(NOT OpenGL_FOUND)
    find_package(GLUT)
    if(NOT GLUT_FOUND)
        message(WARNING "GLUT not found, not compiling graphics programs.")
    endif(NOT GLUT_FOUND)
endif(NOT OpenGL_FOUND)

file( GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp )
# file( GLOB APP_SOURCES ${CMAKE_SOURCE_DIR}/*.c )
# AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} APP_SOURCES)
foreach( testsourcefile ${APP_SOURCES} )
    # I used a simple string replace, to cut off .cpp.
    string( REPLACE ".cpp" "" testname ${testsourcefile} )
    add_executable( ${testname} ${testsourcefile} )

    set_target_properties(${testname} PROPERTIES LINKER_LANGUAGE CXX)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${testname} OpenMP::OpenMP_CXX)
    endif()
    if (GLUT_FOUND)
        if(APPLE)
            target_compile_options(${testname} PUBLIC -Wno-deprecated)
        endif(APPLE)
        target_compile_definitions(${testname} PUBLIC USE_GLUT)
        target_include_directories(${testname} PUBLIC ${GLUT_INCLUDE_DIRS})
        target_link_libraries(${testname} OpenGL::GL ${GLUT_LIBRARIES})
    endif(GLUT_FOUND)
    install(TARGETS ${testname} DESTINATION "bin/graphics")

endforeach( testsourcefile ${APP_SOURCES} )
