
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define HELP ("Useage: prem [OPTION]... [COMMAND]...\n"\
        "Run the command with no privilege.\n\n"\
        " -u, --uid=<value> run the program with UID <value>. Default, <value> is 1000\n"\
        " -v, --version     print version\n"\
        " -h, --help        print this help message\n"\
        "\nCopyright clockvoid\n")
#define VERSION ("Privilege remover versin, 0.1.0"\
        "\nCopyright clockvoid\n")

pid_t fork_child(int uid, char *command);
