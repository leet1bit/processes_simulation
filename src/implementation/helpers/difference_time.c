

#include <time.h>

long diff_ms_safe(struct timespec a, struct timespec b) {
    long sec  = b.tv_sec  - a.tv_sec;
    long nsec = b.tv_nsec - a.tv_nsec;

    if (nsec < 0) {
        sec--;
        nsec += 1000000000L;
    }

    return sec * 1000 + nsec / 1000000;
}