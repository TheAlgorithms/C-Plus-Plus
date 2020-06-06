add_library(libqueue OBJECT queue.h queue.cpp)
add_executable( test_queue 
    test_queue.cpp 
)
target_link_libraries(test_queue PUBLIC libqueue)

install(TARGETS test_queue DESTINATION "bin/data_structures")
