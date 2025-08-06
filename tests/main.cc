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
	std::cout<<result<<std::endl;
	pclose(pipe);
	return (result);
}

// UNIT TESTS:

TEST(FT_LS, handleArgs_noArgs) {
	int argc = 2;
	const char *args[argc] = {"./ft_ls", NULL};
	ASSERT_EQ(0, handle_args(args, argc));
}

TEST(FT_LS, handleArgs_oneArg_validPath) {
	int argc = 3;
	const char *args[argc] = {"./ft_ls", "src", NULL};
	ASSERT_EQ(0, handle_args(args, argc));
}

TEST(FT_LS, handleArgs_oneArg_validOption) {
	int argc = 3;
	const char *args[argc] = {"./ft_ls", "-l", NULL};
	ASSERT_EQ(0, handle_args(args, argc));
}

TEST(FT_LS, handleArgs_oneArg_invalidOption) {
	int argc = 3;
	const char *args[argc] = {"./ft_ls", "-x", NULL};
	std::string error = "ft_ls: invalid option -- 'x'\nTry 'ls --help' for more information.\n";
	ASSERT_EXIT(handle_args(args, argc), testing::ExitedWithCode(2), error);
}

TEST(FT_LS, handleArgs_oneArg_invalidPath) {
	int argc = 3;
	const char *args[argc] = {"./ft_ls", "xxx", NULL};
	std::string error = "ft_ls: cannot access 'xxx': No such file or directory\n";
	testing::internal::CaptureStderr();
	ASSERT_EQ(2, handle_args(args, argc));
	std::string capture = testing::internal::GetCapturedStderr();
	ASSERT_EQ(capture, error);
}

TEST(FT_LS, handleArgs_oneArg_invalidPathThenFlag_flagError) {
	int argc = 4;
	const char *args[argc] = {"./ft_ls", "xxx", "-x", NULL};
	std::string error = "ft_ls: invalid option -- 'x'\nTry 'ls --help' for more information.\n";
	ASSERT_EXIT(handle_args(args, argc), testing::ExitedWithCode(2), error);
}

TEST(FT_LS, handleArgs_multiplePaths_sameNumberOfErrors) {
	int argc = 5;
	const char *args[argc] = {"./ft_ls", "xxx", "xyz", "yyy", "zzz", NULL};
	std::string error = "ft_ls: cannot access 'xxx': No such file or directory\n"
						"ft_ls: cannot access 'xyz': No such file or directory\n"
						"ft_ls: cannot access 'yyy': No such file or directory\n"
						"ft_ls: cannot access 'zzz': No such file or directory\n";
	testing::internal::CaptureStderr();
	ASSERT_EQ(2, handle_args(args, argc));
	std::string capture = testing::internal::GetCapturedStderr();
	ASSERT_EQ(capture, error);


}

TEST(FT_LS, isValidFlag) {
}

TEST(FT_LS, isValidFlag_NULL_throwsError) {
}

TEST(FT_LS, isValidFlag_invalidFlag_throwsError) {
}

// UNIT TESTS.

/*
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
*/

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
