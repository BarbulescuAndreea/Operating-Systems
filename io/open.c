/* SPDX-License-Identifier: BSD-3-Clause */
#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#define S_IFDIR 0040000

// stat - sys call which gives informations about a file - usefull to check if this exits
int check_file(const char *filename) {
    struct stat buffer;
    return stat(filename, &buffer) == 0;
}

int open(const char *filename, int flags, ...)
{
	int mode_for_file = -1;
    if(flags & O_CREAT){
		if(check_file(filename)){ // the file that i want to open doesn t exist
			errno = EEXIST;
			return -1;
		}
        va_list arg_list;
        va_start(arg_list, flags);
        mode_for_file = va_arg(arg_list, mode_t);
        va_end(arg_list);
    }
	if((flags & O_WRONLY) || (flags & O_DIRECTORY)){
        mode_for_file = 0; // Ignore mode_for_file if either flag is set
    }

	if(flags == O_RDONLY){ //if i want to open in READONLY
		if(!check_file(filename)){ // the file that i want to open doesn t exist
			errno = ENOENT;
			return -1;
		}
	}
	if(flags == O_WRONLY){ // if i want to open in WRITEONLY
		struct stat buffer;
        stat(filename, &buffer);
		if(buffer.st_mode & S_IFDIR){ // if i want to write, the filename must be a file, not a directory
			errno = EISDIR; // error says that i have a directory, instead of a file
			return -1;
		}
		if(!(buffer.st_mode & S_IWUSR)){
			errno = EACCES;
			return -1;
		}
	}

	if(flags == O_DIRECTORY){ // if i want to open a DIRECTORY
		struct stat buffer;
		int ret = stat(filename, &buffer);
		if(ret == 0 && !(buffer.st_mode & S_IFDIR)) { // check if the filename is a directory
            errno = ENOTDIR; // if it is not a directory, error
            return -1;
        }
	}

	int res = syscall(__NR_open, filename, flags, mode_for_file);
	if(res == -1){
		errno = errno;
		return -1;
	}
	// unsigned long r = res;

	// if(fd < 0 || r > 4096UL){
	// 	errno = -r;
	// 	return -1;
	// }
	return res;
}
