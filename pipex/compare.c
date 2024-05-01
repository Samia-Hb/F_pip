#include "pipex.h"
char *get_executable(char *command, char *path)
{
    int i;
    char *full_path;
    char **dir;

    i = 0;
    dir = ft_split(path, ':');
    while (dir[i])
    {
        full_path = malloc(strlen(dir[i]) + strlen(command) + 2);
        if (full_path == NULL)
        {
            perror("malloc");
            exit(1);
        }
        strcpy(full_path, dir[i]);
        strcat(full_path, "/");
        strcat(full_path, command);
        if (access(full_path, X_OK) == 0)
            break;
        free(full_path);
        i++;
    }
    free(dir);
    if(dir[i])
        return full_path;
    return NULL;
    //return (dir[i] ? full_path : NULL);
}