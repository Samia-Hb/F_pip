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
void execute_commands(char *cmd1, char *cmd2, char *infile, char *outfile,char **envp) {
    int pipefd[2];
    int i = 0;
    char *command_path;
    int arr_count;
    char **new_arr;
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(1);
    }
    int pid1 = fork();
    if (pid1 == -1)
    {
        perror("fork");
        exit(1);
    } else if (pid1 == 0) {
        i = 0;
        arr_count = 0;
        // Child process 1 (cmd1)
        close(pipefd[0]); // Close read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the pipe
        close(pipefd[1]); // Close the original write end of the pipe
        int infile_fd = open(infile, O_RDONLY);
        if (infile_fd == -1){
            perror("open");
            exit(1);
        }
        dup2(infile_fd, STDIN_FILENO); // Redirect stdin to the input file
        close(infile_fd); // Close the original file descriptor
        //to_get_path
            char **arr = ft_split(cmd1,' ');
            int H = 0 ;
            while (arr[H] != NULL)
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
            while (i < arr_count)
            {
                new_arr[i] = arr[i];
                i++;
            }
            new_arr[arr_count] = NULL;
            command_path = get_executable(new_arr[0], find_path(envp));
        //
        execve(command_path,new_arr,envp);
        perror("execve");
        exit(1);
    } else {
        int pid2 = fork();
        if (pid2 == -1) {
            perror("fork");
            exit(1);
        } else if (pid2 == 0) {
            i = 0;
            arr_count = 0;
            // Child process 2 (cmd2)
            close(pipefd[1]); // Close write end of the pipe
            dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the pipe
            close(pipefd[0]); // Close the original read end of the pipe

            int outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
            if (outfile_fd == -1) {
                perror("open");
                exit(1);
            }
            dup2(outfile_fd, STDOUT_FILENO); // Redirect stdout to the output file
            close(outfile_fd); // Close the original file descriptor
            //to_get_path
            char **arr = ft_split(cmd2,' ');
            int H = 0 ;
            while (arr[H] != NULL)
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
            while (i < arr_count)
            {
                new_arr[i] = arr[i];
                i++;
            }
            new_arr[arr_count] = NULL;
            command_path = get_executable(new_arr[0], find_path(envp));
            //
            execve(command_path,new_arr,envp);
            perror("execve");
            exit(1);
        } else {
            // Parent process
            close(pipefd[0]); // Close both ends of the pipe
            close(pipefd[1]);
            
            // Wait for both child processes to finish
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
        }
    }
}

int main(int argc, char **argv,char **envp) {
    if (argc == 5) {
        execute_commands(argv[2], argv[3], argv[1], argv[4],envp);
    } else {
        fprintf(stderr, "Usage: %s <infile> <cmd1> <cmd2> <outfile>\n", argv[0]);
        return 1;
    }

    return 0;
}