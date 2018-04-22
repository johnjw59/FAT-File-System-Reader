/*
 * fatfs.c
 *
 * Basic operations on a FAT filesystem.
 */

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "fatfs.h"

/**
 * How to use this program.
 */
#define USAGE "Usage: %s file-system-file\n"

/*
 * Default size of one sector.
 */
#define DEFAULT_SECTOR_SIZE 512

/*
 * Size of one directory entry.
 */
#define DIR_ENTRY_SIZE 32

/*
 * Function to open the file system and map it into memory. 
 */
void * open_filesystem(int argc, char *argv[])
{
    char *filename;
    void *memory; 
    int fd;
    struct stat statBuff;

    if (argc == 2)
    {
	filename = argv[1];
    }
    else
    {
	fprintf(stderr, USAGE, argv[0]);
	exit(1);
    }

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
      char buff[256];
      snprintf(buff, 256, "Could not open %s", filename);
      perror(buff);
      exit(1);
    }
    
    if (fstat(fd, &statBuff)) {
	perror("Stat failed");
	exit(1);
    }
    memory = mmap(0, statBuff.st_size, PROT_READ,  MAP_FILE | MAP_PRIVATE, fd, 0);
    if (memory == NULL) {
      perror("MMAP of file failed");
      exit(1);
    }
    return memory;
}

/*
 * This function sets up information about a FAT filesystem that will be used to read from
 * that file system.
 */
filesystem_info *initialize_filesystem_info(void *diskStart)
{
    filesystem_info *fsinfo = (filesystem_info *) malloc(sizeof(filesystem_info));
    fsinfo->diskStart = diskStart;

    unsigned char *charDisk = diskStart;
    
    // for all common settings, set the values.
    fsinfo->sector_size = *(uint16_t*)&charDisk[11];
    fsinfo->cluster_size = *(uint8_t*)&charDisk[13];
    fsinfo->reserved_sectors = *(uint16_t*)&charDisk[14];
    fsinfo->rootdir_size = *(uint16_t*)&charDisk[17];
    fsinfo->hidden_sectors = *(uint16_t*)&charDisk[28];
    fsinfo->fat_offset = (unsigned int)fsinfo->reserved_sectors;
    int temp = (fsinfo->rootdir_size * 32)%fsinfo->sector_size;
    fsinfo->sectors_for_root = (unsigned int)(fsinfo->rootdir_size * 32)/fsinfo->sector_size + temp;

    // if rootdir_size is set, it's at FAT12 system.
    if (fsinfo->rootdir_size) {
        fsinfo->fs_type = 12;

        fsinfo->sectors_per_fat = (unsigned int)(*(uint16_t*)&charDisk[22]);
        fsinfo->rootdir_offset = (unsigned int)(fsinfo->fat_offset + (*(uint8_t*)&charDisk[16] * fsinfo->sectors_per_fat));
        fsinfo->cluster_offset = (unsigned int)(fsinfo->sectors_for_root + fsinfo->rootdir_offset - (2 * fsinfo->cluster_size));
    }
    // otherwise it's a FAT32 system.
    else {
        fsinfo->fs_type = 32;

        fsinfo->sectors_per_fat = (unsigned int)(*(uint32_t*)&charDisk[36]);
        fsinfo->rootdir_offset = (unsigned int)(fsinfo->fat_offset + (*(uint8_t*)&charDisk[16] * fsinfo->sectors_per_fat) + (*(uint32_t*)&charDisk[44] * fsinfo->cluster_size) - (2 * fsinfo->cluster_size));
        fsinfo->cluster_offset = (unsigned int)(fsinfo->fat_offset + (*(uint8_t*)&charDisk[16] * fsinfo->sectors_per_fat) - (2 * fsinfo->cluster_size));
    }

    return fsinfo;
}

