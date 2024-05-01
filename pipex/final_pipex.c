#include "pipex.h"

void ft_putstr(char *str) // done
{
	int i = 0;
	while(str[i])
	{
		write(1,&str[i],1);
		i++;
	}
}
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
    return path_env;
}

char *get_executable(char *command, char *path)
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
        strcpy(full_path, dir[i]);
        strcat(full_path, "/");
        strcat(full_path, command);
        if (access(full_path, X_OK) == 0)
        {
            break;
        }
        free(full_path);
        full_path = NULL;
        i++;
    }
    free(dir);
    return full_path;
}
char *execute_command(char *full_command, char **envp, char *file_name) {
    int pid = fork();
    char *buff = NULL;
    if (pid > 0) {
        wait(NULL);
    } else if (pid == 0) {
        char **arr = ft_split(full_command,' '); // Split the full command
        int arr_count = 0;
        while (arr[arr_count] != NULL) {
            arr_count++;
        }
        char **new_arr = malloc((arr_count + 2) * sizeof(char *));
        if (new_arr == NULL) {
            perror("malloc");
            exit(1);
        }
        for (int i = 0; i < arr_count; i++) {
            new_arr[i] = arr[i];
        }
        new_arr[arr_count] = file_name;
        new_arr[arr_count + 1] = NULL;

        char *command_path = get_executable(new_arr[0], find_path(envp));
        int ex = execve(command_path, new_arr, envp);
        if (ex == -1)
        {
            perror("execve");
            exit(1);
        }
    } else {
        perror("fork");
        exit(1);
    }

    return buff;
}

int main(int args,char **argv,char **envp)
{
    if(args == 5)
    {
        if(access(argv[1],F_OK) == 0)
        {
            int i = 0;
            char *buff; 
            buff = execute_command(argv[2],envp,argv[1]);
                            //read from buff to a middle file
            int fd = open("M_FILE.txt",O_CREAT | O_RDWR | O_TRUNC,0777);
            if(fd == -1)
            {
                free(buff);
                perror("open");
            }
            while(buff[i])
            {
                write (fd,&buff[i],1);
                i++;
            }
            buff = execute_command(argv[3],envp,argv[4]); //I have to add the file name
            int fd1 = open(argv[4],O_CREAT | O_RDWR , 0777);
            if(fd1 == -1){
                perror("open_last_file");
                return 0;
            }
            i = 0;
            while(buff[i])
            {
                write(fd1,&buff[i],1);
                i++;
            }
        }
        else
        {
            perror("zsh");
        }
    }
}


// char *execute_command(char *full_command,char **envp,char *file_name)
// {
//     int pid = fork();
//     char *buff;
//     if(pid > 0)
//         wait(NULL);
//     else if(pid == 0)
//     {
//         char **arr = ft_split(command); //I have to include the file_name in the array as the first element
//         char *command_path = get_executable(arr[0],find_path(envp));
//         int ex = execve(command_path,arr,envp);
//         if(ex == -1)
//         {
//             perror("execve");
//             exit(1);
//         }
//         int dp = dup2(fd[0],STDOUT_FILENO);
//         if(dp == -1)
//             return NULL;
//         buff = malloc(BUFFER_SIZE);
//         if(!buff)
//             return NULL;
//         int r = read(fd[0],buff,BUFFER_SIZE);
//         if(r == -1)
//         {
//             free(buff);
//             return NULL;
//         }
//     }
//     else
//         return NULL;
//     return buff;
// }