# Fetch Unity test framework
include(FetchContent)
FetchContent_Declare(
  unity
  GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
  GIT_TAG        v2.5.2
)
FetchContent_Populate(unity)

# Create the test executable
# We compile unity.c directly with our tests (standard Unity practice)
add_executable(unit_tests 
    test_dummy.c
    ${unity_SOURCE_DIR}/src/unity.c
    # Future C modules will be added here, e.g.:
    # ../Core/Src/pid_controller.c
)

# Include Unity headers
target_include_directories(unit_tests PRIVATE
    ${unity_SOURCE_DIR}/src
)

# Register tests with CTest
include(CTest)
add_test(NAME AllTests COMMAND unit_tests)