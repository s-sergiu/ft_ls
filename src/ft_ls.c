
#include "ft_ls.h"

t_flags	*init_flags(void) {
	t_flags *flags;

	flags = (t_flags *)malloc(sizeof(t_flags));
	flags->exit_status = EXIT_SUCCESS;
	flags->valid_dirs = 0;

	return (flags);
}

int		main(int argc, const char **argv, char **envp) 
{
	t_flags	*flags;

	flags = init_flags();
	(void)envp;
	flags->exit_status = handle_args(argv, argc);
	if (flags->valid_dirs > 0)
		execute(argv);
	return(flags->exit_status);
}
