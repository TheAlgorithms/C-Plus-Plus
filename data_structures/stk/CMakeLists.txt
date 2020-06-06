add_executable( stack 
    stack.cpp 
    main.cpp 
)
add_executable( test_stack 
    stack.cpp 
    test_stack.cpp 
)
install(TARGETS stack DESTINATION "bin/data_structures")
install(TARGETS test_stack DESTINATION "bin/data_structures")
install(FILES students.txt DESTINATION "bin/data_structures")
