/* SPDX-License-Identifier: BSD-3-Clause */

#include <unistd.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>
#define MAX_OPEN_FILES 1024

int close(int fd)
{
	int result = syscall(__NR_close, fd);
    if(result == -1){
        errno = errno;
        return -1;
    }
    return 0;  // return success
}
