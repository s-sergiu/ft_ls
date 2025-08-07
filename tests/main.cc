#include <gtest/gtest.h>

extern "C" {
	#include "ft_ls.h"
}
using namespace	testing::internal;
using namespace	testing;
using namespace	std;

string	exec(const std::string &command) {
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

//	handle_args(const char**, int);

TEST(FT_LS, handleArgs_noArgs) {
	int			argc = 1;
	const char	*args[argc] = {"./ft_ls", NULL};

	ASSERT_EQ(0, handle_args(args, argc));
}

TEST(FT_LS, handleArgs_oneArg_validPath) {
	int			argc = 2;
	const char	*args[argc] = {"./ft_ls", "src", NULL};

	ASSERT_EQ(0, handle_args(args, argc));
}

TEST(FT_LS, handleArgs_oneArg_validOption) {
	int			argc = 2;
	const char	*args[argc] = {"./ft_ls", "-l", NULL};

	ASSERT_EQ(0, handle_args(args, argc));
}

TEST(FT_LS, handleArgs_oneArg_invalidOptionMinus) {
	int			argc = 2;
	const char	*args[argc] = {"./ft_ls", "-", NULL};
	string err = "ft_ls: cannot access '-': No such file or directory\n";

	ASSERT_EXIT(handle_args(args, argc), ExitedWithCode(2), err);
}

TEST(FT_LS, handleArgs_oneArg_invalidOption) {
	int			argc = 2;
	const char	*args[argc] = {"./ft_ls", "-x", NULL};
	string		err = "ft_ls: invalid option -- 'x'\n"
					  "Try 'ls --help' for more information.\n";

	ASSERT_EXIT(handle_args(args, argc), ExitedWithCode(2), err);
}

TEST(FT_LS, handleArgs_oneArg_invalidPath) {
	int			argc = 2;
	const char	*args[argc] = {"./ft_ls", "xxx", NULL};
	string		err = "ft_ls: cannot access 'xxx': "
					  "No such file or directory\n";

	CaptureStderr();
	ASSERT_EQ(2, handle_args(args, argc));

	string		capture = GetCapturedStderr();

	ASSERT_EQ(capture, err);
}

TEST(FT_LS, handleArgs_oneArg_invalidPathThenFlag_flagError) {
	int			argc = 3;
	const char	*args[argc] = {"./ft_ls", "xxx", "-x", NULL};
	string		err = "ft_ls: invalid option -- 'x'\n"
					  "Try 'ls --help' for more information.\n";

	ASSERT_EXIT(handle_args(args, argc), ExitedWithCode(2), err);
}

TEST(FT_LS, handleArgs_multiplePaths_sameNumberOfErrors) {
	int			argc = 5;
	const char	*args[argc] = {"./ft_ls", "xxx", "xyz", "yyy", "zzz", NULL};
	string		err = "ft_ls: cannot access 'xxx': "
					  "No such file or directory\n"
					  "ft_ls: cannot access 'xyz': "
					  "No such file or directory\n"
					  "ft_ls: cannot access 'yyy': "
					  "No such file or directory\n"
					  "ft_ls: cannot access 'zzz': "
					  "No such file or directory\n";
	CaptureStderr();
	ASSERT_EQ(2, handle_args(args, argc));
	string capture = GetCapturedStderr();
	ASSERT_EQ(capture, err);


}

//	is_valid_flag(const char**, int);

TEST(FT_LS, isValidFlagList) {
	int			argc = 3;
	const char	*program = "./ft_ls";
	char		*flags[6] = {"-l", "-R", "a", "r", "t", NULL};
	const char	*args[argc] = {program, flags[0], NULL};

	for (int i = 0; i < 5; i++) {
		args[1] = flags[i];
		ASSERT_EQ(0, is_valid_flag(args, 1));
	}
}

TEST(FT_LS, isValidFlagListWithInvalidFlagAtEnding) {
	int			argc = 3;
	const char	*args[argc] = {"./ft_ls", "-larz", NULL};
	string		err = "ft_ls: invalid option -- 'z'\n"
					  "Try 'ls --help' for more information.\n";

	ASSERT_EXIT(is_valid_flag(args, 1), ExitedWithCode(2), err);
}

TEST(FT_LS, isValidFlag_NULL_throwsError) {
	ASSERT_EQ(1, is_valid_flag(NULL, 1));
}

TEST(FT_LS, isValidFlag_invalidFlag_throwsError) {
	int			argc = 2;
	const char	*program = "./ft_ls";
	const char	*args[argc] = {program, "-z", NULL};
	string		err = "ft_ls: invalid option -- 'z'\n"
					  "Try 'ls --help' for more information.\n";

	ASSERT_EXIT(is_valid_flag(args, 1), ExitedWithCode(2), err);
}

// UNIT TESTS.

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
