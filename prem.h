
#include <stdlib.h>
#include <stdio.h>

#define HELP ("Useage: prem [OPTION]... [COMMAND]...\n"\
        "Run the command with no privilege.\n\n"\
        " -u, --uid=<value> run the program with UID <value>. Default, <value> is 1000\n"\
        " -v, --version     print version\n"\
        " -h, --help        print this help message\n"\
        "\nCopyright clockvoid\n")
#define VERSION ("Privilege remover version, 0.1.0"\
        "\nCopyright clockvoid\n")

pid_t fork_child(int uid, char *command);
