add_executable(
    PermutationsWithRepetition
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
    PermutationsWithRepetitionTesting
        Testing.cpp
)
target_link_libraries(PermutationsWithRepetitionTesting gtest_main)

include_directories(
        ../../../tools
)