#include <stdio.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31} // one extra day in a leap year
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

/**
Rewrite the routines day_of_year and month_day with
pointers instead of indexing.
*/

int main() {
    int d = day_of_year(2000, 4, 29);
    printf("I was born %d days from the beginning of 2000.\n", d);
    return 0;
}

/* day_of_year: set day of year from month and day. */
int day_of_year(int year, int month, int day) {
    int i, leap, temp;

    // check that month is valid
    if (month < 1 || month > 12)
        return -1;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    // check if the day is valid, checked against the current month
    temp = *(*(daytab + leap) + month);
    if (day < 0 || day > temp)
        return -1;

    for (i = 1; i < month; i++)
        day += *(*(daytab + leap) + month);

    return day;
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    // check that year is valid
    if (year < 1 || year > 12)
        return -1;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;

    // check that yearday is valid
    if (yearday < 0 || (!leap && yearday > 365) || (leap && yearday > 366))
        return -1;

    for (i = 1; yearday > daytab[leap][i]; i++)
        yearday -= *(*(daytab + leap) + i);
    *pmonth = i;
    *pday = yearday;
}
