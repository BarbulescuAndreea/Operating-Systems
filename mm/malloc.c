/* SPDX-License-Identifier: BSD-3-Clause */

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <internal/syscall.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void *malloc(size_t size)
{
	void* mmap_res = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if(mmap_res != MAP_FAILED){
		return mmap_res;
	}else{
		return NULL;
	}
}

void *calloc(size_t nmemb, size_t size)
{
	void* addr = malloc(size * nmemb);
	if(addr != NULL){
		memset(addr, 0, size * nmemb);
		return addr;
	}
	return NULL;
}

void free(void *ptr)
{
	if (ptr != NULL) {
		munmap(ptr, sizeof(ptr));
	}
	return NULL;
}

void *realloc(void *ptr, size_t size)
{
	if(ptr == NULL)
        return malloc(size);
    else if (size == 0) {
        free(ptr);
        return NULL;
    }else{
        void *my_NEW_ptr = malloc(size);

        if(my_NEW_ptr == NULL)
            return NULL;

        size_t ex_size = sizeof(my_NEW_ptr);
        if(ex_size > size)
            ex_size = size;

        memcpy(my_NEW_ptr, ptr, ex_size);
        free(ptr);
        return my_NEW_ptr;
    }
	return NULL;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    size_t new_size = nmemb * size;
    return realloc(ptr, new_size);
}
