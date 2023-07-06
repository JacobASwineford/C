#include <stdio.h>
#include <limits.h>
#include <float.h>

/**
Write a program to determine the ranges of char, short, int,
and long variables, both signed and unsigned, by printing
appropriate values from standard headers and by direct computation.
Harder if you compute them. determine the ranges of various floating
point types.
*/

void bytes(char[], int);
void size(char[], int, long, long);

int main() {
  printf("Using standard headers:\n");
  printf("Signed char min: %d\n", SCHAR_MIN);
  printf("Signed char max: %d\n", SCHAR_MAX);
  printf("Unsigned char max: %u\n", UCHAR_MAX);

  printf("Signed short min: %d\n", SHRT_MIN);
  printf("Signed short max: %d\n", SHRT_MAX);
  printf("Unsigned short max: %u\n", USHRT_MAX);

  printf("Signed int min: %d\n", INT_MIN);
  printf("Signed int max: %d\n", INT_MAX);
  printf("Unsigned int max: %u\n", UINT_MAX);

  printf("Signed long min: %ld\n", LONG_MIN);
  printf("Signed long max: %ld\n", LONG_MAX);
  printf("Unsigned long max: %lu\n", ULONG_MAX);

  printf("\nUsing direct computation:\n");

  // signed char
  char scmin = -((unsigned char) ~0 >> 1) - 1;
  char scmax = (unsigned char) ~0 >> 1;
  printf("Signed char [%d bytes]:\nmin:%d\nmax:%d\n\n", sizeof(char), scmin, scmax);

  // unsigned char
  unsigned char ucmin = 0;
  unsigned char ucmax = ~0;
  printf("Unsigned char [%d bytes]:\nmin:%d\nmax:%d\n\n", sizeof(unsigned char), ucmin, ucmax);

  // signed short
  short ssmin = -((unsigned short) ~0 >> 1) - 1;
  short ssmax = ((unsigned short) ~0 >> 1);
  printf("Signed short [%d bytes]:\nmin:%d\nmax:%d\n\n", sizeof(short), ssmin, ssmax);

  // unsigned short
  unsigned short usmin = 0;
  unsigned short usmax = ~0;
  printf("Unsigned short [%d bytes]:\nmin:%d\nmax:%d\n\n", sizeof(unsigned short), usmin, usmax);

  // signed long
  long slmin = -((unsigned long) ~0 >> 1) - 1;
  long slmax = ((unsigned long) ~0 >> 1);
  printf("Signed long [%d bytes]:\nmin:%d\nmax:%d\n\n", sizeof(long), slmin, slmax);

  // unsigned long
  unsigned long ulmin = 0;
  unsigned long ulmax = ~0;
  printf("Unsigned long [%d bytes]:\nmin:%d\nmax:%d\n\n", sizeof(unsigned long), ulmin, ulmax);

  // signed int
  int imin = -((unsigned int) ~0 >> 1) - 1;
  int imax = ((unsigned int) ~0 >> 1);
  printf("Signed int [%d bytes]:\nmin:%d\nmax:%d\n\n", sizeof(int), imin, imax);

  // unsigned int
  unsigned int uimin = 0;
  unsigned int uimax = ~0;
  printf("Unsigned int [%d bytes]:\nmin:%d\nmax:%d\n\n", sizeof(unsigned int), uimin, uimax);

  return 0;
}
