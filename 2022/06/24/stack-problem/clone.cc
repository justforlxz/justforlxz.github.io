#include <sched.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>

#define CHILD_STACK 8192

int count = 0;

int child_run(void *arg)
{
    printf("count in child: %d\n", ++count);
    return 0;
}

int main(int argc, char *argv[])
{
    int   pid;
    int   status;
    void *child_stack = malloc(CHILD_STACK);
    if (!child_stack) {
        fprintf(stderr, "failed to allocate child stack\n");
        exit(1);
    }

    printf("count before clone: %d\n", count);
    /* Simulate vfork */
    pid = clone(child_run, (void *) ((char *) child_stack + CHILD_STACK),
                CLONE_NEWPID, 0);

    if (pid == -1) {
        fprintf(stderr, "failed to clone\n");
        perror("clone failed: ");
        exit(2);
    }
    else {
        waitpid(pid, &status, 0);
        printf("count after clone: %d\n", count);
    }
    return 0;
}
