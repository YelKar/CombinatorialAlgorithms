add_executable(
    Backpack
        main.cpp
)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
        BackpackTesting
        Testing.cpp
)
target_link_libraries(BackpackTesting gtest_main)

include_directories(
        ../../../tools
)