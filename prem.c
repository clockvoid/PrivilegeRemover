
#include "prem.h"

#ifdef __linux__

static void child_process(int error, char *command)
{
    if (error == 0) {
        printf("UID is now %d\n", geteuid());
        printf("PID is now %d\n", getpid());
        //chdir("/home/jim");
        char *argv[2];
        char *environ[1];
        argv[0] = command;
        argv[1] = NULL;
        environ[0] = "";
        execve(argv[0], (char **)argv, (char **)environ);
    }
}

static pid_t fork_child(int uid, char *command)
{
    pid_t pid;
    uid_t original = getuid();
    int status, error;

    if ((pid = fork()) == 0) {
        error = setuid(uid);
        child_process(error, command);
    } else {
        // wait on child
        wait(&status);
        error = setuid(original); // set user default
        printf("setuid is %s\n", error == 0 ? "succeeded" : "faild");
    }
    assert(pid != 0); // child_process never returns
    return pid;
}

int main(int argc, char *argv[])
{
    int i, j, k, uid_num = 1000;
    char *command = (char *)malloc(sizeof(char) * 256);
    char *uid = (char *)malloc(sizeof(char) * 256);
    for (i = 1; i < argc; i++) {
        if (*argv[i] == '-') {
            switch (*(argv[i] + 1)) {
                case 'h':
                    printf(HELP);
                    break;
                case 'v':
                    printf(VERSION);
                    break;
                case 'u':
                    for (j = 0; j < strlen(argv[i]); j++) {
                        if (argv[i][j] == '=') {
                            strcpy(uid, argv[i] + j + 1);
                            for (k = 0; k < strlen(uid); k++) {
                                uid_num += (int)((uid[k] - '0') * pow(10, strlen(uid) - 1 - k));
                            }
                        }
                    }
                    break;
                default:
                    printf("Invalid option.\n");
                    printf(HELP);
                    break;
            }
        } else if (i == argc - 1) {
            strcpy(command, argv[i]);
            fork_child(uid_num, command);
        } else {
            printf("Invalid input.\n");
            printf(HELP);
            break;
        }
    }
}

#endif
