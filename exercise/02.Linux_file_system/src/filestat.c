#include <stdio.h>
#include "../inc/filestat.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
void file_path(char *path)
{
    printf("file path: %s\n",path);
}

void file_type( struct stat *file)
{
    
    printf("File type: ");

    switch (file->st_mode & S_IFMT) {
        case S_IFBLK:  printf("block device\n");     break;
        case S_IFCHR:  printf("character device\n"); break;
        case S_IFDIR:  printf("directory\n");        break;
        case S_IFIFO:  printf("FIFO/pipe\n");        break;
        case S_IFLNK:  printf("symlink\n");          break;
        case S_IFREG:  printf("regular file\n");     break;
        case S_IFSOCK: printf("socket\n");           break;
        default:       printf("unknown\n");          break;
    }

}

void file_bytes(struct stat *file)
{
    printf("File size: %lld bytes\n", (long long) file->st_size);
}

void file_times(struct stat *file)
{
     printf("Last status change:       %s", ctime(&file->st_ctime));
    printf("Last file access:         %s", ctime(&file->st_atime));
    printf("Last file modification:   %s", ctime(&file->st_mtime));
}