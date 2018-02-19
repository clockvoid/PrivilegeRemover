
#include "prem.h"

#ifdef __linux__

#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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

pid_t fork_child(int uid, char *command)
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

#endif
