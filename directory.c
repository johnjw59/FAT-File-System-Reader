/*
 * directory.c
 *
 * Functions used to deal with directory entries.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "directory.h"
#include "fatfs.h"
#include "fat12.h"
#include "fat32.h"

/*
 * Print the contents of a directory, recursing down each found directory.
 */
int print_directory(const filesystem_info *fsinfo, unsigned int dir_index, char *path) {
  unsigned char *disk = fsinfo->diskStart;
  dir_index = dir_index * fsinfo->sector_size;

  // figure out how long this directory could be.
  int dir_end;
  if (dir_index >= (fsinfo->rootdir_offset * fsinfo->sector_size)) {
    dir_end = dir_index + (fsinfo->cluster_size * fsinfo->sector_size) - 32;
  }
  else {
    dir_end = dir_index + (fsinfo->rootdir_size * 32) - 32;
  }

  char filename[9] = "";
  char ext[4] = "";
  uint32_t cluster;
  int size;
  char subpath[66] = "";
  int flag = 0;
  char attributes;
  char clust_help[4];
  int directory;

  // Keep looking at entries in directory until you hit zeroes or are at the end of the directory.
  while ((disk[dir_index]) && (dir_index <= dir_end)) {
    // copy the values for the filename, extension and first cluster from the disk.
    memcpy(&filename, &disk[dir_index], 8);
    trim_spaces(filename, 9);
    memcpy(&ext, &disk[dir_index + 8], 3);
    memcpy(&attributes, &disk[dir_index + 11], 1);
    directory = attributes & 0x10;
    // if it's a FAT32 system, the cluster is made of 4 bytes stored in two locations.
    if (fsinfo->fs_type == 32) {
      memcpy(&clust_help[0], &disk[dir_index + 26], 2);
      memcpy(&clust_help[2], &disk[dir_index + 20], 2);
      cluster = *(uint32_t*)&clust_help[0];
      // The four top bits of each entry are reserved for other purposes and should be masked off.
      cluster = cluster & 0x0fffffff;
    }
    else {
      memcpy(&cluster, &disk[dir_index + 26], 2);
    }

    // don't print deleted files, volume labels or VFAT names.
    if ((filename[0] != 0xffffffe5) && (attributes != 0x0f) && !(attributes & 0x08)) {
      printf("Filename: %s%s", path, filename);

      // if it the directory bit is set, its a directory
      if (directory) {
        printf("\nThis file is a directory.\n");
      }
      // otherwise it's a file and has a size.
      else {
        // files don't have to have extensions.
        if (ext[0] == ' ') {
          printf("\n");
        }
        else {
          printf(".%s\n", ext);
        }
        memcpy(&size, &disk[dir_index + 28], 4);
        printf("Size: %d\n", size);
      }

      printf("Clusters: %d", cluster);
      // follow the cluster chain!
      // flag tells us if there is more than one cluster to this file/directory.
      if (fsinfo->fs_type == 12) {
        flag = print_cluster_chain12(fsinfo, cluster);
      }
      else {
        flag = print_cluster_chain32(fsinfo, cluster);
      }
      printf("\n\n");

      // if its an actual directory (not ./ or ../), recurse.
      if (directory && (filename[0] != '.')) {
        strcpy(subpath, path);
        build_subpath(&filename[0], subpath);
        print_directory(fsinfo, ((cluster * fsinfo->cluster_size) + fsinfo->cluster_offset), subpath);
        // if this directory is made of more than one cluster, recurse down those as well.
        if (flag) {
          if (fsinfo->fs_type == 12) {
            cluster = get_next_cluster12(disk, (fsinfo->fat_offset * fsinfo->sector_size), cluster);
            while(cluster) {
              print_directory(fsinfo, ((cluster * fsinfo->cluster_size) + fsinfo->cluster_offset), subpath);
              cluster = get_next_cluster12(disk, (fsinfo->fat_offset * fsinfo->sector_size), cluster);
            }
          }
          else {
            cluster = get_next_cluster32(disk, (fsinfo->fat_offset * fsinfo->sector_size), cluster);
            while(cluster) {
              print_directory(fsinfo, ((cluster * fsinfo->cluster_size) + fsinfo->cluster_offset), subpath);
              cluster = get_next_cluster32(disk, (fsinfo->fat_offset * fsinfo->sector_size), cluster);
            }
          }
        }
      }
    }
    dir_index += 32;
  }
}

/*
 * Remove trailing white spaces from file names.
 */
int trim_spaces(char *str, int len) {
  len --; // we assume the string is null terminated.
  // go through string until you hit something that isn't a space, or you reach the end of the string.
  while ((str[len - 1] == ' ') && (len > 0)) {
    str[len - 1] = '\0';
    len --;
  }
}

/*
 * Build a string from a directories path string, and the name of the directory.
 */
int build_subpath(char *dir, char *path) {
  char slash[2] = {'\\', '\0'};
  strcat(path, dir);
  strcat(path, &slash[0]);
}
