#include <gtest/gtest.h>

extern "C" {
	#include "ft_ls.h"
}

std::string exec(const std::string &command) {
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

TEST(LIST, new_node_with_content) {
	struct s_dir	*list = NULL; 
	std::string		content = "new";

	list = s_dir_new((char *)content.c_str());

	EXPECT_NE(nullptr, list);
}

TEST(LIST, new_node_no_content) {
	struct s_dir	*list = NULL; 

	list = s_dir_new(NULL);

	EXPECT_EQ(nullptr, list);
}

TEST(FT_LS, noArguments) {
	system("mkdir emptyDir; export PWD=/home/ssergiu/projects/ft_ls/emtpyDir");
	std::string original_command = exec("cd emptyDir && ls");
	std::string my_command = exec("cd emptyDir && ../ft_ls");
	EXPECT_EQ(my_command, original_command);
	system("rmdir emptyDir");
}

TEST(FT_LS, emptyDirectory) {
	system("mkdir emptyDir");
	std::string original_command = exec("ls emptyDir");
	std::string my_command = exec("./ft_ls emptyDir");
	EXPECT_EQ(my_command, original_command);
	system("rmdir emptyDir");
}

TEST(FT_LS, directoryWithOneFile) {
	system("mkdir emptyDir; touch emptyDir/file");
	std::string original_command = exec("ls emptyDir");
	std::string my_command = exec("./ft_ls emptyDir");
	EXPECT_EQ(my_command, original_command);
	system("rm -rf emptyDir");
}

TEST(FT_LS, directoryWithTwoFiles) {
	system("mkdir emptyDir; touch emptyDir/file; touch emptyDir/filf");
	std::string original_command = exec("ls emptyDir");
	std::string my_command = exec("./ft_ls emptyDir");
	EXPECT_EQ(my_command, original_command);
	system("rm -rf emptyDir");
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
