#include<stdio.h>
#include<stdlib.h>
struct node
{
	struct node *link;
	int data;
};
struct node *start=NULL;
void ins_end(int item)
{
	struct node *temp, *ptr;
	temp=(struct node*)malloc(sizeof(struct node));
	if(temp==NULL)
	{
		printf("insufficient memory\n");
		return;
	}
	temp->data=item;
	temp->link=NULL;
	if(start==NULL)
		start=temp;
	else
	{
		ptr=start;
		while(ptr->link!=NULL)
			ptr=ptr->link;
		ptr->link=temp;
	}	
}
void del_begin()
{
	struct node *ptr;
	if(start==NULL)
	{
		printf("empty queue\n");
		return;
	}
	ptr=start;
	start=start->link;
	free(ptr);
}
void display()
{
	struct node *ptr;
	if(start==NULL)
	{
		printf("empty queue\n");
		return;
	}
	printf("Start->");
	ptr=start;
	while(ptr!=NULL)
	{
		printf("%d->",ptr->data);
		ptr=ptr->link;
	}
	printf("end\n");
}
int main()
{
	struct node *start;
	int item,n;
	while(1)
	{
		printf("Please choose any option\n");
		printf("1. Insert\t2. Delete\n3. Display\t4. Exit\n");
		scanf("%d",&n);
		switch(n)
		{
			case 1: printf("Enter the element to be inserted in the queue\n");
					scanf("%d",&item);
					ins_end(item);
					break;
			case 2: del_begin();
					break;
			case 3: display();
					break;
			case 4: exit(0);
					break;
			default: printf("Wrong input. Choose correct option\n");
		}
	}
	return 0;	
}
