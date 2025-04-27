#include <gtest/gtest.h>

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
		t_dir*	dir;
		t_file*	file;

	void SetUp() override {
		dir = (t_dir*)malloc(sizeof(t_dir));
	}

	void TearDown() override {
	}
};

TEST_F(StackTest, emptyList_isEmpty) {
	EXPECT_EQ(true, s_dir_is_empty(dir));
}

TEST_F(StackTest, afterOnePush_isNotEmpty) {
	EXPECT_EQ(true, s_dir_push(&dir, "one"));
	EXPECT_STREQ(dir->files->name, "one");
	EXPECT_EQ(false, s_dir_is_empty(dir));
	EXPECT_EQ(1, dir->size);
}

TEST_F(StackTest, afterOnePushOnePop_isEmpty) {
	EXPECT_EQ(true, s_dir_push(&dir, "one"));
	EXPECT_STREQ(dir->files->name, "one");
	EXPECT_EQ(true, s_dir_pop(&dir));
	EXPECT_EQ(NULL, dir->files);
	EXPECT_EQ(true, s_dir_is_empty(dir));
	EXPECT_EQ(0, dir->size);
}

TEST_F(StackTest, newStackPop_isEmpty_underflow) {
	t_dir*	empty_dir = NULL;
	EXPECT_EQ(-1, s_dir_pop(NULL));
	EXPECT_EQ(-1, s_dir_pop(&empty_dir));
	EXPECT_EQ(-1, s_dir_pop(&dir));
	EXPECT_EQ(0, dir->size);
}

TEST_F(StackTest, afterTwoPushOnePop_sizeOne) {
	EXPECT_EQ(true, s_dir_push(&dir, "one"));
	EXPECT_STREQ(dir->files->name, "one");
	EXPECT_EQ(true, s_dir_push(&dir, "two"));
	EXPECT_STREQ(dir->files->name, "two");
	EXPECT_EQ(true, s_dir_pop(&dir));
	EXPECT_STREQ(dir->files->name, "one");
	EXPECT_EQ(false, s_dir_is_empty(dir));
	EXPECT_EQ(1, dir->size);
}

TEST_F(StackTest, afterTwoPushTwoPop_sizeZero) {
	EXPECT_EQ(true, s_dir_push(&dir, "one"));
	EXPECT_STREQ(dir->files->name, "one");
	EXPECT_EQ(true, s_dir_push(&dir, "two"));
	EXPECT_STREQ(dir->files->name, "two");
	EXPECT_EQ(true, s_dir_pop(&dir));
	EXPECT_STREQ(dir->files->name, "one");
	EXPECT_EQ(true, s_dir_pop(&dir));
	EXPECT_EQ(NULL, dir->files);
	EXPECT_EQ(true, s_dir_is_empty(dir));
	EXPECT_EQ(0, dir->size);
}

TEST_F(StackTest, afterTwoPushThreePop_underflow) {
	EXPECT_EQ(true, s_dir_push(&dir, "one"));
	EXPECT_STREQ(dir->files->name, "one");
	EXPECT_EQ(true, s_dir_push(&dir, "two"));
	EXPECT_STREQ(dir->files->name, "two");
	EXPECT_EQ(true, s_dir_pop(&dir));
	EXPECT_STREQ(dir->files->name, "one");
	EXPECT_EQ(true, s_dir_pop(&dir));
	EXPECT_EQ(NULL, dir->files);
	EXPECT_EQ(-1, s_dir_pop(&dir));
	EXPECT_EQ(0, dir->size);
}

/*---------------------newFile----------------------------*/

TEST_F(StackTest, newFileWithNoName_expectNull) {
	t_file*	file;
	EXPECT_EQ(NULL,t_file_new(""));
}

/*---------------------Push----------------------------*/

TEST_F(StackTest, pushNoName_expectErr) {
	EXPECT_EQ(-1,s_dir_push(&dir, ""));
}

TEST_F(StackTest, pushIntoNullDir_expectErr) {
	t_dir*	empty_dir = NULL;
	EXPECT_EQ(-1,s_dir_push(&empty_dir , "one"));
	EXPECT_EQ(-1,s_dir_push(NULL, "one"));
}

/*----------------------SORT----------------------------*/

TEST_F(StackTest, emptyNode_isSorted) {
	EXPECT_EQ(true, s_dir_is_sorted(dir));
}

TEST_F(StackTest, nodeWithOne_isSorted) {
	s_dir_push(&dir, "one");
	EXPECT_EQ(true, s_dir_is_sorted(dir));
}

TEST_F(StackTest, nodeWithTwo_isSorted) {
	s_dir_push(&dir, "one");
	s_dir_push(&dir, "two");
	EXPECT_EQ(true, s_dir_is_sorted(dir));
}

TEST_F(StackTest, nodeWithTwo_isNotSorted) {
	s_dir_push(&dir, "two");
	s_dir_push(&dir, "one");
	EXPECT_EQ(false, s_dir_is_sorted(dir));
}

TEST_F(StackTest, nodeWithThree_isSorted) {
	s_dir_push(&dir, "abc");
	s_dir_push(&dir, "acb");
	s_dir_push(&dir, "adb");
	EXPECT_EQ(true, s_dir_is_sorted(dir));
}

TEST_F(StackTest, nodeWithThree_isNotSorted) {
	s_dir_push(&dir, "abc");
	s_dir_push(&dir, "adb");
	s_dir_push(&dir, "acb");
	EXPECT_EQ(false, s_dir_is_sorted(dir));
}

TEST_F(StackTest, nodeWithMoreThanThree_isSorted) {
	s_dir_push(&dir, "abc");
	s_dir_push(&dir, "acar");
	s_dir_push(&dir, "adb");
	s_dir_push(&dir, "bar");
	s_dir_push(&dir, "baz");
	s_dir_push(&dir, "boar");
	s_dir_push(&dir, "car");
	s_dir_push(&dir, "foo");
	s_dir_push(&dir, "stoor");
	EXPECT_EQ(true, s_dir_is_sorted(dir));
}

TEST_F(StackTest, nodeWithMoreThanThree_isNotSorted) {
	s_dir_push(&dir, "abc");
	s_dir_push(&dir, "adb");
	s_dir_push(&dir, "bar");
	s_dir_push(&dir, "car");
	s_dir_push(&dir, "stoor");
	s_dir_push(&dir, "foo");
	s_dir_push(&dir, "baz");
	s_dir_push(&dir, "acar");
	s_dir_push(&dir, "boar");
	EXPECT_EQ(false, s_dir_is_sorted(dir));
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
