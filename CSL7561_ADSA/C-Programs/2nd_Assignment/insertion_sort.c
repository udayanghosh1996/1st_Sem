#include<stdio.h>
#include<stdlib.h>
void insertion_sort(int *a, int n)
{
	int i,j,temp;
	for(i=1;i<n;i++)
	{
		temp=*(a+i);
		for(j=i;j>0&&(temp<*(a+j-1));j--)
			*(a+j)=*(a+j-1);
		*(a+j)=temp;
	}
}
int main()
{
	int *a,i,n;
	scanf("%d",&n);
	a=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",a+i);
	insertion_sort(a,n);
	for(i=0;i<n;i++)
		printf("%d ",*(a+i));
	return 0;
}
