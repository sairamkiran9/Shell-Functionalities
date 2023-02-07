#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sys/times.h>
#include <sys/resource.h>

void print_real_time(clock_t end_time, clock_t start_time)
{
    int delta = end_time - start_time;
    int r_usec = delta % 100;
    int r_sec = delta / 100;
    int r_m = 0;
    if (r_sec >= 60)
    {
        r_m = r_sec / 60;
        r_sec = r_sec % 60;
    }
    printf("\nreal\t%dm%d.%03ds\n", r_m, r_sec, r_usec);
}

void print_time(char *type, long tv_sec, long tv_usec)
{
    int usecs, secs, mins = 0;

    usecs = tv_usec / 1000;
    secs = tv_sec;

    if (usecs >= 1000)
    {
        secs = usecs / 1000;
        usecs %= 1000;
    }
    if (secs >= 60)
    {
        mins = secs / 60;
        secs %= 60;
    }
    printf("%s\t%dm%d.%03ds\n", type, mins, secs, usecs);
}

int main(int argc, char *argv[])
{
    int status;
    pid_t pid;

    clock_t start, end;
    struct tms tms_start, tms_end;

    struct rusage usage;

    start = times(&tms_start);

    pid = fork();

    if (pid < 0)
    {
        fprintf(stderr, "Failed to fork the process\n");
        exit(1);
    }
    else if (pid == 0)
    {
        execvp(argv[1], &argv[1]);
        fprintf(stderr, "%s command not found\n", argv[1]);
        exit(1);
    }
    else
    {
        wait4(pid, &status, 0, &usage);
    }

    end = times(&tms_end);

    print_real_time(end, start);
    print_time("user", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    print_time("sys", usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
    return 0;
}
