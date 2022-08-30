#include<stdio.h>
#include<stdlib.h>
int n;
void adjust(int *a, int i, int n)
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
void heapify(int *a, int n)
{
	int i;
	for(i=n/2;i>0;i--)
		adjust(a,i,n);
}
void del_max(int *a,int n)
{
	if(n==0)
	{
		printf("empty heap\n");
		return;
	}
	*(a+1)=*(a+n);
	adjust(a,1,n);
	return;
}
void display(int *a)
{
	int i;
	for(i=1;i<=n;i++)
		printf("%d  ",*(a+i));
	printf("\n");
}
int main()
{
	int i,*a,k;
	printf("enter the size of the heap\n");
	scanf("%d",&n);
	a=(int*)malloc((n+1)*(sizeof(int)));
	printf("enter the elements in the heap\n");
	for(i=1;i<=n;i++)
		scanf("%d",a+i);
	heapify(a,n);
	//display(a);
	printf("enter the k-th position\n");
	scanf("%d",&k);
	for(i=1;i<k;i++)
		del_max(a,n);
	printf("%d-th largest element is %d\n",k,*(a+1));
	return 0;
}
