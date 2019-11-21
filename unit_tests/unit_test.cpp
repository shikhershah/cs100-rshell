//#include <string>	
//#include <iostream>

#include "gtest/gtest.h"
#include "../header/Base.h"
#include "../header/Parser.h"
#include "../header/AndLogicOp.h"
#include "../header/OrLogicOp.h"


using namespace std;
TEST(string_test,Parser_run) {
Base* user_test = new Parser("ls- a && ls -b" );

EXPECT_EQ(user_test->run(), 1);
}

/*TEST(string_test,Parser_dissect) {
Base* user_test = new Parser("ls- a && ls -b" );

EXPECT_EQ(user_test->dissect(), 1);
}
*/
TEST(string_test,Parser_fail) {
Base* user_test = new Parser("" );

EXPECT_EQ(user_test->run(), 0);
}



TEST(string_test,and_success) {
Base* user_test = new AndLogicOp("ls- a","ls -b" );

EXPECT_EQ(user_test->run(), 1);
}

TEST(string_test, and_fail){
Base* user_test = new AndLogicOp("ls -a ", "") ;

EXPECT_EQ(user_test->run(),0);
}

TEST(string_test, or_success) {
Base* user_test = new OrLogicOp("ls -a", "ls -b");

EXPECT_EQ(user_test->run(), 1);
}

TEST(string_test, or_fail) {
Base* user_test = new OrLogicOp("ls -a", "");

EXPECT_EQ(user_test->run(), 0);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

