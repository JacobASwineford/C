void *alloc(int);

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
        return 0;

    void *ret = allocp;
    allocp += bytes;
    return ret;
}
