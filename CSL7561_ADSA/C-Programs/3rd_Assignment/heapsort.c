#include<stdio.h>
#include<stdlib.h>
void adjust(int *a, int i, int n)   //adjust the heap structure whenever the heap structure is destroyed
{
	int j, item;
	j=2*i;
	item=*(a+i);
	while(j<=n)
	{
		if(j<n && *(a+j)<*(a+j+1))
			j=j+1;
		if(item>=*(a+j))
			break;
		*(a+j/2)=*(a+j);
		j=2*j;
	}
	*(a+j/2)=item;
}
void heapify(int *a, int n)     //initally heapify the array
{
	int i;
	for(i=n/2;i>0;i--)
		adjust(a,i,n);
}
int* heapsort(int *a,int n)    // heapsort in accesnding order
{
	int i,*b, temp;
	b=(int*)malloc(n*sizeof(int));
	i=n;
	while(i>0)
	{
		temp=*(a+1);
		*(a+1)=*(a+i);
		adjust(a,1,i);
		*(b+i-1)=temp;
		i--;
	}
	return b;
}
int main()
{
	int n,i,*a,*b;
	scanf("%d",&n);
	a=(int*)malloc((n+1)*sizeof(int));
	b=(int*)malloc(n*sizeof(int));
	for(i=1;i<=n;i++)
		scanf("%d",a+i);
	heapify(a,n);
	b=heapsort(a,n);
	for(i=0;i<n;i++)
		printf("%d ",*(b+i));
	return 0;
}
