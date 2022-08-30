#include<stdio.h>
#include<stdlib.h>
int diff_max_min(int *arr, int size)
{
	int i, max, min;
	max=*arr;
	min=*arr;
	for(i=1;i<size;i++)
	{
		if(*(arr+i)>max)
			max=*(arr+i);
		if(*(arr+i)<min)
			min=*(arr+i);
	}
	//printf("%d   %d    ",max,min);
	return (max-min);
}
int main()
{
	int size, *arr, i;
	printf("enter the size of the array\n");
	scanf("%d",&size);
	arr=(int*)malloc(size*sizeof(int));
	printf("enter the elements in the array\n");
	for(i=0;i<size;i++)
		scanf("%d",arr+i);
	printf("difference betwwen the largest and smallest number in the array is: %d\n",diff_max_min(arr,size));
	return 0;
}
