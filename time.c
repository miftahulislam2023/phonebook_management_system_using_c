#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    time_t t; // long integer
    struct tm *systime;
    char *month;
    t = time(NULL);
    systime = localtime(&t);
    printf("%ld\n", t);
    printf("%d %d %d %d %d\n", systime->tm_hour, systime->tm_mon, systime->tm_year + 1900, systime->tm_wday, systime->tm_mday);

    switch (systime->tm_mon)
    {
    case 0:
        strcpy(month, "January");
        break;
    case 3:
        strcpy(month, "April");
        break;
    default:
        break;
    }
    printf("%s", month);
    return 0;
}
