CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)
#ADD_SUBDIRECTORY(tests)


#add_library(tests unit_test.cpp)

SET(CMAKE_CXX_STANDARD 11)


ADD_EXECUTABLE(test 
	unit_tests/unit_test.cpp)

#ADD_EXECUTABLE(test_1  
#	test.cpp)

ADD_EXECUTABLE(rshell
	src/main.cpp)

 
TARGET_LINK_LIBRARIES(test gtest)

TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)

