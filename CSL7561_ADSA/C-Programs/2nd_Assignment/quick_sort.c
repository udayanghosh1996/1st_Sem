#include<stdio.h>
#include<stdlib.h>
int partition(int *a, int high, int low)
{
	int pivot, i, j, temp;
	pivot=*(a+low);
	j=low;
	for(i=j+1;i<=high;i++)
	{
		if(*(a+i)<pivot)
		{
			j++;
			temp=*(a+i);
			*(a+i)=*(a+j);
			*(a+j)=temp;
		}
	}
	*(a+low)=*(a+j);
	*(a+j)=pivot;
	return j;
}
void quick_sort(int *a,int high,int low)
{
	int j;
	if(low<high)
	{
		j=partition(a,high,low);
		quick_sort(a,j-1,low);
		quick_sort(a,high,j+1);
	}
	else
		return;
}
int main()
{
	int *a,i,n;
	scanf("%d",&n);
	a=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",a+i);
	quick_sort(a,n-1,0);
	for(i=0;i<n;i++)
		printf("%d ",*(a+i));
	return 0;
}
