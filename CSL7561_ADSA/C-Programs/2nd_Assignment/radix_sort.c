#include<stdio.h>
#include<stdlib.h>
struct node
{
	int data;
	struct node *link;
};
struct node a[19];
int maxdigit(int *a, int n)
{
	int i,dc=0,max;
	if(*a>0)
		max=*a;
	else
		max=-*a;		
	for(i=1;i<n;i++)
		if(*(a+i)>0)
			if(*(a+i)>max)
				max=*(a+i);
		else
			if(-*(a+i)>max)
				max=-*(a+i);
	while(max!=0)
	{
		dc++;
		max=max/10;	
	}
	return dc;
}
void ins_end(int digit, int item)
{
	struct node *temp, *ptr;
	temp=(struct node*)malloc(sizeof(struct node));
	if(temp==NULL)
	{
		return;
	}
	temp->data=item;
	temp->link=NULL;
	ptr=(a+digit+9);
	if(ptr->link==NULL)
	{
		(a+digit+9)->link=temp;
		return;
	}
	while(ptr->link!=NULL)
		ptr=ptr->link;
	ptr->link=temp;
	
}
int del_begin(int j)
{
	struct node *ptr;
	int val;
	if((a+j)->link==NULL)
	{
		return;
	}
	ptr=(a+j)->link;
	(a+j)->link=(a+j)->link->link;
	val=ptr->data;
	free(ptr);
	return val;
}
void insert(int *b, int n, int divisor)
{
	int i;
	for(i=0;i<n;i++)
		ins_end(((*(b+i)/divisor)%10),*(b+i));
}
void del(int *b, int n)
{
	int i,j=0;
	struct node *p=(a+j);
	for(i=0;i<n && j<19;i++)
	{
		if(p->link!=NULL)
		{
			*(b+i)=del_begin(j);
		}
		else
		{
			j++;
			p=(a+j);
			i--;
		}
	}
}
radix_sort(int *a, int n)
{
	int dc,*b,i,divisor=1;
	dc=maxdigit(a,n);
	b=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		*(b+i)=*(a+i);
	for(i=1;i<=dc;i++)
	{
		insert(b,n,divisor);
		del(b,n);
		divisor=divisor*10;
	}
	for(i=0;i<n;i++)
		*(a+i)=*(b+i);
}
int main()
{
	int *a,i,n;
	scanf("%d",&n);
	a=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",a+i);
	radix_sort(a,n);
	for(i=0;i<n;i++)
		printf("%d ",*(a+i));
	return 0;
}
