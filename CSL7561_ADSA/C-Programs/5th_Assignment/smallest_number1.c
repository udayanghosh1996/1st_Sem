#include<stdio.h>
#include<stdlib.h>
struct node
{
	struct node *left;
	int val;
	//int in_ord_val;
	struct node *parent;
	struct node *right;
};
struct node *root=NULL;
void insert(int item)
{
	struct node *temp,*ptr;
	temp=(struct node*)malloc(sizeof(struct node));
	if(temp==NULL)
	{
		//printf("Insufficient memory\n");
		return;
	}
	temp->val=item;
	//temp->in_ord_val=item;
	temp->left=NULL;
	temp->right=NULL;
	if(root==NULL)
	{
		temp->parent=NULL;
		root=temp;
		return;
	}
	ptr=root;
	while(1)
	{
		if(ptr->val==item)
		{
			//printf("item already existed in the tree, can't be inserted furthermore\n'");
			return;
		}
		if(item<ptr->val)
		{
			if(ptr->left!=NULL)
				ptr=ptr->left;
			else
				break;
		}
		else
		{
			if(ptr->right!=NULL)
				ptr=ptr->right;
			else
				break;
		}
		
	}
	if(item<ptr->val)
	{
		temp->parent=ptr;
		ptr->left=temp;
	}
	else
	{
		temp->parent=ptr;
		ptr->right=temp;
	}
}
int smallest(struct node *ptr, int low, int high)
{
	while(ptr!=NULL && ptr->val<=low)
		ptr=ptr->right;
	if(ptr==NULL)
		return;
	while(ptr!=NULL && ptr->val<=high)
	{
		if(ptr->parent->val+1!=ptr->val)
			return ptr->parent->val+1;
		ptr=ptr->right;
	}
	return;
}
int main()
{
	int n,*a,item,e,s,i,smalles;
	scanf("%d",&n);
	scanf("%d%d",&s,&e);
	a=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",a+i);
	for(i=0;i<n;i++)
		insert(*(a+i));
	smalles=smallest(root,s,e);
	printf("%d",smalles);
	return 0;
}
