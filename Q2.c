#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Function for binary search using fork
void binarySearch(int arr[], int left, int right, int target)
{
    if (left > right)
    {
        printf("-1\n");
        exit(0);
    }

    int mid = (left + right) / 2;

    if (arr[mid] == target)
    {
        printf("The target value found at index: %d\n",mid);
        exit(0);
    }
    // Right array
    else if (arr[mid] < target)
    {
        pid_t q = fork();
        if (q == 0)
        { // Child process
            binarySearch(arr, mid + 1, right, target);
            exit(0);
        }
        else if (q < 0)
        { // Fork failed
            perror("Fork failed");
            exit(1);
        }
        else
        { // Parent process
            wait(NULL);
            exit(0);
        }
    }
    // Left array
    else
    {
        pid_t q = fork();
        if (q == 0)
        {   // Child process
            binarySearch(arr, left, mid - 1, target);
            exit(0); 
        }
        else if (q < 0)
        { // Fork failed
            perror("Fork failed");
            exit(1);
        }
        else
        { // Parent process
            wait(NULL); 
            exit(0);
        }
    }
}

int main()
{
    int numbers[16] = {3, 5, 8, 12, 14, 18, 21, 25, 29, 34, 37, 42, 46, 50, 54, 60};
    int target;

    // Print the array
    printf("Array: ");
    for (int i = 0; i < 16; i++)
    {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    // Ask the user for the target value
    printf("Enter the target value to search: ");
    scanf("%d", &target);

    // Start binary search with the entire array (index 0 to 15)
    binarySearch(numbers, 0, 15, target);

    return 0;
}
