#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int collatz_eq(int n)
{   
    printf("%d ", n);
    int term = n;
    if (n == 1){
        return 1;
    }
    else if (n % 2 == 0){
        term = n/2;
    }
    else if (n % 2 == 1){
        term = 3*n + 1;
    }
    return collatz_eq(term);
}
int test_collaz(int N, int MIN, int MAX){
    int i;
    for (i = 0; i < N; i++) {
        int randomNumber = (rand() % (MAX - MIN + 1)) + MIN;
        printf("Collatz sequence for %d: \n", randomNumber);
        int collatz = collatz_eq(randomNumber);
        printf("\n");
    }
    return 0;
}


int main(int argc, char *argv[])
{
    if (argc != 4){
        printf("Usage: %s <N> <MIN> <MAX>\n", argv[0]);
       return 1;  
    }

    int N = atoi(argv[1]);
    int MIN = atoi(argv[2]);
    int MAX = atoi(argv[3]);

    srand(time(NULL)); 


    test_collaz(N, MIN, MAX);

    



    return 0;




    
    



    
}
