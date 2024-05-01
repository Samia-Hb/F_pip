#include "pipex.h"

void check_cmds(char **arr)
{
    int i = 0;
    char cmp = 39;

    while(arr[i] != NULL)
    {
        if(arr[i][0] == cmp)
            arr[i] = ft_strtrim(arr[i],"'");
        i++;
    }
}
int main(int args, char **argv)
{
    (void)args;
    int i = 0;
    char **arr = ft_split(argv[1],' ');
    check_cmds(arr);
    while(arr[i])
    {
        printf("%s\n",arr[i]);
        i++;
    }
}