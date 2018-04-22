/*
 * fat32.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fat32.h"
#include "fatfs.h"

/*
 * Follow and print the chain of clusters from the FAT.
 * 
 * If it's a continuous chain, print the starting cluster and ending cluster.
 * Otherwise print each cluster.
 * Returns 1 if there is more than 1 cluster in the chain.
 */
int print_cluster_chain32(const filesystem_info *fsinfo, uint32_t cluster) {
  unsigned char *disk = fsinfo->diskStart;
  uint32_t temp_clust1 = cluster;
  uint32_t temp_clust2 = get_next_cluster32(disk, (fsinfo->fat_offset * fsinfo->sector_size), cluster);
  int flag = 0;
  // keep going as long as we're getting valid clusters
  while (temp_clust2) {
    flag = 1;
    // if it's continuous chain, only print the first and last clusters
    if (temp_clust2 == (temp_clust1 +1)) {
      printf("-");
      while (temp_clust2 == (temp_clust1 +1)) {
        temp_clust1 = temp_clust2;
        temp_clust2 = get_next_cluster32(disk, (fsinfo->fat_offset * fsinfo->sector_size), temp_clust1);
      }
      printf("%d", temp_clust1);
    }
    if (temp_clust2) {
      printf(",%d", temp_clust2);
      temp_clust1 = temp_clust2;
      temp_clust2 = get_next_cluster32(disk, (fsinfo->fat_offset * fsinfo->sector_size), temp_clust1);
    }
  }
  return flag;
}

/*
 * Return the next cluster in the chain of the provided cluster from the FAT.
 * If the cluster you find is out of bounds, return 0
 */
uint32_t get_next_cluster32(unsigned char *disk, int fat_offset, uint32_t cluster) {
  uint32_t new_clust;
  memcpy(&new_clust, &disk[fat_offset + (cluster * 4)], 4);
  // The four top bits of each entry are reserved for other purposes and should be masked off.
  new_clust = new_clust & 0x0fffffff;
  
  // for FAT32, the valid entries are between 0x2 and0xfffffef.
  if ((new_clust > 2) && (new_clust < 268435439)) {
    return new_clust;
  }
  return 0;
}
