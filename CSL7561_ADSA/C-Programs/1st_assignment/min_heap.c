#include<stdio.h>
#include<stdlib.h>
int n,size;
void adjust(int *a, int i, int n)
{
	int j, item;
	j=2*i;
	item=*(a+i);
	while(j<=n)
	{
		if(j<n && *(a+j)>*(a+j+1))
			j=j+1;
		if(item<=*(a+j))
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
void ins(int *a,int item)
{
	n++;
	if(n>size)
	{
		printf("heap is full, can't insert'\n");
		n--;
		return;
	}
	*(a+n)=item;
	printf("n=%d\n",n);
	heapify(a,n);
	return;
}
void del(int *a)
{
	if(n==0)
	{
		printf("empty heap, can't delete\n'");
		return;
	}
	printf("deleted item is %d\n",*(a+1));
	*(a+1)=*(a+n);
	n--;
	if(n>1)
		heapify(a,n);
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
	int i, item, *a, k;
	printf("enter max size of the heap\n");
	scanf("%d",&size);
	a=(int*)malloc((size+1)*sizeof(int));
	printf("how many elements want to insert in the heap initially\n");
	scanf("%d",&n);
	printf("enter the elements\n");
	for(i=1;i<=n;i++)
		scanf("%d",a+i);
	heapify(a,n);
	while(1)
	{
		printf("choose any option\n1. Insert\t2. Delete\n3. Display\t4. Exit\n");
		scanf("%d",&k);
		switch(k)
		{
			case 1: printf("enter the element to be inserted\n");
					scanf("%d",&item);
					ins(a,item);
					display(a);
					break;
			case 2: del(a);
					break;
			case 3: display(a);
					break;
			case 4: exit(0);
					break;
			default: printf("wrong input. choose correctly\n");
		}
	}
	return 0;
}
