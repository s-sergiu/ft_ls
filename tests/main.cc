#include <gtest/gtest.h>

extern "C" {
	#include "ft_ls.h"
}

std::string exec_ft_ls(const std::string &args) {
	std::string command = "./ft_ls " + args;
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

TEST(FT_LS, emptyDirectory) {
	system("mkdir emptyDirectory");
	std::string result = exec_ft_ls("./emptyDirectory");
	EXPECT_EQ("", result);
	system("rmdir emptyDirectory");
}

TEST(FT_LS, directoryWithOneFile) {
	system("mkdir emptyDirectory; touch emptyDirectory/file");
	std::string result = exec_ft_ls("./emptyDirectory");
	EXPECT_EQ("file", result);
	system("rm -rf emptyDirectory");
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
