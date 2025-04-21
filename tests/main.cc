#include <gtest/gtest.h>

extern "C" {
	#include "ft_ls.h"
}

int	list_size(struct s_dir *lst)
{
	int				i;
	struct s_dir	*tmp;

	tmp = lst->head;
	i = 0;
	while (tmp->next)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
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

/*---------------------LIST----------------------------*/

class StackTest : public ::testing::Test {
	protected:
		struct s_dir	*stack;


	void SetUp() override {
		this->stack = get_directory_list();
	}

	void TearDown() override {
	}
};

TEST_F(StackTest, newNode_isEmpty) {
	EXPECT_EQ(true, is_empty(stack));
}

TEST_F(StackTest, afterOnePush_isNotEmpty) {
	s_dir_push(&stack, "one");
	EXPECT_EQ(false, is_empty(stack));
	EXPECT_EQ(1, list_size(stack));
}

/*----------------------FT_LS----------------------------*/

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
