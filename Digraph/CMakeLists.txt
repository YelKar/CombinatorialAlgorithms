add_executable(Digraph main.cpp Digraph.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    ConnectionComponentTesting
        ConnectionComponentTesting.cpp
        Digraph.cpp
)
target_link_libraries(ConnectionComponentTesting gtest_main)

add_executable(
    CondensationTesting
        CondensationTesting.cpp
        Digraph.cpp
)
target_link_libraries(CondensationTesting gtest_main)

include_directories(../tools)