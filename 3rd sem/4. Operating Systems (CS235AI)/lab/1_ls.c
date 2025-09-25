// ls -l
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main()
{
    DIR* d = opendir("."); // Moved inside main
    struct dirent* de;
    struct stat buf;
    struct passwd* p;
    struct group* g;
    struct tm* t;
    char permissions[] = "rwxrwxrwx", timeStr[26]; // Renamed time to timeStr
    int i, j;

    if (d == NULL) {
        perror("opendir");
        return 1;
    }

    readdir(d);
    readdir(d);

    while ((de = readdir(d)) != NULL) {
        stat(de->d_name, &buf);
        // d-cblps
        if (S_ISDIR(buf.st_mode))
            putchar('d');
        else if (S_ISREG(buf.st_mode))
            putchar('-');
        else if (S_ISCHR(buf.st_mode))
            putchar('c');
        else if (S_ISBLK(buf.st_mode))
            putchar('b');
        else if (S_ISLNK(buf.st_mode))
            putchar('l');
        else if (S_ISFIFO(buf.st_mode))
            putchar('p');
        else if (S_ISSOCK(buf.st_mode))
            putchar('s');
        
        for (i = 0, j = 1 << 8; i < 9; i++, j >>= 1)
            putchar((buf.st_mode & j) ? permissions[i] : '-');
        
        p = getpwuid(buf.st_uid);
        g = getgrgid(buf.st_gid);
        if (p && g)
            printf(" %s %s ", p->pw_name, g->gr_name);
        else
            printf(" %d %d ", buf.st_uid, buf.st_gid);

        t = localtime(&buf.st_mtime);
        strftime(timeStr, 26, "%b %d %H:%M", t); // Updated variable name
        printf("%s ", timeStr); // Updated variable name
        printf("%s\n",de->d_name);
    }
    closedir(d);
}