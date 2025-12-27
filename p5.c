#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int maximum[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

int nProcesses, nResources;

int isSafe()
{
    int work[MAX_RESOURCES];
    int finish[MAX_PROCESSES];
    int count = 0;

    for (int i = 0; i < nResources; i++)
        work[i] = available[i];

    for (int i = 0; i < nProcesses; i++)
        finish[i] = 0;

    while (count < nProcesses)
    {
        int found = 0;

        for (int i = 0; i < nProcesses; i++)
        {
            if (finish[i] == 0)
            {
                int j;
                for (j = 0; j < nResources; j++)
                {
                    if (need[i][j] > work[j])
                        break;
                }

                if (j == nResources)
                {
                    for (int k = 0; k < nResources; k++)
                        work[k] += allocation[i][k];

                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }

        if (!found)
            break;
    }

    return (count == nProcesses);
}

void simulateResourceRequest(int process, int request[])
{
    for (int i = 0; i < nResources; i++)
    {
        if (request[i] > need[process][i])
        {
            printf("Error: Request exceeds maximum claim.\n");
            return;
        }
    }

    for (int i = 0; i < nResources; i++)
    {
        if (request[i] > available[i])
        {
            printf("Process %d must wait. Insufficient resources.\n", process);
            return;
        }
    }

    for (int i = 0; i < nResources; i++)
    {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (isSafe())
    {
        printf("Request by Process %d granted. New state is safe.\n", process);
    }
    else
    {
        printf("Request by Process %d denied. New state would be unsafe. Rolling back.\n", process);

        for (int i = 0; i < nResources; i++)
        {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }
}

int main()
{
    printf("Enter the number of processes: ");
    scanf("%d", &nProcesses);

    printf("Enter the number of resources: ");
    scanf("%d", &nResources);

    printf("Enter the maximum resources for each process:\n");
    for (int i = 0; i < nProcesses; i++)
    {
        printf("Process %d: ", i);
        for (int j = 0; j < nResources; j++)
        {
            scanf("%d", &maximum[i][j]);
            need[i][j] = maximum[i][j];
        }
    }

    printf("Enter the available resources: ");
    for (int i = 0; i < nResources; i++)
        scanf("%d", &available[i]);

    printf("Enter the current allocation for each process:\n");
    for (int i = 0; i < nProcesses; i++)
    {
        printf("Process %d: ", i);
        for (int j = 0; j < nResources; j++)
        {
            scanf("%d", &allocation[i][j]);
            need[i][j] -= allocation[i][j];
        }
    }

    int requestingProcess;
    printf("Enter the process number making a resource request: ");
    scanf("%d", &requestingProcess);

    int request[nResources];
    printf("Enter the resource request for Process %d: ", requestingProcess);
    for (int i = 0; i < nResources; i++)
        scanf("%d", &request[i]);

    simulateResourceRequest(requestingProcess, request);

    return 0;
}
