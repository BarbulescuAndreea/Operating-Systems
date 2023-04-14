/* SPDX-License-Identifier: BSD-3-Clause */
#include <fcntl.h>
#include <internal/syscall.h>
#include <errno.h>
#include <internal/types.h>
#include <sys/stat.h>
#define S_IFDIR 0040000

int ftruncate(int fd, off_t length)
{
	long result = syscall(__NR_ftruncate, fd, length);

	if(result < 0){
		errno = -result;
		return -1;
	}
	return result;
}
