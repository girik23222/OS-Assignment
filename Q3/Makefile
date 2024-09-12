# Default target
all: date cal uptime main

# Rule to build date
date: date.c
	gcc date.c -o date

# Rule to build calendar
cal: cal.c
	gcc cal.c -o cal

# Rule to build uptime
uptime: uptime.c
	gcc uptime.c -o uptime

# Rule to build main
main: main.c date cal uptime
	gcc main.c -o main

# Rule to clean up generated files
clean:
	rm -f date cal uptime main
