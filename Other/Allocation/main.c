#include <stdio.h>

int main() {

    return 0;
}

#define MAXALLOC 2000

char allocbuf[MAXALLOC];
char *allocp = allocbuf;

/**
Allocates a particular amount of bytes from statically allocated
memory.
*/
void *alloc(int bytes) {
    int max = allocbuf + MAXALLOC;
    int next = allocp + bytes;
    if (next > max)
        return NULL;

    void *ret = allocp;
    allocp += bytes;
    return ret;
}
