// cp
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>

int input_fd, output_fd;
char buffer[8192];
ssize_t ret_in;

int main(int argc, char* argv[])
{
    if (argc != 3) {
        perror("syntax");
        return 1;
    }
    if ((input_fd = open(argv[1], O_RDONLY)) == -1) {
        perror("open");
        return 2;
    }
    if ((output_fd = open(argv[2], O_WRONLY | O_CREAT, 0644)) == -1) {
        perror("open");
        return 3;
    }
    while ((ret_in = read(input_fd, &buffer, 8192)) > 0) {
        if (write(output_fd, buffer, ret_in) != ret_in) {
            perror("write");
            close(input_fd);
            close(output_fd);
            return 4;
        }
    }
    close(input_fd);
    close(output_fd);
}