#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *environ;
    int i;
    environ = getenv("PATH");
    printf("%s\n", environ);
    /*for (i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }*/
    return 0;
}
