/*
 * blockio.c
 *
 * Low-level functions used to perform  i/o operations on blocks (sectors). All of them
 * take as parameter an object  that contains information about the file that
 * is being accessed, the size of a sector, etc.
 */
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include "blockio.h"

