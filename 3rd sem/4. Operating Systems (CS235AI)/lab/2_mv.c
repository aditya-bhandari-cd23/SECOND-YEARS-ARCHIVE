// mv
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
    if (argc != 3) {
        perror("syntax");
        return 1;
    }
    if (link(argv[1], argv[2]) == -1) {
        perror("link");
        return 2;
    }
    if (unlink(argv[1]) == -1) {
        perror("unlink");
        return 3;
    }
}