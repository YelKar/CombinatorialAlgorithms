add_executable(
    TravelingSalesmanProblem
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
    TravelingSalesmanProblemTesting
        Testing.cpp
)
target_link_libraries(TravelingSalesmanProblemTesting gtest_main)

include_directories(../../../tools ../1)