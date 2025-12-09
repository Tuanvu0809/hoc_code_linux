#ifndef FILESTAS_H
#define FILESTAS_H

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void file_path(char *path);
void file_type(  struct stat *file);
void file_bytes(struct stat *file);
void file_times(struct stat *file);

#endif