#include <gtest/gtest.h>
#include <filesystem>

extern "C" {
	#include "ft_ls.h"
}

std::string	exec(const std::string &command) {
	char		buffer[128];
	std::string	result = "";

	FILE *pipe = popen(command.c_str(), "r");
	if (!pipe)
		write(2, "error\n", 6);
	while(!feof(pipe)) {
		if (fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	return (result);
}

/*---------------------LIST----------------------------*/

class StackTest : public ::testing::Test {
	protected:
		struct s_dir	*stack;


	void SetUp() override {
		stack = (struct s_dir*)malloc(sizeof(struct s_dir));
	}

	void TearDown() override {
	}
};

TEST_F(StackTest, newNode_isEmpty) {
	EXPECT_EQ(true, is_empty(stack));
}

TEST_F(StackTest, afterOnePush_isNotEmpty) {
	EXPECT_EQ(true, s_dir_push(&stack, "one"));
	EXPECT_EQ(false, is_empty(stack));
	EXPECT_EQ(1, stack->size);
}

TEST_F(StackTest, afterOnePushOnePop_isEmpty) {
	EXPECT_EQ(true, s_dir_push(&stack, "one"));
	EXPECT_STREQ(stack->head->file, "one");
	EXPECT_EQ(true, s_dir_pop(&stack));
	EXPECT_EQ(true, is_empty(stack));
	EXPECT_EQ(0, stack->size);
}

TEST_F(StackTest, newStackPop_isEmpty_underflow) {
	EXPECT_EQ(-1, s_dir_pop(&stack));
	EXPECT_EQ(0, stack->size);
}

TEST_F(StackTest, afterTwoPushOnePop_sizeOne) {
	EXPECT_EQ(true, s_dir_push(&stack, "one"));
	EXPECT_STREQ(stack->head->file, "one");
	EXPECT_EQ(true, s_dir_push(&stack, "two"));
	EXPECT_STREQ(stack->head->file, "two");
	EXPECT_EQ(true, s_dir_pop(&stack));
	EXPECT_EQ(false, is_empty(stack));
	EXPECT_EQ(1, stack->size);
}

TEST_F(StackTest, afterTwoPushTwoPop_sizeZero) {
	EXPECT_EQ(true, s_dir_push(&stack, "one"));
	EXPECT_STREQ(stack->head->file, "one");
	EXPECT_EQ(true, s_dir_push(&stack, "two"));
	EXPECT_STREQ(stack->head->file, "two");
	EXPECT_EQ(true, s_dir_pop(&stack));
	EXPECT_EQ(true, s_dir_pop(&stack));
	EXPECT_EQ(true, is_empty(stack));
	EXPECT_EQ(0, stack->size);
}

TEST_F(StackTest, afterTwoPushThreePop_underflow) {
	EXPECT_EQ(true, s_dir_push(&stack, "one"));
	EXPECT_STREQ(stack->head->file, "one");
	EXPECT_EQ(true, s_dir_push(&stack, "two"));
	EXPECT_STREQ(stack->head->file, "two");
	EXPECT_EQ(true, s_dir_pop(&stack));
	EXPECT_EQ(true, s_dir_pop(&stack));
	EXPECT_EQ(-1, s_dir_pop(&stack));
	EXPECT_EQ(0, stack->size);
}

/*----------------------SORT----------------------------*/


TEST_F(StackTest, emptyNode_isSorted) {
	EXPECT_EQ(true, s_dir_is_sorted(stack));
}

TEST_F(StackTest, nodeWithOne_isSorted) {
	s_dir_push(&stack, "one");
	EXPECT_EQ(true, s_dir_is_sorted(stack));
}

TEST_F(StackTest, nodeWithTwo_isSorted) {
	s_dir_push(&stack, "one");
	s_dir_push(&stack, "two");
	EXPECT_EQ(true, s_dir_is_sorted(stack));
}

TEST_F(StackTest, nodeWithTwo_isNotSorted) {
	s_dir_push(&stack, "two");
	s_dir_push(&stack, "one");
	EXPECT_EQ(false, s_dir_is_sorted(stack));
}

TEST_F(StackTest, nodeWithThree_isSorted) {
	s_dir_push(&stack, "abc");
	s_dir_push(&stack, "acb");
	s_dir_push(&stack, "adb");
	EXPECT_EQ(true, s_dir_is_sorted(stack));
}

TEST_F(StackTest, nodeWithThree_isNotSorted) {
	s_dir_push(&stack, "abc");
	s_dir_push(&stack, "adb");
	s_dir_push(&stack, "acb");
	EXPECT_EQ(false, s_dir_is_sorted(stack));
}

TEST_F(StackTest, nodeWithMoreThanThree_isSorted) {
	s_dir_push(&stack, "abc");
	s_dir_push(&stack, "acar");
	s_dir_push(&stack, "adb");
	s_dir_push(&stack, "bar");
	s_dir_push(&stack, "baz");
	s_dir_push(&stack, "boar");
	s_dir_push(&stack, "car");
	s_dir_push(&stack, "foo");
	s_dir_push(&stack, "stoor");
	EXPECT_EQ(true, s_dir_is_sorted(stack));
}

TEST_F(StackTest, nodeWithMoreThanThree_isNotSorted) {
	s_dir_push(&stack, "abc");
	s_dir_push(&stack, "adb");
	s_dir_push(&stack, "bar");
	s_dir_push(&stack, "car");
	s_dir_push(&stack, "stoor");
	s_dir_push(&stack, "foo");
	s_dir_push(&stack, "baz");
	s_dir_push(&stack, "acar");
	s_dir_push(&stack, "boar");
	EXPECT_EQ(false, s_dir_is_sorted(stack));
}

/*----------------------FT_LS----------------------------*/

TEST(FT_LS, emptyDirectory_noArguments) {
	system("mkdir emptyDir && cd emptyDir");
	std::string original_command = exec("cd emptyDir && ls");
	std::string my_command = exec("export PATH=$PATH:$PWD && cd emptyDir && ft_ls");
	EXPECT_EQ(my_command, original_command);
	system("rmdir emptyDir");
}

TEST(FT_LS, emptyDirectory) {
	system("mkdir emptyDir");
	std::string original_command = exec("ls emptyDir");
	std::string my_command = exec("export PATH=$PATH:$PWD && ft_ls emptyDir");
	EXPECT_EQ(my_command, original_command);
	system("rmdir emptyDir");
}

TEST(FT_LS, directoryWithOneFile) {
	system("mkdir emptyDir && touch emptyDir/file");
	std::string original_command = exec("ls emptyDir");
	std::string my_command = exec("../ft_ls emptyDir 2> /dev/null || ./ft_ls emptyDir");
	EXPECT_EQ(my_command, original_command);
	system("rm -rf emptyDir");
}

TEST(FT_LS, directoryWithTwoFiles) {
	system("mkdir emptyDir && touch emptyDir/file && touch emptyDir/filf");
	std::string original_command = exec("ls emptyDir");
	std::string my_command = exec("../ft_ls emptyDir 2> /dev/null || ./ft_ls emptyDir");
	EXPECT_EQ(my_command, original_command);
	system("rm -rf emptyDir");
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
