#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h> //for qsort
struct process_struct
{
    int pid;
    int at;
    int bt;
    int ct, wt, tat, rt, start_time;
} ps[100];
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Non peemptive
void FIFO(int n, int arrival_time[], int burst_time[], int process_id[])
{
    // 1. Making local copies of arrays
    int pid[n], arrive[n], burst[n];
    for (int i = 0; i < n; i++)
    {
        pid[i] = process_id[i];
        arrive[i] = arrival_time[i];
        burst[i] = burst_time[i];
    }

    // 2. Sorting the arrays according to arrival time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arrive[i] > arrive[j])
            {
                // Swap arrival times
                swap(&arrive[i], &arrive[j]);
                // Swap burst times
                swap(&burst[i], &burst[j]);
                // Swap process IDs
                swap(&pid[i], &pid[j]);
            }
        }
    }

    int waiting_time[n], turnaround_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;
    int current_time = 0;

    // 3. Calculation of waiting time and turnaround time
    for (int i = 0; i < n; i++)
    {
        if (current_time < arrive[i])
        {
            current_time = arrive[i];
        }

        waiting_time[i] = current_time - arrive[i];
        turnaround_time[i] = waiting_time[i] + burst[i];

        current_time += burst[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // 4. Print the order of execution
    printf("Order of Execution: ");
    for (int i = 0; i < n; i++)
    {
        printf("P%d ", pid[i]);
    }
    // Print average waiting time and turnaround time
    printf("\nAverage Waiting Time: %.2f", (float)total_waiting_time / n);
    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
    printf("\n\n");
}
void SJF(int n, int arrival_time[], int burst_time[], int process_id[])
{
    for (int i = 0; i < n; i++)
    {
        ps[i].pid = i;
        ps[i].at = arrival_time[i];
        ps[i].bt = burst_time[i];
    }
    bool is_completed[100] = {false};
    int current_time = 0;
    int completed = 0;
    int sum_tat = 0, sum_wt = 0, sum_rt = 0;

    printf("Order of Execution : ");
    while (completed != n)
    {
        // find process with min. burst time in ready queue at current time
        int min_index = -1;
        int minimum = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && is_completed[i] == false)
            {
                if (ps[i].bt < minimum)
                {
                    minimum = ps[i].bt;
                    min_index = i;
                }
                else if (ps[i].bt == minimum)
                {
                    if (ps[i].at < ps[min_index].at)
                    {
                        minimum = ps[i].bt;
                        min_index = i;
                    }
                }
            }
        }

        if (min_index == -1)
        {
            current_time++;
        }
        else
        {
            // Stroing the values
            ps[min_index].start_time = current_time;
            ps[min_index].ct = ps[min_index].start_time + ps[min_index].bt;
            ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
            ps[min_index].rt = ps[min_index].start_time - ps[min_index].at;

            sum_tat += ps[min_index].tat;
            sum_rt += ps[min_index].rt;

            completed++;
            is_completed[min_index] = true;
            current_time = ps[min_index].ct;
        }
        printf("P%d ", ps[min_index].pid + 1);
    }

    // Outputs
    printf("\nAverage Turn Around Time : %.2f", (float)sum_tat / n);
    printf("\nAverage Response Time : %.2f\n", (float)sum_rt / n);
}

// Peemptive
void SRTF(int n, int arrival_time[], int burst_time[], int process_id[])
{
    int bt_remaining[100];
    for (int i = 0; i < n; i++)
    {
        ps[i].pid = i;
        ps[i].at = arrival_time[i];
        ps[i].bt = burst_time[i];
        bt_remaining[i] = ps[i].bt;
    }
    bool is_completed[100] = {false};
    int current_time = 0;
    int completed = 0;
    ;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    printf("Order of Execution : ");
    while (completed != n)
    {
        // find process with min. burst time in ready queue at current time
        int min_index = -1;
        int minimum = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (ps[i].at <= current_time && is_completed[i] == false)
            {
                if (bt_remaining[i] < minimum)
                {
                    minimum = bt_remaining[i];
                    min_index = i;
                }
                if (bt_remaining[i] == minimum)
                {
                    if (ps[i].at < ps[min_index].at)
                    {
                        minimum = bt_remaining[i];
                        min_index = i;
                    }
                }
            }
        }

        if (min_index == -1)
        {
            current_time++;
        }
        else
        {
            if (bt_remaining[min_index] == ps[min_index].bt)
            {
                ps[min_index].start_time = current_time;
            }
            bt_remaining[min_index] -= 1;
            current_time++;
            if (bt_remaining[min_index] == 0)
            {
                ps[min_index].ct = current_time;
                ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
                ps[min_index].rt = ps[min_index].start_time - ps[min_index].at;

                sum_tat += ps[min_index].tat;
                sum_rt += ps[min_index].rt;
                completed++;
                is_completed[min_index] = true;
            }
        }
        printf("P%d ", ps[min_index].pid + 1);
    }

    // Outputs
    printf("\nAverage Turn Around Time : %.2f", (float)sum_tat / n);
    printf("\nAverage Response Time : %.2f\n", (float)sum_rt / n);
}

