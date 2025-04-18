#include <gtest/gtest.h>

extern "C" {
	#include "ft_ls.h"
}

std::string exec_ft_ls(const std::string &command) {
	char buffer[128];
	std::string result = "";

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

TEST(FT_LS, noArguments) {
	system("mkdir emptyDir; export PWD=/home/ssergiu/projects/ft_ls/emtpyDir");
	std::string original_command = exec_ft_ls("cd emptyDir && ls");
	std::string my_command = exec_ft_ls("cd emptyDir && ../ft_ls");
	EXPECT_EQ(my_command, original_command);
	system("rmdir emptyDir");
}

TEST(FT_LS, emptyDirectory) {
	system("mkdir emptyDir");
	std::string original_command = exec_ft_ls("ls emptyDir");
	std::string my_command = exec_ft_ls("./ft_ls emptyDir");
	EXPECT_EQ(my_command, original_command);
	system("rmdir emptyDir");
}

TEST(FT_LS, directoryWithOneFile) {
	system("mkdir emptyDir; touch emptyDir/file");
	std::string original_command = exec_ft_ls("ls emptyDir");
	std::string my_command = exec_ft_ls("./ft_ls emptyDir");
	EXPECT_EQ(my_command, original_command);
	system("rm -rf emptyDir");
}

TEST(FT_LS, directoryWithTwoFiles) {
	system("mkdir emptyDir; touch emptyDir/file; touch emptyDir/file1");
	std::string original_command = exec_ft_ls("ls emptyDir");
	std::string my_command = exec_ft_ls("./ft_ls emptyDir");
	EXPECT_EQ(my_command, original_command);
	system("rm -rf emptyDir");
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
