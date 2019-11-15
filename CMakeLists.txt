CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)
ADD_SUBDIRECTORY(unit_tests)


add_library(unit_tests unit_test.cpp)

SET(CMAKE_CXX_STANDARD 11)


ADD_EXECUTABLE(unit_test ${unit_tests}/unit_test.cpp)
ADD_EXECUTABLE(test_1
   unit_test.cpp
)

TARGET_LINK_LIBRARIES(test_1 gtest)

TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)

