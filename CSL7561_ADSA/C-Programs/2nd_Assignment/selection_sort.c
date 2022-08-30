#include<stdio.h>
#include<stdlib.h>
void selection_sort(int *a, int n)
{
	int i,j,temp,min;
	for(i=0;i<n;i++)
	{	
		min=i;
		for(j=i+1;j<n;j++)
			if(*(a+j)<*(a+min))
				min=j;
		temp=*(a+i);
		*(a+i)=*(a+min);
		*(a+min)=temp;
	}
	
}
int main()
{
	int *a,i,n;
	scanf("%d",&n);
	a=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",a+i);
	selection_sort(a,n);
	for(i=0;i<n;i++)
		printf("%d ",*(a+i));
	return 0;
}
