#include <time.h>
#include <unistd.h>
#include <errno.h>

unsigned int sleep(unsigned int seconds)
{
    struct timespec req, rem;
    
    req.tv_sec = seconds;
    req.tv_nsec = 0;

    while(nanosleep(&req, &rem) == -1) {
        req = rem;
    }
    return 0;
}