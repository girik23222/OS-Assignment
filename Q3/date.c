#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <time.h>

int main(int argc, char *argv[])
{
    time_t t = time(NULL);
    struct tm date = *localtime(&t);
    char *day[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    char *month[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    if (argc == 1)
    {
        // Default format: Day DD Month name Year HH:MM:SS
        printf("%s %02d %s %d %02d:%02d:%02d\n",
               day[date.tm_wday],
               date.tm_mday,
               month[date.tm_mon],
               date.tm_year + 1900,
               date.tm_hour,
               date.tm_min,
               date.tm_sec);
    }
    else
    {
        if (strcmp(argv[1], "-r") == 0)
        {
            // RFC 2822 format
            printf("%s, %02d %s %d %02d:%02d:%02d +0000\n",
                   day[date.tm_wday],
                   date.tm_mday,
                   month[date.tm_mon],
                   date.tm_year + 1900,
                   date.tm_hour,
                   date.tm_min,
                   date.tm_sec);
        }
        else if (strcmp(argv[1], "-u") == 0)
        {
            // UTC format
            printf("%d-%02d-%02dT%02d:%02d:%02dZ\n",
                   date.tm_year + 1900,
                   date.tm_mon + 1,
                   date.tm_mday,
                   date.tm_hour,
                   date.tm_min,
                   date.tm_sec);
        }
        else if (strcmp(argv[1], "-e") == 0)
        {
            // European Format
            printf("%02d-%02d-%d\n",
                   date.tm_mday,
                   date.tm_mon + 1,
                   date.tm_year + 1900);
        }
        else
        {
            printf("Invalid Choice\n");
            printf("Use '-u' for representing time in UTC Format\n");
            printf("Use '-r' for representing time in RFC 2822 Format\n");
            printf("Use '-e' for representing time in European Format\n");
            exit(0);
        }
    }

    return 0;
}
