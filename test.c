
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_COUNT 100

#ifdef __linux__
static void child_process()
{
    /*int i;
      for (i = 1; i < MAX_COUNT; i++) {
      printf("This line is from child, value = %d\n", i);
      }*/
    //printf("Call execve\n");
    //const char *new_argv[4];
    //const char *environ = ":/bin:/usr/bin";
    int error;
    //if ((environ = getenv("PATH")) == NULL) {
    //    //printf("getenv() returns NULL\n");
    //    exit(-1);
    //}
    //printf("PATH is %s\n", *environ);
    //new_argv[0] = "/bin/sh";
    //new_argv[1] = "touch";
    //new_argv[2] = "test.txt";
    //new_argv[3] = NULL;
    //execve(new_argv[0], (char **)new_argv, (char **)environ);
    error = seteuid(1001); // set user jim (nothing can do in the environment)
    if (error == 0) {
        printf("UID is now %d\n", geteuid());
        execlp("touch", "touch", "test.txt", NULL);
    }
    error = seteuid(1000); // set user clock
    //printf("*** Child Process is done***\n");
}

static void parent_process()
{
    int i;
    for (i = 1; i < MAX_COUNT; i++) {
        printf("This line is from parent, value = %d\n", i);
    }
    printf("*** Parent Process is done***\n");
}

static pid_t fork_child()
{
    pid_t pid;

    if ((pid = fork()) == 0) {
        child_process();
    } else {
        //printf("UID is now %d\n", getuid());
    }
    assert(pid != 0); // child_process never returns
    return pid;
}

int main(void)
{
    fork_child();
    //printf("The result pid is %d\n", fork_child());
}

#endif
