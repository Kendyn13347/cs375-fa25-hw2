#include <stdio.h>
#include <sys/resource.h>

static void print_limit(const char *label, int resource)
{
    struct rlimit lim;
    if (getrlimit(resource, &lim) == -1) {
        perror("getrlimit");
        return;
    }

    if (lim.rlim_cur == RLIM_INFINITY) {
        printf("%s: unlimited\n", label);
    } else {
        /* rlim_t is typically unsigned long; print safely as unsigned long long */
        printf("%s: %llu\n", label, (unsigned long long)lim.rlim_cur);
    }
}

int main(void)
{
    /* soft (current) limits */
    print_limit("stack size", RLIMIT_STACK);

#ifdef RLIMIT_NPROC   /* defined on Linux; not on some other OSes */
    print_limit("process limit", RLIMIT_NPROC);
#else
    printf("process limit: (not available on this platform)\n");
#endif

    print_limit("max file descriptors", RLIMIT_NOFILE);
    return 0;
}
