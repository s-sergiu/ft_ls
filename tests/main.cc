
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
	t_data*		data;
	int			argc = 1;
	const char*	args[argc] = {"./ft_ls", NULL};

	data = init_data(argc, (char **)args);
	handle_args(data);
	ASSERT_EQ(0, data->exit_status);
}

TEST(FT_LS, handleArgs_oneArg_validPath) {
	t_data*		data;
	int			argc = 2;
	const char*	args[argc] = {"./ft_ls", "newfile", NULL};

	exec("mkdir newfile");
	data = init_data(argc, (char **)args);
	handle_args(data);
	ASSERT_EQ(0, data->exit_status);
	exec("rmdir newfile");
}

TEST(FT_LS, handleArgs_oneArg_validOption) {
	t_data*		data;
	int			argc = 2;
	const char*	args[argc] = {"./ft_ls", "-l", NULL};

	data = init_data(argc, (char **)args);
	handle_args(data);
	ASSERT_EQ(0, data->exit_status);
}

TEST(FT_LS, handleArgs_oneArg_invalidOptionMinus) {
	t_data*		data;
	int			argc = 2;
	const char*	args[argc] = {"./ft_ls", "-", NULL};
	string		err = "ft_ls: cannot access '-': No such file or directory\n";

	data = init_data(argc, (char **)args);
	CaptureStderr();
	handle_args(data);
	ASSERT_EQ(2, data->exit_status);

	string		capture = GetCapturedStderr();

	ASSERT_EQ(capture, err);
}

TEST(FT_LS, handleArgs_oneArg_invalidOption) {
	t_data*		data;
	int			argc = 2;
	const char*	args[argc] = {"./ft_ls", "-x", NULL};
	string		err = "ft_ls: invalid option -- 'x'\n"
					  "Try 'ls --help' for more information.\n";

	data = init_data(argc, (char **)args);
	ASSERT_EXIT(handle_args(data), ExitedWithCode(2), Eq(err));
}

TEST(FT_LS, handleArgs_oneArg_invalidPath) {
	t_data*		data;
	int			argc = 2;
	const char*	args[argc] = {"./ft_ls", "xxx", NULL};
	string		err = "ft_ls: cannot access 'xxx': "
					  "No such file or directory\n";

	data = init_data(argc, (char **)args);
	CaptureStderr();
	handle_args(data);
	ASSERT_EQ(2, data->exit_status);

	string		capture = GetCapturedStderr();

	ASSERT_EQ(capture, err);
}

TEST(FT_LS, handleArgs_twoArgs_invalidPathThenInvalidFlag_flagError) {
	t_data*		data;
	int			argc = 3;
	const char*	args[argc] = {"./ft_ls", "xxx", "-x", NULL};
	string		err = "ft_ls: invalid option -- 'x'\n"
					  "Try 'ls --help' for more information.\n";

	data = init_data(argc, (char **)args);
	ASSERT_EXIT(handle_args(data), ExitedWithCode(2), Eq(err));
}

TEST(FT_LS, handleArgs_twoArgs_invalidPathThenValidFlag_pathError) {
	t_data*		data;
	int			argc = 3;
	const char*	args[argc] = {"./ft_ls", "xxx", "-l", NULL};
	string		err = "ft_ls: cannot access 'xxx': "
					  "No such file or directory\n";

	data = init_data(argc, (char **)args);
	CaptureStderr();
	handle_args(data);
	ASSERT_EQ(2, data->exit_status);
	string		capture = GetCapturedStderr();
	ASSERT_EQ(capture, err);
}

TEST(FT_LS, handleArgs_multiplePaths_sameNumberOfErrors) {
	t_data*		data;
	int			argc = 5;
	const char*	args[argc] = {"./ft_ls", "xxx", "xyz", "yyy", NULL};
	string		err = "ft_ls: cannot access 'xxx': "
					  "No such file or directory\n"
					  "ft_ls: cannot access 'xyz': "
					  "No such file or directory\n"
					  "ft_ls: cannot access 'yyy': "
					  "No such file or directory\n";
	data = init_data(argc, (char **)args);
	CaptureStderr();
	handle_args(data);
	ASSERT_EQ(2, data->exit_status);
	string		capture = GetCapturedStderr();
	ASSERT_EQ(capture, err);
}

//	is_valid_flag(const char**, int);

TEST(FT_LS, isValidFlagList) {
	int			argc = 3;
	const char*	program = "./ft_ls";
	const char*	flags[6] = {"-l", "-R", "a", "r", "t", NULL};
	const char*	args[argc] = {program, flags[0], NULL};

	for (int i = 0; i < 5; i++) {
		args[1] = flags[i];
		ASSERT_EQ(0, is_valid_flag((char *)args[1]));
	}
}

TEST(FT_LS, isValidFlagListWithInvalidFlagAtEnding) {
	int			argc = 3;
	const char*	args[argc] = {"./ft_ls", "-larz", NULL};
	string		err = "ft_ls: invalid option -- 'z'\n"
					  "Try 'ls --help' for more information.\n";

	ASSERT_EXIT(is_valid_flag((char *)args[1]), ExitedWithCode(2), Eq(err));
}

TEST(FT_LS, isValidFlag_NULL_throwsError) {
	ASSERT_EQ(1, is_valid_flag(NULL));
}

TEST(FT_LS, isValidFlag_invalidFlag_throwsError) {
	int			argc = 2;
	const char*	program = "./ft_ls";
	const char*	args[argc] = {program, "-z", NULL};
	string		err = "ft_ls: invalid option -- 'z'\n"
					  "Try 'ls --help' for more information.\n";

	ASSERT_EXIT(is_valid_flag((char *)args[1]), ExitedWithCode(2), Eq(err));
}

// UNIT TESTS.

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
