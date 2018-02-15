
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef __linux__
static void child_process(int error)
{
    if (error == 0) {
        printf("UID is now %d\n", geteuid());
        printf("PID is now %d\n", getpid());
        chdir("/home/jim");
        execlp("ghci", "ghci", NULL);
    }
}

static pid_t fork_child()
{
    pid_t pid;
    uid_t original = getuid();
    int *status, error;

    if ((pid = fork()) == 0) {
        error = setuid(1001); // set user 1001 (nothing can do in the environment)
        child_process(error);
    } else {
        // wait on child
        wait(status);
        //error = setuid(original); // set user default
    }
    assert(pid != 0); // child_process never returns
    return pid;
}

int main(void)
{
    fork_child();
}

#endif
