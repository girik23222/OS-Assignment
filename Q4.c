#include <stdio.h>

// Function to swap two integers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// FIFO
void sortForFIFO(int n, int arrival_time[], int burst_time[], int process_id[])
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arrival_time[j] > arrival_time[j + 1])
            {
                // Swap arrival time
                swap(&arrival_time[j], &arrival_time[j + 1]);
                // Swap burst time
                swap(&burst_time[j], &burst_time[j + 1]);
                // Swap process ID
                swap(&process_id[j], &process_id[j + 1]);
            }
        }
    }
}
void FIFO_Times(int n, int arrival_time[], int burst_time[], int process_id[])
{
    sortForFIFO(n, arrival_time, burst_time, process_id);
    int completion_time[n], turnaround_time[n], response_time[n];
    int total_turnaround_time = 0, total_response_time = 0;
    int current_time = 0;

    for (int i = 0; i < n; i++)
    {
        // Calculate completion time
        if (current_time < arrival_time[i])
        {
            current_time = arrival_time[i];
        }
        completion_time[i] = current_time + burst_time[i];
        current_time = completion_time[i];

        // Calculate Turnaround Time and Response Time
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        response_time[i] = turnaround_time[i] - burst_time[i];

        // Accumulate total Turnaround Time and Response Time
        total_turnaround_time += turnaround_time[i];
        total_response_time += response_time[i];
    }

    // Calculate and print the average Turnaround Time and average Response Time
    double avg_turnaround_time = (double)total_turnaround_time / n;
    double avg_response_time = (double)total_response_time / n;

    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Response Time: %.2f\n", avg_response_time);

    // Print the order of execution
    printf("Order of execution: ");
    for (int i = 0; i < n; i++)
    {
        printf("P%d ", process_id[i]);
    }
    printf("\n\n");
}

// SJF

void sortForSJF(int n, int arrival_time[], int burst_time[], int process_id[])
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            // Sort by arrival time first, if equal, then by burst time
            if (arrival_time[j] > arrival_time[j + 1] ||
                (arrival_time[j] == arrival_time[j + 1] && burst_time[j] > burst_time[j + 1]))
            {
                // Swap arrival time
                swap(&arrival_time[j], &arrival_time[j + 1]);
                // Swap burst time
                swap(&burst_time[j], &burst_time[j + 1]);
                // Swap process ID
                swap(&process_id[j], &process_id[j + 1]);
            }
        }
    }
}

void SJF_Times(int n, int arrival_time[], int burst_time[], int process_id[])
{
    sortForSJF(n, arrival_time, burst_time, process_id);
    int completion_time[n], turnaround_time[n], response_time[n], start_time[n];
    int total_turnaround_time = 0, total_response_time = 0;
    int current_time = 0;
    int is_completed[n]; // To mark completed processes

    // Initialize all processes as incomplete
    for (int i = 0; i < n; i++)
    {
        is_completed[i] = 0;
    }

    int completed = 0;

    while (completed < n)
    {
        int min_burst = 999999, index = -1;
        // Find process with minimum burst time that has arrived and is not completed
        for (int i = 0; i < n; i++)
        {
            if (arrival_time[i] <= current_time && !is_completed[i] && burst_time[i] < min_burst)
            {
                min_burst = burst_time[i];
                index = i;
            }
        }

        // If no process is found, move the current time forward to the next arriving process
        if (index == -1)
        {
            current_time++;
            continue;
        }

        // Set start time for the chosen process
        start_time[index] = current_time;

        // Calculate completion time for the chosen process
        completion_time[index] = current_time + burst_time[index];
        current_time = completion_time[index];

        // Mark the process as completed
        is_completed[index] = 1;
        completed++;

        // Calculate turnaround time and response time
        turnaround_time[index] = completion_time[index] - arrival_time[index];
        response_time[index] = start_time[index] - arrival_time[index];

        // Accumulate total turnaround and response times
        total_turnaround_time += turnaround_time[index];
        total_response_time += response_time[index];
    }

    // Print the order of execution
    printf("Order of execution: ");
    for (int i = 0; i < n; i++)
    {
        printf("P%d ", process_id[i]);
    }
    printf("\n");
    // Calculate and print the average turnaround time and response time
    double avg_turnaround_time = (double)total_turnaround_time / n;
    double avg_response_time = (double)total_response_time / n;

    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Response Time: %.2f\n", avg_response_time);

    printf("\n\n");
}

// SRTF
// Function to find the process with the shortest remaining time that has arrived
int FindPRocess(int n, int arrival_time[], int remaining_time[], int current_time, int is_completed[]) {
    int min_remaining_time = 999999, index = -1;
    for (int i = 0; i < n; i++) {
        if (arrival_time[i] <= current_time && !is_completed[i] && remaining_time[i] < min_remaining_time) {
            min_remaining_time = remaining_time[i];
            index = i;
        }
    }
    return index;
}

// Function to calculate average Turnaround Time and average Response Time (SRTF)
void SRTF_Times(int n, int arrival_time[], int burst_time[], int process_id[]) {
    int completion_time[n], turnaround_time[n], response_time[n], remaining_time[n];
    int total_turnaround_time = 0, total_response_time = 0;
    int current_time = 0, completed = 0, is_completed[n], first_response[n];

    // Initialize remaining times and flags
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
        is_completed[i] = 0;  // Mark all processes as not completed
        first_response[i] = -1;  // To mark if the process has started
    }

    // Start preemptive scheduling loop
    while (completed < n) {
        int index = FindPRocess(n, arrival_time, remaining_time, current_time, is_completed);

        if (index == -1) {
            current_time++;  // No process is available, increase time
            continue;
        }

        // Mark first response time (if not already done)
        if (first_response[index] == -1) {
            first_response[index] = current_time;
            response_time[index] = first_response[index] - arrival_time[index];  // Calculate response time
        }

        // Process this task for one unit of time
        remaining_time[index]--;
        current_time++;

        // If the process is complete
        if (remaining_time[index] == 0) {
            completion_time[index] = current_time;
            turnaround_time[index] = completion_time[index] - arrival_time[index];
            is_completed[index] = 1;
            completed++;

            total_turnaround_time += turnaround_time[index];
            total_response_time += response_time[index];
        }
    }

    // Print the order of execution (based on process IDs)
    printf("Order of execution: ");
    for (int i = 0; i < n; i++) {
        printf("P%d ", process_id[i]);
    }
    printf("\n");
    // Calculate and print the average Turnaround Time and average Response Time
    double avg_turnaround_time = (double)total_turnaround_time / n;
    double avg_response_time = (double)total_response_time / n;

    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Response Time: %.2f\n", avg_response_time);

    printf("\n\n");
}
// RR

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int process_id[n], arrival_time[n], burst_time[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter Process ID, Arrival Time and Burst Time for process %d: ", i + 1);
        scanf("%d %d %d", &process_id[i], &arrival_time[i], &burst_time[i]);
    }
    printf("\n");
    printf("    According to FIFO process scheduling    \n");
    // Sort processes based on arrival time (FIFO order)

    FIFO_Times(n, arrival_time, burst_time, process_id);

    printf("    According to SJF process scheduling    \n");

    SJF_Times(n, arrival_time, burst_time, process_id);

    printf("    According to SRTF process scheduling    \n");
    SRTF_Times(n, arrival_time, burst_time, process_id);
    // printf("    According to RR process scheduling    \n");
    // sortProcessesByArrival(n, arrival_time, burst_time, process_id);
    // calculateTimes(n, arrival_time, burst_time, process_id);
    return 0;
}
