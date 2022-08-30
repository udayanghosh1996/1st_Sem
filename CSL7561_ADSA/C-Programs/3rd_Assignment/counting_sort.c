#include<stdio.h>
#include<stdlib.h>
int mx(int *arr, int n) //finding max value in the array
{
	int max,i;
	max=*(arr+0);
	for(i=1;i<n;i++)
		if(*(arr+i)>max)
			max=*(arr+i);
	return max;
}
int positioner(int *arr, int *container, int n, int max) //positioning the counts
{
	int i;
	for(i=0;i<=max;i++)
		*(container+i)=0;
	for(i=0;i<n;i++)
		container[arr[i]]++;
	return max;
}
void count_sort(int *arr,int *container, int n, int size,int min) //sorting to the original array
{
	int i,j;
	i=j=0;
	for(i;i<=size && j<n;)
	{
		if(container[i]==0)
			i++;
		else
		{
			*(arr+j)=i;
			container[i]--;
			j++;
		}
		
	}
}
int main()
{
	int i,n,*arr,*container,*arr_attri,max;
	scanf("%d",&n);
	arr_attri=(int*)malloc(2*sizeof(int));
	arr=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",arr+i);
	max=mx(arr,n);
	container=(int*)malloc((max+1)*sizeof(int));
	max=positioner(arr,container,n,max);
	count_sort(arr,container,n,max,0);
	for(i=0;i<n;i++)
		printf("%d ",*(arr+i));
	return 0;
}

