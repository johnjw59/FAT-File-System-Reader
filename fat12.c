/*
 * fat12.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fat12.h"
#include "fatfs.h"

/*
 * Follow and print the chain of clusters from the FAT.
 * 
 * If it's a continuous chain, print the starting cluster and ending cluster.
 * Otherwise print each cluster.
 * Returns 1 if there is more than 1 cluster in the chain.
 */
int print_cluster_chain12(const filesystem_info *fsinfo, uint32_t cluster) {
  unsigned char *disk = fsinfo->diskStart;
  uint32_t temp_clust1 = cluster;
  uint32_t temp_clust2 = get_next_cluster12(disk, (fsinfo->fat_offset * fsinfo->sector_size), cluster);
  int flag = 0;
  // keep going as long as we're getting valid clusters
  while (temp_clust2) {
    flag = 1;
    // if it's continuous chain, only print the first and last clusters
    if (temp_clust2 == (temp_clust1 +1)) {
      printf("-");
      while (temp_clust2 == (temp_clust1 +1)) {
        temp_clust1 = temp_clust2;
        temp_clust2 = get_next_cluster12(disk, (fsinfo->fat_offset * fsinfo->sector_size), temp_clust1);
      }
      printf("%d", temp_clust1);
    }
    if (temp_clust2) {
      printf(",%d", temp_clust2);
      temp_clust1 = temp_clust2;
      temp_clust2 = get_next_cluster12(disk, (fsinfo->fat_offset * fsinfo->sector_size), temp_clust1);
    }
  }
  return flag;
}

/*
 * Return the next cluster in the chain of the provided cluster from the FAT.
 * If the cluster you find is out of bounds, return 0
 *
 * For FAT12, two entries are stored in 3 bytes. if the bytes are uv, wx, yz then the entries are xuv and yzw
 */
uint32_t get_next_cluster12(unsigned char *disk, int fat_offset, uint32_t cluster) {
  unsigned char fat_entry[2];
  uint32_t new_clust;
  // If the cluster number is odd, we're getting the last half of the three bytes.
  if (cluster % 2) {
    memcpy(&fat_entry[0], &disk[fat_offset + ((cluster/2)*3)+1], 1);
    memcpy(&fat_entry[1], &disk[fat_offset + ((cluster/2)*3)+2], 1);
    memcpy(&new_clust, &fat_entry[0], 2);
    new_clust = new_clust>>4; 
  }
  // If it's even we're getting the first half.
  else {
    memcpy(&fat_entry[0], &disk[fat_offset + ((cluster/2)*3)], 1);
    memcpy(&fat_entry[1], &disk[fat_offset + ((cluster/2)*3)+1], 1);
    fat_entry[1] = fat_entry[1]&0x0f;
    memcpy(&new_clust, &fat_entry[0], 2);
  }
  // for FAT12, the valid entries are between 0x2 and0xfef.
  if ((new_clust > 2) && (new_clust < 4079)) {
    return new_clust;
  }
  return 0;
}


