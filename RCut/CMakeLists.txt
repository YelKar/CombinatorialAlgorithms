add_executable(RCut main.cpp RCut.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    RCutTesting
        RCutTesting.cpp
        RCut.cpp
)
target_link_libraries(RCutTesting gtest_main)

include_directories(../tools)