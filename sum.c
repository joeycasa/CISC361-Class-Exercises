#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_NO_OF_ELEMENTS 100000000

static long long int sum;
static int arr[MAX_NO_OF_ELEMENTS];

int main()
{
	//let the array consists of first MAX_NO_OF_ELEMENTS integers,
	//1 to MAX_NO_OF_ELEMENTS
	for (int i = 0; i < MAX_NO_OF_ELEMENTS; i++)
		arr[i] = i + 1;
	
	//Setup timing
	clock_t start, end;
	double cpu_time_taken;
	
	start = clock();
	
	//Summing code here
	for (int j = 0; j < MAX_NO_OF_ELEMENTS; j++)
		sum += arr[j];
	
	
	//Time calculations here
	end = clock();
	cpu_time_taken = (end - start);
	printf("Total sum: %lld\n", sum);
	printf("Time taken to sum all the numbers are %lf ticks\n", cpu_time_taken);
	return 0;
}