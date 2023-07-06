#include <stdio.h>
#include <string.h>

/**
rewrite readlines to store lines in an array supplied by main,
rather than calling alloc to maintain storage. How much faster
is the program?
*/

#define MAXLINES 5000 /* Max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */
#define MAXCHARS 10000

char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *linestg, char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main() {
    int nlines; /* number of input lines read */
    int linestg[MAXCHARS]; // storage for the line, to be used instead of alloc

    if ((nlines = readlines(linestg, lineptr, MAXLINES)) >= 0) {
        qsort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("error: input too big to sort\n");
        return 1;
    }
}

int getline(char *, int);
char *alloc(int);
void afree(char *p);

/* readlines; read input lines */
int readlines(char *linestg, char *lineptr[], int maxlines) {
    int len, nlines, stgp = 0;
    char *p, line[MAXLEN];

    nlines = 0;
    printf("got here!\n");
    while ((len = getline(line, MAXLEN)) > 0) {
        printf("Also here!\n");
        if (nlines >= maxlines || stgp + 1 + len > MAXCHARS)
            return -1;
        else {
            printf("Then here!\n");
            p = linestg + stgp;
            stgp += len + 1; // advance to next available
            line[len - 1] =  '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}

/* writelines: write output line */
void writelines(char *lineptr[], int nlines) {
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);
}

/* qsort: v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right) {
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right) /* do nothing if array contains */
        return; /* fewer than two elements */
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left+1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j) {
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

/**
FROM SECTION 1.9
*/
/* getline: Read a line into s, return length. */
int getline(char s[], int lim) {
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/**
FROM SECTION 5.4
*/
#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE]; /* storage for alloc */
static char *allocp = allocbuf; /* next free position */

/* return pointer to n characters */
char *alloc(int n) {
    if (allocbuf + ALLOCSIZE - allocp >= n) { /* it fits */
        allocp += n;
        return allocp - n; /* old pointer */
    } else /* not enough room */
        return 0;
}

/* free storage pointed to by p */
void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}
