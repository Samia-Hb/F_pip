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

int main(int args,char **argv,char **envp)
{
	if(args == 5)
	{
		if(access(argv[1],F_OK) == 0 && strchr(argv[2],' ') == NULL)
		{
			char* arr[]= {argv[2],argv[1],NULL};
			int pid = fork();
			if(pid == -1)
			{
				perror("fork");
				return 1;
			}
			if (pid == 0)
			{
				char *command_path = get_executable(argv[2],find_path(envp));
				int pp = execve(command_path,arr,NULL);
                if(pp == -1)
                {
                        perror("execve");
                        return 1;
                }
				perror("execve");
				return 1;
			}
			else
				wait(NULL);
		}
		else if(access(argv[1],F_OK) == 0 && strchr(argv[2],' ') != NULL)
		{
			char **command = ft_split(argv[2],' ');
			argv[3] = command[1];
			argv[2] = command[0];
			char *arr[] = {argv[2],argv[3],argv[1],NULL};
			int pid = fork();
			if(pid == -1)
			{
				perror("fork");
				return 1;
			}
			if(pid == 0)
			{
				char *command_path = get_executable(argv[2],find_path(envp));
				int pp = execve(command_path,arr,NULL);
                if(pp == -1)
                {
                        perror("execve");
                        return 1;
                }
				perror("execve");
				return 1;
			}
			else
				wait(NULL);
		}else
		{
			if (errno = ENOENT)
			{
				ft_putstr("zsh: ");
				ft_putstr(strerror(errno));
				ft_putstr(": ");
				ft_putstr(argv[1]);
			}
		}
		int i = 0;
		char *buff;
		buff = malloc(BUFFER_SIZE);
		int fd = open("tem.txt",O_CREAT | O_RDWR | O_TRUNC,0777);
		if(fd == -1)
			return 1;
		int pipe_fd[2];
		int k = dup(STDOUT_FILENO);
		if (k == -1)
			return 1;
		pipe_fd[0] = k;
		pipe_fd[1] = fd;
		int r = read(pipe_fd[0],buff,BUFFER_SIZE);
		if(r == -1)
			perror("Error");
		while(buff[i])
		{
			write(pipe_fd[1],&buff[i],1);
			i++;
		}
		free(buff);
							//second traitement
		if(strchr(argv[3],' ') == NULL)
		{
			char* arr[]= {argv[3],argv[4],NULL};
			int pid = fork();
			if(pid == -1)
			{
				perror("fork");
				return 1;
			}
			if(pid == 0)
			{
				char *command_path = get_executable(argv[3],find_path(envp));
				int pp = execve(command_path,arr,NULL);
            	if(pp == -1)
            	{
                    perror("execve");
                    return 1;
            	}
			}
		else
			wait(NULL);
		}
		else if(strchr(argv[3],' ') != NULL)
		{
			char **command = ft_split(argv[3],' ');
			argv[3] = command[1];
			argv[2] = command[0];
			char *arr[] = {argv[2],argv[3],argv[4],NULL};
			int pid = fork();
			if(pid == -1)
			{
				perror("fork");
				return 1;
			}
			if(pid == 0)
			{
				char *command_path = get_executable(argv[2],find_path(envp));
				int pp = execve(command_path,arr,NULL);
                if(pp == -1)
                {
                        perror("execve");
                        return 1;
                }
				perror("execve");
				return 1;
			}
			else
				wait(NULL);
		}
		//last step:
	i = 0;
	char *buff1;
	int op = open(argv[4],O_CREAT,0777);
	if(op == -1)
	{
		perror("open");
		exit(1);
	}
	buff1 = malloc(BUFFER_SIZE);
	int dp = dup(STDOUT_FILENO);
	if (dp == -1)
		return 1;
	pipe_fd[0] = fd;
	pipe_fd[1] = op;
	r = read(pipe_fd[0],buff1,BUFFER_SIZE);
	if(r == -1)
		perror("Error");
	while(buff1[i])
	{
		write(pipe_fd[1],&buff1[i],1);
		i++;
	}
	free(buff1);
	}
	return 0;
}
//function no use : close , unlink,waitpid
//function that i use : strcat strcpy strchr
