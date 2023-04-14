/* SPDX-License-Identifier: BSD-3-Clause */

#include <sys/stat.h>
#include <internal/types.h>
#include <unistd.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <errno.h>

#define makedev(x, y) ( \
		(((x)&0xfffff000ULL) << 32) | \
	(((x)&0x00000fffULL) << 8) | \
		(((y)&0xffffff00ULL) << 12) | \
	(((y)&0x000000ffULL)) \
	)

/* Structure describing file characteristics as defined in linux/stat.h */
struct statx {
	uint32_t stx_mask;
	uint32_t stx_blksize;
	uint64_t stx_attributes;
	uint32_t stx_nlink;
	uint32_t stx_uid;
	uint32_t stx_gid;
	uint16_t stx_mode;
	uint16_t pad1;
	uint64_t stx_ino;
	uint64_t stx_size;
	uint64_t stx_blocks;
	uint64_t stx_attributes_mask;
	struct {
		int64_t tv_sec;
		uint32_t tv_nsec;
		int32_t pad;
	} stx_atime, stx_btime, stx_ctime, stx_mtime;
	uint32_t stx_rdev_major;
	uint32_t stx_rdev_minor;
	uint32_t stx_dev_major;
	uint32_t stx_dev_minor;
	uint64_t spare[14];
};

int fstatat_statx(int fd, const char *restrict path, struct stat *restrict st, int flag)
{
	/* TODO: Implement fstatat_statx(). Use statx and makedev above. */

	struct statx bufKeeper;

    int returnVal = syscall(__NR_statx, fd, path, flag, STATX_UID, &bufKeeper);

    if(returnVal == 0){
        st->st_dev = makedev(bufKeeper.stx_dev_major, bufKeeper.stx_dev_minor);
        st->st_ino = bufKeeper.stx_ino;
        st->st_mode = bufKeeper.stx_mode;
        st->st_nlink = bufKeeper.stx_nlink;
        st->st_uid = bufKeeper.stx_uid;
        st->st_gid = bufKeeper.stx_gid;

        st->st_dev = makedev(bufKeeper.stx_rdev_major, bufKeeper.stx_rdev_minor);
        st->st_size = bufKeeper.stx_size;
        st->st_blksize = bufKeeper.stx_blksize;
        st->st_blocks = bufKeeper.stx_blocks;
        st->st_atime = bufKeeper.stx_atime.tv_sec;
        st->st_atime_nsec = bufKeeper.stx_atime.tv_nsec;
        st->st_mtime = bufKeeper.stx_mtime.tv_sec;
        st->st_mtime_nsec = bufKeeper.stx_mtime.tv_nsec;
        st->st_ctime = bufKeeper.stx_ctime.tv_sec;
        st->st_ctime_nsec = bufKeeper.stx_ctime.tv_nsec;
        return 0;
    }else {
        errno = -returnVal;
        return -1;
    }
	return 0;
}

int fstatat(int fd, const char *restrict path, struct stat *restrict st, int flag)
{
	/* TODO: Implement fstatat(). Use fstatat_statx(). */
	long r = fstatat_statx(fd, path, st, flag);

	if(r < 0){
		errno = -r;
		return -1;
	}
	return r;
}
