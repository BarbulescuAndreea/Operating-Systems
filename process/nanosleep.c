#include <internal/syscall.h>
#include <time.h>

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    int ret;
    ret = syscall(__NR_nanosleep, req, rem);

    return ret;
}