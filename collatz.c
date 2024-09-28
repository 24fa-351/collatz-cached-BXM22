#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int collatz_eq(int n) //collatz equation
{   
    int steps = 0;
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        steps++;
    }
    return steps;
}

int test_collaz(int N, int MIN, int MAX) //generates file and puts the num and steps onto csv
{
    const char *filename = "collatz_output.csv"; 
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(fp, "Number,Steps\n"); 

    for (int i = 0; i < N; i++) {
        int randomNumber = (rand() % (MAX - MIN + 1)) + MIN;
        fprintf(fp, "%d,", randomNumber); 

        int steps = collatz_eq(randomNumber);
        fprintf(fp, "%d\n", steps); 
    }

    fclose(fp);
    printf("Data exported to %s successfully.\n", filename);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 4) {
        printf("Usage: %s <N> <MIN> <MAX>\n", argv[0]);
        return 1;  
    }

    int N = atoi(argv[1]);
    int MIN = atoi(argv[2]);
    int MAX = atoi(argv[3]);

    srand(time(NULL)); 

    if (test_collaz(N, MIN, MAX) != 0) {
        printf("Error in processing.\n");
        return 1;
    }

    return 0;
}
