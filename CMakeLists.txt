cmake_minimum_required(VERSION 2.6.2)

project(has_basic_sdk C CXX)

# for makefile debug
#set(CMAKE_VERBOSE_MAKEFILE ON)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
add_definitions(-D_LINUX_)

set(GLOG_SOURCE_DIR ${PROJECT_SOURCE_DIR}/dl/glog-0.3.5)
add_subdirectory(${GLOG_SOURCE_DIR})

aux_source_directory(${PROJECT_SOURCE_DIR}/platform/linux PLATFORM_OS)
set(LIBSRC ${PLATFORM_OS})

include_directories(${PROJECT_SOURCE_DIR}/include/has_platform)
include_directories(${PROJECT_SOURCE_DIR}/include/has_platform/linux)

set(LIBS m pthread rt glog stdc++)

add_library(has_platform STATIC ${LIBSRC})
target_link_libraries(has_platform ${LIBS})

# install
set(CMAKE_INSTALL_PREFIX ../release)
install(TARGETS has_platform ARCHIVE DESTINATION lib)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/has_platform DESTINATION include)

# use googletest as test tool
set(GOOGLETEST_SOURCE_DIR ${PROJECT_SOURCE_DIR}/dl/googletest)
add_subdirectory(${GOOGLETEST_SOURCE_DIR})
enable_testing()
include_directories(${GOOGLETEST_SOURCE_DIR}/include)

# unit test
link_directories(${LIBRARY_OUTPUT_DIRECTORY})
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)
aux_source_directory(${TEST_DIR} TEST_SRC)
set(UNITTEST_BIN has_platform_unittest)
add_executable(${UNITTEST_BIN} ${TEST_SRC})
target_link_libraries(${UNITTEST_BIN} gtest_main gtest has_platform)

add_test(NAME ${UNITTEST_BIN} COMMAND ${UNITTEST_BIN})
