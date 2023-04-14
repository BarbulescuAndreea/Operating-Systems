/* SPDX-License-Identifier: BSD-3-Clause */

#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <internal/syscall.h>

int fstat(int fd, struct stat *st)
{
	unsigned long result = syscall(__NR_fstat, fd, st);

	if(result > 4096){
		errno = -result;
		return -1;
	}

	return result;
}
