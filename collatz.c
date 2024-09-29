#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cachefile.h"



int collatz_eq(int n, LRUCache* cache) //collatz equation
{   

    int cacheResult = get(cache,n);
    if (cacheResult != -1) {
        return cacheResult;
    }
    int steps = 0;
    int num = n;
    while (n != 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        steps++;
    }
    insert(cache,num,steps);
    return steps;
}

int test_collaz(int N, int MIN, int MAX) //generates file and puts the num and steps onto csv
{
    LRUCache* cache = create_cache(CACHE_CAPACITY);
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

        int steps = collatz_eq(randomNumber,cache);
        fprintf(fp, "%d\n", steps); 
    }

    fclose(fp);
    printf("Steps exported to %s.\n", filename);
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
