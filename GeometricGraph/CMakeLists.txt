add_executable(GeometricGraph main.cpp GeometricGraph.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    HamiltonianCycleTesting
        HamiltonianCycleTesting.cpp
        GeometricGraph.cpp
)
target_link_libraries(HamiltonianCycleTesting gtest_main)

include_directories(../tools)