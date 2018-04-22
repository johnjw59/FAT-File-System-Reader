/*
 * fat12.h
 *
 * Functions used to deal with the file allocation table.
 */
#ifndef FAT12_H
#define FAT12_H

#include "fatfs.h"

/*
 * Follow and print the chain of clusters from the FAT.
 */
int print_cluster_chain12(const filesystem_info *fsinfo, uint32_t cluster);

/*
 * Return the next cluster in the chain of the provided cluster from the FAT.
 * If the cluster you find is out of bounds, return 0
 */
uint32_t get_next_cluster12(unsigned char *disk, int fat_offset, uint32_t cluster);

#endif
