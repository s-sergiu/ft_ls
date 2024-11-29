#include <gtest/gtest.h>

extern "C" {
	#include "ft_ls.h"
}

TEST(test, ok) {
		
	EXPECT_TRUE(1);
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
