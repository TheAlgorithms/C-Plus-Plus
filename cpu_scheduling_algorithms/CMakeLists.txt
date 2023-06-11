# If necessary, use the RELATIVE flag, otherwise each source file may be listed
# with full pathname. The RELATIVE flag makes it easier to extract an executable's name
# automatically.

file( GLOB APP_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp )
foreach( testsourcefile ${APP_SOURCES} )
    string( REPLACE ".cpp" "" testname ${testsourcefile} ) # File type. Example: `.cpp`
    add_executable( ${testname} ${testsourcefile} )

    set_target_properties(${testname} PROPERTIES LINKER_LANGUAGE CXX)
    if(OpenMP_CXX_FOUND)
        target_link_libraries(${testname} OpenMP::OpenMP_CXX)
    endif()
    install(TARGETS ${testname} DESTINATION "bin/cpu_scheduling_algorithms") # Folder name. Do NOT include `<>`

endforeach( testsourcefile ${APP_SOURCES} )
