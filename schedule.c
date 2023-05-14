#include <stdio.h>
#include <stdbool.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sortProcesses(int *arrival_time, int *burst_time, int num_processes)
{
    for (int i = 0; i < num_processes - 1; i++)
    {
        for (int j = 0; j < num_processes - i - 1; j++)
        {
            if (arrival_time[j] > arrival_time[j + 1])
            {
                swap(&arrival_time[j], &arrival_time[j + 1]);
                swap(&burst_time[j], &burst_time[j + 1]);
            }
        }
    }
}

int main()
{
    // Initialize variables
    int i, num_processes = 0, time_quantum = 0;
    int arrival_time[10] = {0}, burst_time[10] = {0}, temp[10] = {0};
    float average_wait_time = 0, average_turnaround_time = 0;
    bool round_robin_algorithm = false;

    // Define Number of Processes
    while (num_processes < 1 || num_processes > 10)
    {
        printf("\nEnter Total Number of Processes (1 - 10):\t");
        scanf("%d", &num_processes);
        if (num_processes < 1 || num_processes > 10)
        {
            printf("Incorrect Value Entered");
        }
    }

    // Define Process Details
    for (i = 0; i < num_processes; i++)
    {
        printf("\nEnter Details of Process[%d]\n", i + 1);
        printf("Arrival Time (>= 0):\t");
        scanf("%d", &arrival_time[i]);

        printf("Burst Time (> 0):\t");
        scanf("%d", &burst_time[i]);

        temp[i] = burst_time[i];

        if (arrival_time[i] < 0 || burst_time[i] <= 0)
        {
            printf("Incorrect Values Entered");
            i--;
        }
    }

    // Define Quantum
    if (round_robin_algorithm)
    {
        while (time_quantum < 1)
        {
            printf("\nEnter Time Quantum (> 0):\t");
            scanf("%d", &time_quantum);
            if (time_quantum < 1)
            {
                printf("Incorrect Value Entered");
            }
        }
    }

    // Prepare Output
    printf("\nProcess ID\t\tArrival Time\t\tBurst Time\tTurnaround Time\tWaiting Time\n");

    // Perform Scheduling Calculations
    average_wait_time = 0;
    average_turnaround_time = 0;

    if (!round_robin_algorithm)
    {
        // First come, first serve
        sortProcesses(arrival_time, burst_time, num_processes);

        int burstSum = 0;
        for (i = 0; i < num_processes; i++)
        {
            int wait_time = burstSum - arrival_time[i];
            average_wait_time += wait_time;
            int turnaround_time = burst_time[i] + wait_time;
            average_turnaround_time += turnaround_time;
            printf("%d\t\t\t%d\t\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], turnaround_time, wait_time);
        burstSum += burst_time[i];
    }
}
else
{
    // Round robin
    int remaining[num_processes];
    int wait_times[num_processes], turnaround_times[num_processes];
    bool complete[num_processes];
       int elapsed_time = 0;

    sortProcesses(arrival_time, burst_time, num_processes);

    // Initialize arrays
    for (i = 0; i < num_processes; i++)
    {
        remaining[i] = burst_time[i];
        complete[i] = false;
    }

    // Run the scheduler
    int completed_processes = 0;
    while (completed_processes < num_processes)
    {
        for (i = 0; i < num_processes; i++)
        {
            // Check if the process has arrived and has remaining time
            if (complete[i] || arrival_time[i] > elapsed_time || remaining[i] <= 0)
                continue;

            // Execute the process
            if (remaining[i] <= time_quantum)
            {
                elapsed_time += remaining[i]; // Finish up this process
                remaining[i] = 0;             // No more time left
            }
            else
            {
                elapsed_time += time_quantum;
                remaining[i] -= time_quantum;
            }

            // Update wait/turnaround for this process
            wait_times[i] = elapsed_time - burst_time[i] - arrival_time[i];
            turnaround_times[i] = elapsed_time - arrival_time[i];

            // Update completed processes
            if (remaining[i] == 0)
            {
                complete[i] = true;
                completed_processes++;
            }
        }
    }

    // Results
    for (i = 0; i < num_processes; i++)
    {
        average_wait_time += wait_times[i];
        average_turnaround_time += turnaround_times[i];
        printf("%d\t\t\t%d\t\t\t%d\t\t%d\t\t%d\n", i + 1, arrival_time[i], burst_time[i], turnaround_times[i], wait_times[i]);
    }
}

// Calculate & Print Average Wait and Turnaround Times
average_turnaround_time /= num_processes;
average_wait_time /= num_processes;
printf("\n\nAverage Waiting Time:\t%f", average_wait_time);
printf("\nAvg Turnaround Time:\t%f\n", average_turnaround_time);

return 0;
}
