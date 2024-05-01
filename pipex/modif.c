#include "pipex.h"

char *find_path(char **envp) //done
{
    char *path_env = NULL;
    int i = 0;
    while(envp[i])
    {
        if(strncmp(envp[i], "PATH=", 5) == 0)
        {
            path_env = envp[i] + 5;
            break;
        }
        i++;
    }
    return (path_env);
}

char *get_executable(char *command, char *path) //done
{
    int i = 0;
    char *full_path = NULL;
    char **dir = ft_split(path, ':');
    while (dir[i])
    {
        full_path = malloc(strlen(dir[i]) + strlen(command) + 2);
        if(full_path == NULL)
        {
            perror("malloc");
        	exit(1);
        }
        ft_strcpy(full_path, dir[i]);
        ft_strcat(full_path, "/");
        ft_strcat(full_path, command);
        if (access(full_path, X_OK) == 0)
            break;
        free(full_path);
        full_path = NULL;
        i++;
    }
    free(dir);
    return full_path;
}


char *execute_command(char *full_command, char **envp, int fd) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    int pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }else if (pid == 0)
    {
        char **arr;
        char **new_arr;
        char *command_path;
        int i;
        int arr_count  = 0;
        dup2(pipefd[1], STDOUT_FILENO);
        arr = ft_split(full_command, ' ');
        if (arr == NULL)
        {
            perror("split");
            exit(1);
        }
        // to handle what begin with ' '
        int H = 0 ;
        while(arr[H] != NULL)
        {
            char cmp = arr[H][0];
            if(arr[H][0] == cmp)
                arr[H] = ft_strtrim(arr[H],"'");
            H++;
        }
        while (arr[arr_count] != NULL)
            arr_count++;
        new_arr = malloc((arr_count + 2) * sizeof(char *));
        if (new_arr == NULL)
        {
            perror("malloc");
            exit(1);
        }
        i = 0;
        while(i < arr_count)
        {
            new_arr[i] = arr[i];
            i++;
        }
        new_arr[arr_count] = file_name;
        new_arr[arr_count + 1] = NULL;
        command_path = get_executable(new_arr[0], find_path(envp));
        int ex = execve(command_path, new_arr, envp);
        if (ex == -1)
        {
            perror("execve");
            exit(1);
        }
    }else
    {
        close(pipefd[1]);
        char buf[BUFSIZ];
        int nbytes = read(pipefd[0],buf, BUFSIZ);
        if (nbytes == -1)
        {
            perror("read");
            exit(1);
        }
        buf[nbytes] = '\0';
        char *output = ft_strdup(buf);
        /*if (output == NULL)
        {
            perror("strdup");
            exit(1);
        }*/
        close(pipefd[0]);
        wait(NULL);
        return output;
    }
    return NULL;
}

// int main(int argc, char **argv, char **envp) {
//     if (argc == 5)
//     {
//         if (access(argv[1], F_OK) == 0){
//             int ffd = open(argv[1], O_RDONLY);
//             char *buff = execute_command(argv[2], envp, ffd);
//             close(ffd);
//             if (buff == NULL)
//             {
//                 perror("execute_command");
//                 return 1;
//             }
//             int fd = open("M_FILE.txt", O_CREAT | O_WRONLY | O_TRUNC, 0777);
//             if(fd == -1)
//             {
//                 perror("open");
//                 free(buff);
//                 return 1;
//             }
//             write(fd, buff, ft_strlen(buff));
//             close(fd);
//             buff = execute_command(argv[3], envp, fd);
//             unlink("M_FILE.txt");
//             if (buff == NULL)
//             {
//                 perror("execute_command");
//                 return 1;
//             }
//             int fd1 = open(argv[4] ,O_WRONLY | O_CREAT | O_TRUNC, 0777);
//             if(fd1 == -1)
//             {
//                 perror("open");
//                 free(buff);
//                 return 1;
//             }
//             //printf("%s",buff_update(buff));
//             write(fd1, buff, strlen(buff));
//             close(fd1);
//             free(buff);
//         }else
//         {
//             perror("zsh");
//             return 1;
//         }
//     } else {
//         fprintf(stderr, "Incorrect number of arguments.\n");
//         return 1;
//     }
//     return 0;
// }
int main(int args,char **argv,char **envp)
{
    if(args == 5)
    {
        if(access(argv[1],F_OK) == 0)
        {
            char *buff;
            int fd = open(argv[1],O_RDONLY,0777);
            if(fd == -1)
            {
                perror("open");
                exit(1);
            }
            buff = execute_command(argv[2], envp, fd);
            if(!buff)
            {
                perror("buff1");
                exit (1);
            }
            close(fd);
            int fd1 = open("M_FILE.txt",O_CREAT | O_TRUNC | O_RDWR,0777);
            if(fd1 == -1)
            {
                perror("open1");
                exit(1);
            }
            write(fd,buff,strlen(buff));
            buff = execute_command(argv[3], envp, fd1);
            close(fd1);
            if(!buff)
            {
                perror("buff2");
                exit(1);
            }
            int fd2 = open(argv[4],O_CREAT | O_RDWR | O_TRUNC,0777);
            if(fd2  == -1)
            {
                perror("open2");
                exit(1);
            } 
            write(fd2,buff,strlen(buff));
            close(fd2);
            free(buff);
        }else
            ft_printf("zsh: no such file or directory: %s",argv[1]);
    }
}