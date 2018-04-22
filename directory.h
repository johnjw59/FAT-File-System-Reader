/*
 * directory.h
 *
 * Functions used to deal with directory entries.
 */

#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "direntry.h"
#include "fatfs.h"

/*
 * Print the contents of a directory, recursing down each found directory.
 */ 
int print_directory(const filesystem_info *fsinfo, unsigned int dir_index, char* path);

/*
 * Remove trailing white spaces from file names.
 */
int trim_spaces(char *str, int len);

/*
 * Build a string from a directories parent string, and the name of the directory.
 */
int build_subpath(char *dir, char *path);

#endif
