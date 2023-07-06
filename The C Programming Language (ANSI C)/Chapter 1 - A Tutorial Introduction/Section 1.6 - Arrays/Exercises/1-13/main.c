#include <stdio.h>

#define MAX_WORD 12

/**
Write a program to print a histogram of the lengths of words
in its input. It is easy to draw a histogram with the bars
horizontal; a vertical orientation is more challenging.
*/

void horizontal(void);
void vertical(void);

int main() {
    horizontal();
    vertical();
    return 0;
}

void horizontal() {
    int i, c, spaces, wcount;
    wcount = 0;
    printf("Enter a sentence: ");
    while (1) {
        c = getchar();
        if (c != ' ' && c != '\n') {
            putchar(c);
            wcount++;
        } else {
            printf(":");
            spaces = MAX_WORD - (wcount + 1);
            for (i = 0; i < spaces; ++i)
                putchar(' ');
            for (i = 0; i < wcount; i++)
                putchar('#');
            putchar('\n');
            wcount = 0;

            if (c == '\n')
                break;
        }
    }
}

void vertical() {
    int sen[200];

    int ccounts[20];
    int ccount;
    int mcount;

    int wlos[20];
    int wlo;

    int nword;
    int c;

    int wlogged;

    ccount = 0;
    wlo = 0;
    nword = 0;
    wlogged = 0;
    mcount = 0;

    printf("Enter a sentence: ");
    while (1) {
        c = getchar();
        sen[wlo] = c;
        if (c != ' ' && c != '\n') {
            if (!wlogged) {
                wlos[nword] = wlo;
                wlogged = 1;
            }
            ccount++;
        } else {
            ccounts[nword++] = ccount;
            if (ccount > mcount)
                mcount = ccount;
            ccount = 0;
            wlogged = 0;

            if (c == '\n') break;
        }
        wlo++;
    }

/*
    int i;
    int e;
    for (i = 0; i < wlo; i++)
        putchar(sen[i]);
    printf("\n");
    for (i = 0; i < nword; i++) {
        int word_count = ccounts[i];
        int lo = wlos[i];
        printf("word count: %d, word lo: %d [", word_count, lo);

        while (word_count--) {
            putchar(sen[lo++]);
        }
        printf("]\n");
    }
    printf("max count: %d\n\n", mcount);
*/

    // print bars
    int i;
    int vcount = mcount;
    while (vcount) {
        for (i = 0; i < nword; i++) {
            if (ccounts[i] >= vcount)
                printf(" # ");
            else
                printf("   ");
        }
        putchar('\n');
        vcount--;
    }

    // print middle
    for (i = 0; i < nword; i++)
        printf("---");
    putchar('\n');

    // print words
    while (vcount < mcount) {
        for (i = 0; i < nword; i++) {
            if (ccounts[i] >= vcount)
                printf(" %c ", sen[wlos[i] + vcount]);
            else
                printf("   ");
        }
        putchar('\n');
        vcount++;
    }

}


