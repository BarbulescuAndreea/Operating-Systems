/* SPDX-License-Identifier: BSD-3-Clause */
#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define S_IFDIR 0040000

int truncate(const char *path, off_t length)
{
	/* TODO: Implement lseek(). */
	struct stat buffer;
	int state;
    state = stat(path, &buffer);
	if(state == -1){
		errno = ENOENT;
		return -1;
	}
	if((buffer.st_mode & S_IWUSR) == 0){ // i can t truncate a read_only file
		errno = EACCES;
		return -1;
	}
	if(buffer.st_mode & S_IFDIR){ // is a directory, so i can t truncate a directory
		errno = EISDIR;
		return -1;
	}
	if(length < 0){
		errno = EINVAL;
		return -1;
	}
	int result = syscall(__NR_truncate, path, length);
	if(result == -1){
		errno = result;
	}
	return 0;
}
