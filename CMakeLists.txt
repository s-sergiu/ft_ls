cmake_minimum_required(VERSION 3.14)
project(ft_ls)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories("${CMAKE_SOURCE_DIR}/include", "${CMAKE_SOURCE_DIR}/libs/libft/include")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_library(utils  src/tools/utils.c)
add_library(lft STATIC libs/libft/src/ft_printf.c libs/libft/src/ft_strlcat.c libs/libft/src/ft_strlen.c
			libs/libft/src/ft_putchar_fd.c libs/libft/src/ft_strncmp.c libs/libft/src/printf_utils.c
			libs/libft/src/check_utils.c libs/libft/src/ft_itoa.c libs/libft/src/ft_putnbr_fd.c 
			libs/libft/src/ft_putstr_fd.c libs/libft/src/ft_itoa_unsigned.c)

add_executable(
  hello_test
  tests/main.cc
)
target_link_libraries(
  hello_test
  lft
  utils
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test)
