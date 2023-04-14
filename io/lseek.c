/* SPDX-License-Identifier: BSD-3-Clause */

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

off_t lseek(int fd, off_t offset, int whence)
{
if(fd < 0){ // invalid fd
		errno = EBADF; //  error code that stands for "Bad file descriptor"
		return -1;
	}
	if(whence != SEEK_SET && whence != SEEK_END && whence != SEEK_CUR){
		errno = EINVAL;
		return -1;
	}
	if(offset < 0){
		errno = EINVAL;
		return -1;
	}
	off_t res = syscall(__NR_lseek, fd, offset, whence);
	if(res == -1){
		errno = errno; // set the error number returned by syscall
		return -1;
	}
	return res; // return the r
}
