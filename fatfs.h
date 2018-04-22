/*
 * fatfs.h
 *
 * Definition of the structure used to represent a FAT filesystem.
 */

#ifndef FATFS_H
#define FATFS_H

#include <stdlib.h>
#include <stdint.h>

typedef enum {
  FAT12 = 12,
  FAT16 = 16,
  FAT32 = 32
} FS_TYPE;


typedef struct {
  //    int file_descriptor;     /* File descriptor returned by open().   */
  FS_TYPE fs_type;
  void *diskStart;               /* This is where in memory the disk starts*/
  uint16_t sector_size;          /* Size of one sector on the disk.       */
  uint8_t cluster_size;          /* Number of sectors per cluster.        */
  uint16_t rootdir_size;         /* Number of entries in root directory.  */
  
  unsigned int sectors_per_fat;  /* Number of sectors per fat.            */
  uint16_t hidden_sectors;       /* Number of hidden sectors.             */
  uint16_t reserved_sectors;     /* Number of reserved sectors.           */
  unsigned int sectors_for_root; /* Number of sectors for root directory. */

  unsigned int fat_offset;       /* First sector of the first FAT copy.   */
  unsigned int rootdir_offset;   /* First sector of the root directory.   */
  unsigned int cluster_offset;   /* Sector number of the first cluster.   */
 
  // If you need additional structure fields add them here
 
} filesystem_info;

/*
 * Function to open the file system.
 */
void* open_filesystem(int argc, char *argv[]);

/*
 * This function sets up information about a FAT filesystem that will be used to read from
 * that file system.
 */
filesystem_info *initialize_filesystem_info(void *fg);

#endif
