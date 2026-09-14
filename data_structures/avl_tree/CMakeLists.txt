add_executable( avl_tree 
    avl_tree.hpp
    main_avl_tree.cpp
)
add_executable(test_avl_tree test_avl_tree.cpp)

install(TARGETS avl_tree test_avl_tree DESTINATION "bin/data_structures")
