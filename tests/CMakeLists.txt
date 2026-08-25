if(POLICY CMP0135)
  cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)
FetchContent_MakeAvailable(googletest)

# Disable clang-tidy on GoogleTest targets
if(CLANG_TIDY_EXE)
    set_target_properties(gtest gtest_main gmock gmock_main PROPERTIES
        C_CLANG_TIDY ""
        CXX_CLANG_TIDY ""
    )
endif()

add_executable(tests
    intersection-test.cpp
    HAL_stubs.c
)

target_compile_definitions(tests PRIVATE NATIVE)

target_include_directories(tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests
)

target_link_libraries(tests PRIVATE
    ${CMAKE_PROJECT_NAME}_lib
    gtest_main
)
