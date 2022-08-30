#include<stdio.h>
#include<stdlib.h>
struct node
{
	struct node *left;
	int val;
	struct node *right;
};
struct node *root=NULL;
void insert(int item)
{
	struct node *temp,*ptr;
	temp=(struct node*)malloc(sizeof(struct node));
	if(temp==NULL)
	{
		printf("Insufficient memory\n");
		return;
	}
	temp->val=item;
	temp->left=NULL;
	temp->right=NULL;
	if(root==NULL)
	{
		root=temp;
		return;
	}
	ptr=root;
	while(1)
	{
		if(ptr->val==item)
		{
			printf("item already existed in the tree, can't be inserted furthermore\n'");
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
		ptr->left=temp;
	else
		ptr->right=temp;
}
void search(int item)
{
	struct node *ptr;
	if(root==NULL)
	{
		printf("empty tree\n");
		return;
	}
	ptr=root;
	while(ptr!=NULL && ptr->val!=item)
	{
		if(item<ptr->val)
			ptr=ptr->left;
		else
			ptr=ptr->right;
	}
	if(ptr==NULL)
		printf("%d is not present in the tree\n",item);
	else
		printf("%d is present in the tree\n",item);
}
void in_order(struct node *ptr)
{
	if(ptr!=NULL)
	{
		in_order(ptr->left);
		printf("%d ",ptr->val);
		in_order(ptr->right);
	}
}
void pre_order(struct node *ptr)
{
	if(ptr!=NULL)
	{
		printf("%d ",ptr->val);
		pre_order(ptr->left);
		pre_order(ptr->right);
	}
}
void post_order(struct node *ptr)
{
	if(ptr!=NULL)
	{
		post_order(ptr->left);
		post_order(ptr->right);
		printf("%d ",ptr->val);
	}
}
void del_leaf(struct node *p, struct node *ptr)
{
	if(ptr->val<p->val)
		p->left=NULL;
	else
		p->right=NULL;
	free(ptr);
	return;
}
void del_lco(struct node *p, struct node *ptr, int item)
{
	if(item<p->val)
		p->left=ptr->left;
	else
		p->right=ptr->left;
	free(ptr);
	return;
}
void del_rco(struct node *p, struct node *ptr, int item)
{
	if(item<p->val)
		p->left=ptr->right;
	else
		p->right=ptr->right;
	free(ptr);
	return;
}
void del(int item)
{
	struct node *ptr, *p, *temp;
	if(root==NULL)
	{
		printf("empty tree, nothing to delete\n");
		return;
	}
	ptr=root;
	if(ptr->val==item && ptr->left==NULL && ptr->right==NULL )
	{
		root=NULL;
		free(ptr);
		return;
	}
	else
	{
		while(ptr->val!=item && ptr!=NULL)
		{
			if(item<ptr->val)
			{
				p=ptr;
				ptr=ptr->left;
			}
			else
			{
				p=ptr;
				ptr=ptr->right;
			}
		}
		if(ptr==NULL)
		{
			printf("item not present in the tree\n");
			return;
		}
		if(ptr->left==NULL && ptr->right==NULL)
		{
			del_leaf(p,ptr);
			return;
		}
		if(ptr->left!=NULL && ptr->right==NULL)
		{
			del_lco(p,ptr,item);
			return;
		}
		if(ptr->left==NULL && ptr->right!=NULL)
		{
			del_rco(p,ptr,item);
			return;
		}
		if(ptr->left!=NULL && ptr->right!=NULL)
		{
			temp=ptr;
			p=ptr;
			ptr=ptr->right;
			while(ptr->left!=NULL)
			{
				p=ptr;
				ptr=ptr->left;
			}
			temp->val=ptr->val;
			if(ptr->left==NULL && ptr->right==NULL)
			{
				del_leaf(p,ptr);
				return;
			}
			else if(ptr->left!=NULL && ptr->right==NULL)
			{
				del_lco(p,ptr,item);
				return;
			}
			//if(ptr->left==NULL && ptr->right!=NULL)
			else
			{
				del_rco(p,ptr,item);
				return;
			}
			
		}
	}
}
int main()
{
	int n,item;
	while(1)
	{
		printf("Please choose any option\n");
		printf("1. Insert\t2. Search\t3. Delete\n4. Inorder traverse\t5. Preorder traverse\t6. Postorder traverse\n7. Exit\n");
		scanf("%d",&n);
		switch(n)
		{
			case 1: printf("enter the item to be inserted\n");
					scanf("%d",&item);
					insert(item);
					break;
			case 2: printf("enter the item to be searched\n");
					scanf("%d",&item);
					search(item);
					break;
			case 3:	printf("enter the item to be deleted\n");
					scanf("%d",&item);
					del(item);
					break;
			case 4: in_order(root);
					break;
			case 5: pre_order(root);
					break;
			case 6: post_order(root);
					break;
			case 7: exit(0);
			default: printf("Wrong input. Please choose correct option\n");
		}
	}
	return 0;
}

