#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

//TO BE DONE: argc,argv, program name, read in line by line, time the execution

//Function Declaration
void PROC(int *data, char *dest);
void add_number_to_array(int *data, int x);
void printout(int *readyPrint, char *dest);
void MERGE(int *A, int p, int q, int r);
void *MERGE_T(void *data);
void MERGE_SORT(int *A, int p, int q);
void *MERGE_SORT_T(void *data);
void change_to_int(char *array);

//General Declaration
FILE *file;
int input_data[10002];
struct data{
	int *A;
	int p,q,r;
};

//MAIN
int main(int argc, char *argv[]){

	printf("Hello");
	//Variables
	char *input_data_char;
	size_t datasize;

	//INPUT
	file = fopen(argv[1], "r");
	if (file == NULL) 
	{
  		printf("Can't open input file %s!\n", argv[1]);
  		exit(1);
	}
	while (getline(&input_data_char, &datasize, file))
	{
		clock_t start = clock();
		change_to_int(input_data_char);
		PROC(input_data, argv[2]);
		printf("This case cost %fs.", (double)(clock()-start)/1000);
	}
	fclose(file);


	return 0;
}


//FUNCTION AREA
void PROC(int *data, char *dest)
{
	struct data *args;
	args -> A = data;
	args -> r = (sizeof(data)/sizeof(int))-1;
	args -> q = (args->r)/2;
	//Pthread + Mergesort
	pthread_t sort0, sort1, merge ;
	if(pthread_create(&sort0, NULL, &MERGE_SORT_T, (void *)&args))
	{
		printf("Error entering sort0.");
	}
	args -> q ++;
	if(pthread_create(&sort1, NULL, &MERGE_SORT_T, (void *)&args))
	{
		printf("Error entering sort1.");
	}
	args -> q--;
	args -> p = 0;
	if(pthread_create(&merge, NULL, &MERGE_T, (void *)&args))
	{
		printf("Error entering merge.");
	}
	printout(data, dest);

}
void *MERGE_SORT_T(void *data)
{
	struct data *args = data; 
	MERGE_SORT(args -> A, args->p, args->r);
	return NULL;
}
void MERGE_SORT(int *A, int p, int r)
{
	int q;
	if(p<r)
	{
		q = (p+r)/2;
		MERGE_SORT(A,p,q);
		MERGE_SORT(A,q+1,r);
		MERGE(A,p,q,r);
	}
}
void printout(int *readyPrint, char *dest)
{
	int length = sizeof(readyPrint)/sizeof(int);
	int i;
	file = fopen(dest, "w");
	for(i = 0; i< length; i++)
	{
		fprintf(file, "%d ", readyPrint[i]);
	}
	fprintf(file, "\n");

}
void *MERGE_T(void *data)
{
	struct data *args = data;
	MERGE(args->A, args->p, args->q, args->r);
	return NULL;
}
void MERGE(int *A, int p, int q, int r)
{
	int i,j,k;
	int n1=q-p+1;
	int n2=r-q;
	int L[n1], R[n2];
	for(i=0; i<=n1; i++)
	{
		L[i] = A[p+i-1];
	}
	for(j=0; j<=n2; j++)
	{
		R[j] = A[q+j];
	}
	L[n1] = sizeof(int);
	R[n2] = sizeof(int);
	i = 0, j=0;
	for(k = p; k<=r; k++)
	{
		if(L[i]<=R[j])
		{
			A[k-1] = L[i];
			i++;
		}
		else
		{
			A[k-1] = R[j];
			j++;
		}
	}
}


void change_to_int(char *array)
{
	const char *inter = " ";
	char *temp;

	temp = strtok(array, inter);
	int counter = 0;
	while(temp!=NULL)
	{
		input_data[counter] = atoi(temp);
		temp = strtok(NULL, inter);
		counter ++;
	}

}