#include<stdio.h>
#include<stdlib.h>
struct node
{
	struct node *link;
	int data;
};
struct node *start=NULL;
void ins_head(int item)
{
	struct node *temp;
	temp=(struct node*)malloc(sizeof(struct node));
	if(temp==NULL)
	{
		printf("insufficient memory\n");
		return;
	}
	temp->data=item;
	temp->link=start;
	start=temp;
	
}
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
void ins_any(int pos, int item)
{
	struct node *temp, *ptr;
	int i;
	temp=(struct node*)malloc(sizeof(struct node));
	if(temp==NULL)
	{
		printf("insufficient memory\n");
		return;
	}
	temp->data=item;
	if(start==NULL && pos!=1)
	{
		printf("as linked list is empty, insert at position %d is not possible\n");
		free(temp);
		return;
	}
	else
	{
		if(pos==1)	
		{
			temp->link=start;
			start=temp;
		}
		else if(pos<1)
		{
			printf("Invalid position\n");
			free(temp);
			return;
		}
		else
		{
			ptr=start;
			for(i=1;i<pos-1 && ptr!=NULL; i++)
				ptr=ptr->link;
			if(ptr==NULL)
			{
				printf("invalid position\n");
				free(temp);
				return;
			}
			temp->link=ptr->link;
			ptr->link=temp;
		}
	}
		
}
void del_begin()
{
	struct node *ptr;
	if(start==NULL)
	{
		printf("empty linked-list\n");
		return;
	}
	ptr=start;
	start=start->link;
	free(ptr);
}
void del_end()
{
	struct node *ptr, *temp;
	if(start==NULL)
	{
		printf("empty linked-list\n");
		return;
	}
	ptr=start;
	if(start->link==NULL)
	{
		start=start->link;
		free(ptr);
		return;
	}
	while(ptr->link->link!=NULL)
		ptr=ptr->link;
	temp=ptr->link;
	ptr->link=NULL;
	free(temp);	
}
void del_any(int pos)
{
	struct node *ptr, *temp;
	int i=0;
	if(start==NULL)
	{
		printf("empty linked-list\n");
		return;
	}
	if(pos<1)
	{
		printf("invalid position\n");
		return;
	}
	ptr=start;
	for(i=1;i<pos-1 && ptr->link!=NULL; i++)
		ptr=ptr->link;
	if(ptr->link==NULL)
	{
		printf("invalid position\n");
		return;
	}
	temp=ptr->link;
	ptr->link=ptr->link->link;
	free(temp);
}
void search(int item)
{
	struct node *ptr;
	int i;
	if(start==NULL)
	{
		printf("empty linked-list\n");
		return;
	}
	ptr=start;
	i=1;
	while(ptr->data!=item && ptr->link!=NULL)
	{
		ptr=ptr->link;
		i++;
	}
	if(ptr->data==item)
	{
		printf("%d found at the position %d in the linked-list\n",item,i);
	}
	else
		printf("%d is not present in the linked-list\n",item);
}
void display()
{
	struct node *ptr;
	if(start==NULL)
	{
		printf("empty linked-list");
		return;
	}
	printf("Start->");
	ptr=start;
	while(ptr!=NULL)
	{
		printf("%d->",ptr->data);
		ptr=ptr->link;
	}
	printf("null\n");
}
int main()
{
	int n, item, pos;
	while(1)
	{
		printf("Please choose any option\n");
		printf("1. Insert at head\t2. Insert at end\t3. Insert at any position\n");
		printf("4. Delete from head\t5. Delete from End\t6. Delete from any position\n");
		printf("7. Search item in Linked-list\t8. Display Linked-list\t 9. Exit\n");
		scanf("%d",&n);
		switch(n)
		{
			case 1: printf("enter the item to be inserted\n");
					scanf("%d",&item);
					ins_head(item);
					display();
					break;
			case 2: printf("enter the item to be inserted\n");
					scanf("%d",&item);
					ins_end(item);
					display();
					break;
			case 3: printf("enter the item to be inserted\n");
					scanf("%d",&item);
					printf("enter the position item to be inserted\n");
					scanf("%d",&pos);
					ins_any(pos,item);
					display();
					break;
			case 4: del_begin();
					display();
					break;
			case 5: del_end();
					display();
					break;
			case 6:	printf("enter the postion, item to be deleted\n");
					scanf("%d",&pos);
					del_any(pos);
					display();
					break;
			case 7:	printf("enter the item to be searched\n");
					scanf("%d",&item);
					search(item);
					display();
					break;
			case 8:	display();
					break;
			case 9: exit(0);
			default:	printf("wrong input given\n");
		}
	}
	return 0;
}
