/*
 * fat32.h
 *
 * Functions used to deal with the file allocation table.
 */
#ifndef FAT32_H
#define FAT32_H

#include "fatfs.h"
#include "fatfs.h"

/*
 * Follow and print the chain of clusters from the FAT.
 */
int print_cluster_chain32(const filesystem_info *fsinfo, uint32_t cluster);

/*
 * Return the next cluster in the chain of the provided cluster from the FAT.
 */
uint32_t get_next_cluster32(unsigned char *disk, int fat_offset, uint32_t cluster);

#endif
