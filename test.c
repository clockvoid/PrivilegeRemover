#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#ifdef __linux__

static void child_process(int error)
{
    if (error == 0) {
        printf("UID is now %d\n", geteuid());
        printf("PID is now %d\n", getpid());
        chdir("/home/jim");
        char *argv[2];
        char *environ[1];
        argv[0] = "/home/jim/ghc/bin/ghci";
        argv[1] = NULL;
        environ[0] = "";
        execve(argv[0], (char **)argv, (char **)environ);
    }
}

static pid_t fork_child()
{
    pid_t pid;
    uid_t original = getuid();
    int status, error;

    if ((pid = fork()) == 0) {
        error = setuid(1001); // set user 1001 (nothing can do in the environment)
        child_process(error);
    } else {
        // wait on child
        wait(&status);
        error = setuid(original); // set user default
        printf("setuid is %s\n", error == 0 ? "succeeded" : "faild");
    }
    assert(pid != 0); // child_process never returns
    return pid;
}

int main(void)
{
    fork_child();
}

#endif
