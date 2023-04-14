/* SPDX-License-Identifier: BSD-3-Clause */

#ifndef TIME_H
#define TIME_H 1

#include <stddef.h> /* for size_t */

#ifdef __cplusplus
extern "C" {
#endif

struct tm {
int tm_sec;
int tm_min;
int tm_hour;
int tm_mday;
int tm_mon;
int tm_year;
int tm_wday;
int tm_yday;
int tm_isdst;
};

typedef long time_t;

struct timespec {
               time_t tv_sec;        /* seconds */
               long   tv_nsec;       /* nanoseconds */
};

#ifdef __cplusplus
}
#endif

#endif