CC = gcc
CFLAGS = -g 

SRC = fatinfo.c direntry.c directory.c blockio.c wordio.c fatfs.c fat12.c fat32.c 
OBJ = $(SRC:.c=.o)

fatinfo: $(OBJ)

depend: $(SRC)
	makedepend $(SRC)

clean:
	/bin/rm -f $(OBJ) fatinfo *~

# DO NOT DELETE

#fatinfo.o: /usr/include/stdio.h /usr/include/features.h
#fatinfo.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
#fatinfo.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
#fatinfo.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
#fatinfo.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
#fatinfo.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
#fatinfo.o: fatfs.h /usr/include/stdlib.h /usr/include/bits/waitflags.h
#fatinfo.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
#fatinfo.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
#fatinfo.o: /usr/include/bits/byteswap-16.h /usr/include/sys/types.h
#fatinfo.o: /usr/include/time.h /usr/include/sys/select.h
#fatinfo.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
#fatinfo.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
#fatinfo.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
#fatinfo.o: /usr/include/bits/stdlib-float.h fat12.h fat32.h wordio.h
#fatinfo.o: blockio.h directory.h direntry.h
#direntry.o: /usr/include/stdio.h /usr/include/features.h
#direntry.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
#direntry.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
#direntry.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
#direntry.o: /usr/include/libio.h /usr/include/_G_config.h
#direntry.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
#direntry.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
#direntry.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
#direntry.o: /usr/include/endian.h /usr/include/bits/endian.h
#direntry.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
#direntry.o: /usr/include/sys/types.h /usr/include/time.h
#direntry.o: /usr/include/sys/select.h /usr/include/bits/select.h
#direntry.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
#direntry.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
#direntry.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
#direntry.o: /usr/include/string.h /usr/include/xlocale.h direntry.h
#directory.o: /usr/include/stdio.h /usr/include/features.h
#directory.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
#directory.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
#directory.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
#directory.o: /usr/include/libio.h /usr/include/_G_config.h
#directory.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
#directory.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
#directory.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
#directory.o: /usr/include/endian.h /usr/include/bits/endian.h
#directory.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
#directory.o: /usr/include/sys/types.h /usr/include/time.h
#directory.o: /usr/include/sys/select.h /usr/include/bits/select.h
#directory.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
#directory.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
#directory.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h
#directory.o: /usr/include/string.h /usr/include/xlocale.h directory.h
#directory.o: direntry.h
#blockio.o: /usr/include/sys/types.h /usr/include/features.h
#blockio.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
#blockio.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
#blockio.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
#blockio.o: /usr/include/time.h /usr/include/endian.h
#blockio.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
#blockio.o: /usr/include/bits/byteswap-16.h /usr/include/sys/select.h
#blockio.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
#blockio.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
#blockio.o: /usr/include/bits/pthreadtypes.h /usr/include/unistd.h
#blockio.o: /usr/include/bits/posix_opt.h /usr/include/bits/environments.h
#blockio.o: /usr/include/bits/confname.h /usr/include/getopt.h
#blockio.o: /usr/include/string.h /usr/include/xlocale.h blockio.h
#blockio.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
#blockio.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
#blockio.o: /usr/include/bits/stdlib-float.h
#wordio.o: wordio.h
#fatfs.o: /usr/include/fcntl.h /usr/include/features.h
#fatfs.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
#fatfs.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
#fatfs.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
#fatfs.o: /usr/include/bits/fcntl.h /usr/include/bits/fcntl-linux.h
#fatfs.o: /usr/include/time.h /usr/include/bits/stat.h /usr/include/stdio.h
#fatfs.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
#fatfs.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
#fatfs.o: /usr/include/sys/stat.h /usr/include/sys/types.h
#fatfs.o: /usr/include/endian.h /usr/include/bits/endian.h
#fatfs.o: /usr/include/bits/byteswap.h /usr/include/bits/byteswap-16.h
#fatfs.o: /usr/include/sys/select.h /usr/include/bits/select.h
#fatfs.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
#fatfs.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
#fatfs.o: /usr/include/sys/mman.h /usr/include/bits/mman.h
#fatfs.o: /usr/include/bits/mman-linux.h fatfs.h /usr/include/stdlib.h
#fatfs.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
#fatfs.o: /usr/include/alloca.h /usr/include/bits/stdlib-float.h fat12.h
#fatfs.o: fat32.h
#fat12.o: /usr/include/stdio.h /usr/include/features.h
#fat12.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
#fat12.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
#fat12.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
#fat12.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
#fat12.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
#fat12.o: fat12.h
#fat32.o: /usr/include/stdio.h /usr/include/features.h
#fat32.o: /usr/include/stdc-predef.h /usr/include/sys/cdefs.h
#fat32.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
#fat32.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
#fat32.o: /usr/include/libio.h /usr/include/_G_config.h /usr/include/wchar.h
#fat32.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
#fat32.o: fat32.h fat12.h
