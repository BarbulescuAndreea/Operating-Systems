/* SPDX-License-Identifier: BSD-3-Clause */
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{  
    // if(length < 0){
    //     return MAP_FAILED;
    // }
    struct stat st;
    int result = syscall(__NR_fstat, fd, &st);
    // if( (result == -1)  || (!(st.st_mode & S_IWUSR)) || (st.st_mode & S_IFDIR) ){
    //     errno = EBADF;
    //     return -1;
    // }
    if((result != 0) && (fd != -1)){    
        errno = EBADF;
        return MAP_FAILED;
    }

    if(!((flags & MAP_PRIVATE ) == MAP_PRIVATE) && !((flags & MAP_SHARED) == MAP_SHARED)){
        //puts("a");
        errno = EINVAL;
        return MAP_FAILED;
    }
	void *mem = syscall(__NR_mmap, addr, length, prot, flags, fd, offset);
    //close(fd);
    if (mem == (void*) -1){
        return MAP_FAILED;
    }

    return mem;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	void *new = syscall(__NR_mremap, old_address, old_size, new_size, flags);

    if(new == (void*) -1)
        return MAP_FAILED;

    return new;
}

int munmap(void *addr, size_t length)
{
	int buf = syscall(__NR_munmap, addr, length);
    if(buf == -1)
        return -errno;

    return buf;
}
