find_package(GTest QUIET)

if(NOT GTest_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571
  )

  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
  file(GLOB_RECURSE TEST_FILES "*.cpp" "*.c" "*.h" "*.hpp")
endif()


set (TEST_FILES "" CACHE STRING "")
file(GLOB_RECURSE TEST_FILES "*.cpp" "*.c" "*.h" "*.hpp" )


SET(TEST_FLAGS ${SRC_FLAGS})
SET(TEST_LIB ${TEST_LIB} -lm GTest::gtest GTest::gtest_main -lsubunit -pthread -lgcov)
IF(UNIX)
    SET(TEST_FLAGS ${TEST_FLAGS} -fprofile-arcs -ftest-coverage -g)
endif()

enable_testing()
create_target(test FILES ${TEST_FILES} FLAGS ${TEST_FLAGS} LIBS ${TEST_LIB})

include(GoogleTest)

gtest_discover_tests(test)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Found ccache: ${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK "${CCACHE_PROGRAM}")
endif()