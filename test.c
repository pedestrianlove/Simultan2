#include<stdio.h>
#include<stdlib.h>

int find_max_sum(int* price, int length, int length_needed)
{
	//We have price, length of price array
	//Hence, we can compute the maximal price possible by
	
	//Find the maximum price per volume ratio
	double max_ratio = 0;
	int max_count;
	for(int i = 0; i < length; i++)
	{
		if((double)price[i]/(i+1) > max_ratio && i<length_needed)
		{
			max_ratio = (double)price[i]/(i+1);
			max_count = i;
		}
	}

	//Try to fill up the 'length' space as much as possible with the maximal priced cake size
	return price[max_count]*(max_count+1)+find_max_sum(price,length, length_needed-max_count-1 );
}



int main()
{
	//VARIABLES USED
	int price_buffer;
	int *price_record = NULL;
	size_t counter = 0;

	//PROCESS: INPUT DATA
	while(scanf("%d", &price_buffer) != EOF)
	{
		counter++;
		price_record = realloc(price_record, (counter)*sizeof(int));
		price_record[counter-1] = price_buffer;
	}

	
	//PROCESS: TRIAL AND ERROR
	printf("%d", find_max_sum(price_record, (int)counter, (int)counter));


	return 0;
		

}
