cmake_minimum_required(VERSION 3.14)
project(ft_ls)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(GTEST_VERSION 1.16.0)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories("${CMAKE_SOURCE_DIR}/include",
					"${CMAKE_SOURCE_DIR}/libs/Libft/include")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/releases/download/v${GTEST_VERSION}/googletest-${GTEST_VERSION}.tar.gz
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_library(ls STATIC src/tools/utils.c include/ft_ls.h)
add_library(ft STATIC libs/Libft/src/ft_printf.c libs/Libft/src/ft_strlcat.c
			libs/Libft/src/ft_strlen.c libs/Libft/src/ft_putchar_fd.c
			libs/Libft/src/ft_strncmp.c libs/Libft/src/printf_utils.c
			libs/Libft/src/check_utils.c libs/Libft/src/ft_itoa.c
			libs/Libft/src/ft_putnbr_fd.c libs/Libft/src/ft_putstr_fd.c
			libs/Libft/src/ft_itoa_unsigned.c libs/Libft/include/libft.h)

add_executable(
  hello_test
  tests/main.cc
)
target_link_libraries(
  hello_test
  PRIVATE 
  ls
  ft
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
