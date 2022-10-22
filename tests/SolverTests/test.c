#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "solver.c"


void test_Contains(){
    int arr1[] = {2, 8, 9, 6, 5, 3, 4, 1, 7};
    int x1 = 11;

    int arr2[] = {2, 8, 9, 6, 5, 3, 4, 1, 7};
    int x2 = 2;

    int arr3[] = {2, 8, 9, 6, 5, 3, 4, 1, 7};
    int x3 = 42;

    int c1 = Contains(arr1, x1);
    printf("Answer : %i, 0 was expected \n", c1);
    int c2 = Contains(arr2, x2);
    printf("Answer : %i, 1 was expected \n", c2);
    int c3 = Contains(arr3, x3);
    printf("Answer : %i, 0 was expected \n", c3);
}


void test_IsLignValid(){
    int lign1[9] = {1, 0, 3, 9, 4, 0, 0, 2, 0};
    int lign2[9] = {0, 0, 3, 8, 7, 0, 0, 4, 3};
     
}


void test_IsColumnValid(){

}


int main(int argc, char** argv)
{
    printf("Hello SolverTests !");

 

    return EXIT_SUCCESS;
}

