#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include "commonheaders.h"

int main(int argc, char* argv[]) {
    char path[MAX_PATH_LENGTH];
    
    int fd, fd1, fd2;

    struct stat info;
    getServerPath("",argv[1],path);
    // fd = open(path, O_RDWR | O_APPEND);

    // if(fd<0) {
    //     printf("Error\n");
    // }
    printf("filepath : %s\n", path);
    lstat(path, &info);

    printf("Last Mod: %ld\n", info.st_mtime);

    // creat(path, O_RDWR | O_APPEND |O_CREAT);
    fd = open(path, O_RDWR | O_APPEND);

    if(fd<0) {
        printf("Error\n");
    }

    // char buf[1900];

    // read(fd, buf, 1900);

    // printf("READ, NOW WRITE .. CHECK IF FLUSHING\n");

    write(fd, "hello world", strlen("hello world")+1);

    close(fd);
    printf("%s", buf);


//     fd1 = open("/tmp/fuse/19_file", O_RDWR | O_APPEND | O_CREAT, S_IRWXU);

//     printf("New File: %d\n", fd);
//     write(fd, "New 19 file", strlen("New 19 file"));

//     fd2 = open("/tmp/fuse/19_file", O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
//     close(fd1);
//     printf("Open File: %d\n", fd2);

//     int pid = fork();
// dup2(fd2,0);
//     //    close(fd2);   
//     if(pid==0) {
//         int rc;
//         printf("Closing now %d\n", fd2);
//             rc = write(0, "new", strlen("new"));
//     if(rc<0)
//         printf("Write Error\n");
//     } else {

//         wait(NULL);
    
/*
    int rc;
    rc = read(fd2, buf, 1000);
   
    if(rc<0)
        printf("Read Error\n");
    rc = write(fd2, "new", strlen("new")); 

    printf("Closing in parent\n");
    close(fd2);
*/
    // }

    return 0;
}