int comp(const void *a, const void *b)
{
    int x = ((struct process_struct *)a)->at;
    int y = ((struct process_struct *)b)->at;
    if (x < y)
        return -1; 
    else           
        return 1;  
}
int max(int a, int b)
{
    return a>b?a:b;
}
void RR(int n, int arrival_time[], int burst_time[], int process_id[], int quantum)
{

    int bt_remaining[100];
    for (int i = 0; i < n; i++)
    {
        ps[i].pid = i +1;
        ps[i].at = arrival_time[i];
        ps[i].bt = burst_time[i];
        bt_remaining[i] = ps[i].bt;
    }
    bool is_completed[100] = {false};
    int current_time = 0, index;
    int completed = 0;
    float sum_tat = 0, sum_wt = 0, sum_rt = 0;
    int queue[100], front = 0, rear = 0;

    // Sorting acc to arrival time
    qsort((void *)ps, n, sizeof(struct process_struct), comp);

    queue[rear] = 0;
    is_completed[0] = true;

    printf("Order of Execution: ");
    while (completed != n)
    {
        index = queue[front];
        // q.pop();
        front++;

        if (bt_remaining[index] == ps[index].bt)
        {
            ps[index].start_time = max(current_time, ps[index].at);
            current_time = ps[index].start_time;
        }

        if (bt_remaining[index] - quantum > 0)
        {
            bt_remaining[index] -= quantum;
            current_time += quantum;
        }
        else
        {
            current_time += bt_remaining[index];
            bt_remaining[index] = 0;
            completed++;

            ps[index].ct = current_time;
            ps[index].tat = ps[index].ct - ps[index].at;
            ps[index].rt = ps[index].start_time - ps[index].at;

            sum_tat += ps[index].tat;
            sum_rt += ps[index].rt;
        }

        // check which new Processes needs to be pushed to Ready Queue from Input list
        for (int i = 1; i < n; i++)
        {
            if (bt_remaining[i] > 0 && ps[i].at <= current_time && is_completed[i] == false)
            {
                // q.push(i);
                queue[++rear] = i;
                is_completed[i] = true;
            }
        }
        // check if Process on CPU needs to be pushed to Ready Queue
        if (bt_remaining[index] > 0)
            // q.push(index);
            queue[++rear] = index;

        // if queue is empty, just add one process from list, whose remaining burst time > 0
        if (front > rear)
        {
            for (int i = 1; i < n; i++)
            {
                if (bt_remaining[i] > 0)
                {
                    queue[rear++] = i;
                    is_completed[i] = true;
                    break;
                }
            }
        }
        printf("P%d ", ps[index].pid);
    } // end of while

    // Outputs
    printf("\nAverage Turn Around time= %.2f",(float)sum_tat/n);
  printf("\nAverage Response Time= %.2f",(float)sum_rt/n);  
}
int main()
{
    int n, time_quant;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int process_id[n], arrival_time[n], burst_time[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter Process ID, Arrival Time and Burst Time for process %d: ", i + 1);
        scanf("%d %d %d", &process_id[i], &arrival_time[i], &burst_time[i]);
    }
    printf("Enter the time quantum for Ruund Robin: ");
    scanf("%d", &time_quant);
    printf("\n");
    printf("    According to FIFO process scheduling    \n");
    FIFO(n, arrival_time, burst_time, process_id);
    printf("    According to SJF process scheduling    \n");
    SJF(n, arrival_time, burst_time, process_id);

    printf("    According to SRTF process scheduling    \n");
    SRTF(n, arrival_time, burst_time, process_id);

    printf("    According to RR process scheduling  \n");
    RR(n,arrival_time,burst_time,process_id,time_quant);
}