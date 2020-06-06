add_library(libstack OBJECT stack.h stack.cpp)
add_executable( stack 
    main.cpp 
)
target_link_libraries(stack PUBLIC libstack)
# set_target_properties(stack PROPERTIES LINKER_LANGUAGE CXX)

add_executable( test_stack  
    test_stack.cpp 
)
target_link_libraries(test_stack PUBLIC libstack)

install(TARGETS stack DESTINATION "bin/data_structures")
install(TARGETS test_stack DESTINATION "bin/data_structures")
install(FILES students.txt DESTINATION "bin/data_structures")
