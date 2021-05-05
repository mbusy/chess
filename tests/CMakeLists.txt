find_package(GTest)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_SOURCES
    dummy_test.cpp)

# Build the unit tests only if gtest is found
if(${GTEST_FOUND})
    message("-- GTEST found, will be building unit tests")
    add_executable(run_tests test_launcher.cpp ${TEST_SOURCES})
    target_link_libraries(
        run_tests
        sfml-system
        sfml-window
        sfml-graphics
        sfml-audio
        ${GTEST_LIBRARIES}
        ${CMAKE_THREAD_LIBS_INIT})

else()
    message("-- GTEST missing, the unit tests won't be built")
endif()