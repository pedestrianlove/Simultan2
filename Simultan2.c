#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

//TO BE DONE: argc,argv, program name, read in line by line, time the execution

//Parameters
char outputFile[] = "output.txt";
char inputFile[] = "testcase.txt";
FILE *reader;
FILE *writer;
struct arg_struct {
    int *data;
    int *start;
    int *end;
};
struct arg_struct_1{
	int *merge;
	int *start;
	int *avg;
	int *end;
};
struct arg_struct *arg1;
struct arg_struct_1 *arg2;
//FUNCTION DECLARED

////Merge sort
void mergesort_c(struct arg_struct *arg)
{
	int *avg = NULL;
	struct arg_struct *tmp;
	struct arg_struct_1 *tmp1=NULL;
	if(arg->start < arg->end)
	{
		*avg=(*(arg->start)+*(arg->end))/2;
		tmp = arg;
		mergesort_c(tmp);
		tmp->start ++;
		mergesort_c(tmp);
		tmp1 -> merge = tmp->data;
		tmp1 -> start = tmp->start;
		tmp1 -> end = tmp -> end;
		tmp1 -> avg = avg;

		merge_c(tmp1);
	}
}

////MERGE
void merge_c(struct arg_struct_1 *arg)
{
	int a = (*arg->avg) - (*arg->start) +1;
	int b = (*arg->end) - (*arg->avg);
	int Left[a], Right[b];
	for(int i=1; i<=a; i++)
	{
		Left[i] = arg->merge[*arg->start+i-1];
	}
	for(int j=1; j<=b; j++)
	{
		Right[j] = arg->merge[*arg->avg+j];
	}
	Left[a+1]=sizeof(int);
	Right[b+1]=sizeof(int);
	int i=1, j=1, k=1        ;
	for(k = *(arg->avg); k<=*(arg->end); k++)
	{
		if(Left[i]<=Right[j])
		{
			arg->merge[k] = Left[i];
			i = i + 1;
		}
		else
		{
			arg->merge[k] = Right[j];
			j = j + 1;
		}
	}
}
////PRINTOUT OUTCOME
void printout(int *readyprint)
{
	int lengthy = sizeof(readyprint)/sizeof(int);
	writer = fopen(outputFile, "w");
	char space = "s";
	if(writer ==NULL)
	{
		printf("Can't open output file %s!\n", outputFile);
	}
	for(int i=0; i<lengthy; i++)
	{
		fprintf("%d", readyprint[i]);
		if(i != (lengthy-1))
		{
			fprintf("%s",space);
		}
		else
		{
			fprint("\n");
		}
	}
}

//MAIN
int main()
{
	//Initialization
	int *input_data;
	pthread_t sorting0;
	pthread_t sorting1;
	pthread_t merging;
	int length ;

	//INPUT
	reader = fopen(inputFile, "r");
	if (reader == NULL) 
	{
  		printf("Can't open input file %s!\n", inputFile);
  		exit(1);
	}
	while (fscanf(reader, "%d", input_data) != EOF)
	{
		length= sizeof(input_data)/sizeof(int);
		//INPUT PARAMETER
		arg1 -> data = input_data;
		arg1 -> start = input_data+0;
		arg1 -> end = input_data+(length-1);

		arg2 -> merge = input_data;
		arg2 -> start = input_data+1;
		arg2 -> avg = input_data+(length-1)/2;
		arg2 -> end = input_data+(length-1);
		//MERGE SORT 1
		pthread_create(&sorting0, NULL, mergesort_c, arg1);
		if(pthread_create(&sorting0, NULL, mergesort_c, arg1)) 
		{
			printf("Error creating thread sorting0\n");
			return 1;
		}
		//MERGE SORT 2
		arg1->start ++;
		pthread_create(&sorting1, NULL, mergesort_c, arg1);
		if(pthread_create(&sorting1, NULL, mergesort_c, arg1))
		{
			printf("Error creating thread sorting1\n");
			return 1;
		}

		pthread_join(sorting0, NULL);
		pthread_join(sorting1, NULL);
		pthread_create(&merging, NULL, merge_c, arg2);
		if(pthread_create(&merging, NULL, merge_c, arg2))
		{
			printf("Error creating thread merging\n");
			return 1;
		}
		pthread_join(merging, NULL);
		printout(input_data);

		return 0;
	}




	

}
