#include <stdio.h>
#include <stdlib.h>


int zeller(int day, int month, int year) {
    if (month == 1 || month == 2) {
        month += 12;
        year -= 1;
    }
    int a = year % 100;       // Year of the century
    int cent = year / 100;       // Century
    int h = (day + (13 * (month + 1)) / 5 + a + a / 4 + cent / 4 - 2 * cent) % 7;


    return (h + 5) % 7;  // makeing 0=Monday, ..., 6=Sunday
}

void calendar(int month, int year) {
    char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Check for leap year in case of February
    if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
        days[1] = 29;
    }

    //  0 = Monday, ..., 6 = Sunday
    int first_day = zeller(1, month, year);  
    
    printf("     %s %d\n", months[month - 1], year);
    printf(" Mo Tu We Th Fr Sa Su\n");
    
    // Spaces before first day
    for (int i = 0; i < first_day; i++) {
        printf("   ");
    }

    for (int day = 1; day <= days[month - 1]; day++) {
        printf("%3d", day);
        // Checking Sun arrived and at the end of month
        if ((day + first_day) % 7 == 0 || day == days[month - 1]) {
            printf("\n");
        }
    }
}

int main(int argc, char *argv[])
{
    int month, year;

    if (argc == 3) {
        month = atoi(argv[1]);
        year = atoi(argv[2]);
    } else {

        printf("Error");
    }
    calendar(month, year);

    return 0;
}
