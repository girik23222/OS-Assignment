#include <stdio.h>
#include <sys/sysinfo.h>

int main() {
    struct sysinfo info;

    if (sysinfo(&info) != 0) {
        printf("Error");
        return 1;
    }

    long uptime = info.uptime;
    int hours = uptime / 3600;
    int minutes = (uptime % 3600) / 60;
    int seconds = uptime % 60;

    printf("System Uptime: %02d:%02d:%02d\n", hours, minutes, seconds);

    return 0;
}
