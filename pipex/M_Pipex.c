# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <stddef.h>
# include <sys/types.h>
# include <stddef.h>
# include <sys/stat.h>
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"

int main(int argc, char **argv, char **envp)
{
    if(argc == 5)
    {
        check_arguments(argv,envp);
        char **arr = ft_split(argv[2]);
        
    }
    else
    {
        ft_printf("Usage:  <infile> <cmd1> <cmd2> <outfile>\n");
    }
}