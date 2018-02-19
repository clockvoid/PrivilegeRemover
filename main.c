
#include "prem.h"

#include <math.h>
#include <string.h>

static char *command, *uid;
static int uid_num;

// static using in function means like private
static void change_uid(char const* argv_i) {
    int j, k;
    uid_num = 0;
    for (j = 0; j < strlen(argv_i); j++) {
        if (argv_i[j] == '=') {
            strncpy(uid, argv_i + j + 1, 255);
            for (k = 0; k < strlen(uid); k++) {
                uid_num += (int)((uid[k] - '0') * pow(10, strlen(uid) - 1 - k));
            }
            break;
        }
    }
    if (j == strlen(argv_i)) {
        printf("Invalid input: You must input UID value\n");
    }
}

static void analize_args(char const* argv_i) {
    switch (*(argv_i + 1)) {
        case 'h':
            printf(HELP);
            break;
        case 'v':
            printf(VERSION);
            break;
        case 'u':
            change_uid(argv_i);
            break;
        case '-':
            analize_args(argv_i + 1);
            break;
        default:
            printf("Invalid option.\n");
            printf(HELP);
            break;
    }
}

int main(int argc, char const* argv[])
{
    int i, j, k;
    uid_num = 1000;
    if ((command = (char *)malloc(sizeof(char) * 256)) == NULL || (uid = (char *)malloc(sizeof(char) * 256)) == NULL) {
        printf("Memory allocation error\n");
        exit(-1);
    }
    for (i = 1; i < argc; i++) {
        if (*argv[i] == '-') {
            analize_args(argv[i]);
        } else if (i == argc - 1) {
            strncpy(command, argv[i], 255);
            fork_child(uid_num, command);
        } else {
            printf("Invalid input.\n");
            printf(HELP);
            break;
        }
    }
    free(command);
    free(uid);
    return 0;
}
