#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>

int main(int argc, char* argv[])
{
    struct flock fvar;
    int fd;
    char buffer[100];

    if (argc != 2) {
        perror("syntax");
        return 1;
    }
    if ((fd = open(argv[1], O_RDWR)) == -1) {
        perror("open");
        return 2;
    }

    printf("Press enter to set lock");
    getchar();
    memset(&fvar, 0, sizeof(fvar));
    fvar.l_type = F_WRLCK;
    fvar.l_whence = SEEK_END;
    fvar.l_start = SEEK_END - 100;
    fvar.l_len = 100;
    printf("Setting lock...\n");
    if (fcntl(fd, F_SETLK, &fvar) == -1) {
        fcntl(fd, F_GETLK, &fvar);
        printf("Lock already set by process with pid: %d\n", fvar.l_pid);
        return 1;
    }
    printf("Locked.\n");

    if (lseek(fd, SEEK_END - 50, SEEK_END) == -1) {
        perror("lseek");
        return 3;
    }
    if (read(fd, &buffer, sizeof(buffer)) == -1) {
        perror("read");
        return 4;
    }
    printf("Text: %s\n", buffer);

    printf("Press enter to unlock");
    getchar();
    fvar.l_type = F_UNLCK;
    fvar.l_start = 0;
    fvar.l_whence = 0;
    fvar.l_len = 0;
    printf("Unlocking...");
    if (fcntl(fd, F_UNLCK, &fvar) == -1) {
        perror("fcntl");
        return 5;
    }
    printf("Unlocked");
}