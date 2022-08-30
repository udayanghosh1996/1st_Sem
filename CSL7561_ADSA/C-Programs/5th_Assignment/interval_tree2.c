#include<stdio.h>
#include<stdlib.h>
struct node
{
	struct node *left;
	int val;
	int dest;
	int max;
	struct node *right;
	struct node *parent;
};
struct node *root=NULL;
int get_max(int val, struct node *left,struct node *right)
{
	int max=val;
	if(left!=NULL)
		if(max<left->max)
			max=left->max;
	if(right!=NULL)
		if(max<right->max)
			max=right->max;
	return max;
}
void max(struct node *ptr)
{
	if(ptr!=NULL)
	{
		max(ptr->left);
		max(ptr->right);
		ptr->max=get_max(ptr->dest,ptr->left,ptr->right);
	}
}
void insert(int item, int dest)
{
	struct node *temp,*ptr;
	temp=(struct node*)malloc(sizeof(struct node));
	if(temp==NULL)
	{
		//printf("Insufficient memory\n");
		return;
	}
	temp->val=item;
	temp->dest=dest;
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
		ptr->left=temp;
		temp->parent=ptr;
	}
	else
	{
		ptr->right=temp;
		temp->parent=ptr;
	}
}
void in_order(struct node *ptr)
{
	if(ptr!=NULL)
	{
		in_order(ptr->left);
		printf("%d %d %d \n",ptr->val,ptr->dest,ptr->max);
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
int chk_overlap(struct node *ptr, int val,int dest)
{
	if(val<=ptr->max)
	{
		if(val>=ptr->val)
			return 1;
		else if(dest<ptr->dest && dest>ptr->val)
			return 1;
		else
			return 0;
	}
	return 0;
}
int find_overlap(struct node *ptr, int val, int dest)
{
	if(ptr!=NULL)
	{
		if(chk_overlap(ptr,val,dest))
			return 1;
		return find_overlap(ptr->left,val,dest);
		return find_overlap(ptr->right,val,dest);
		return 0;
	}
}
void del_leaf(struct node *ptr)
{
	//printf("%d\n",ptr->val);
	if(ptr->val<ptr->parent->val)
		ptr->parent->left=NULL;
	else
		ptr->parent->right=NULL;
	free(ptr);
	return;
}
void del_lco(struct node *ptr, int item)
{
	if(item<ptr->parent->val)
		ptr->parent->left=ptr->left;
	else
		ptr->parent->right=ptr->left;
	free(ptr);
	return;
}
void del_rco(struct node *ptr, int item)
{
	if(item<ptr->parent->val)
		ptr->parent->left=ptr->right;
	else
		ptr->parent->right=ptr->right;
	free(ptr);
	return;
}
void del(int item,int dest)
{
	//printf("inside del %d %d",item,dest);
	struct node *ptr, *p, *temp;
	if(root==NULL)
	{
		//printf("empty tree, nothing to delete\n");
		return;
	}
	ptr=root;
	if(ptr->val==item && ptr->dest==dest && ptr==root)
	{
		//printf("inside root del\n");
		root=NULL;
		free(ptr);
		return;
	}
	else
	{
		while(ptr->val!=item && ptr->dest!=dest && ptr!=NULL)
		{
			//printf("finding node in progress %d\n",ptr->val);
			if(item<ptr->val)
			{
				//p=ptr;
				ptr=ptr->left;
			}
			else
			{
				//p=ptr;
				ptr=ptr->right;
			}
		}
		if(ptr==NULL)
		{
			return;
		}
		//printf("after finding the node %d\n",ptr->val);
		if(ptr->left==NULL && ptr->right==NULL)
		{
			
			del_leaf(ptr);
			return;
		}
		if(ptr->left!=NULL && ptr->right==NULL)
		{
			del_lco(ptr,item);
			return;
		}
		if(ptr->left==NULL && ptr->right!=NULL)
		{
			del_rco(ptr,item);
			return;
		}
		if(ptr->left!=NULL && ptr->right!=NULL)
		{
			temp=ptr;
			//p=ptr;
			ptr=ptr->right;
			while(ptr->left!=NULL)
			{
				//p=ptr;
				ptr=ptr->left;
			}
			temp->val=ptr->val;
			temp->dest=ptr->dest;
			if(ptr->left==NULL && ptr->right==NULL)
			{
				del_leaf(ptr);
				return;
			}
			else if(ptr->left!=NULL && ptr->right==NULL)
			{
				del_lco(ptr,item);
				return;
			}
			//if(ptr->left==NULL && ptr->right!=NULL)
			else
			{
				del_rco(ptr,item);
				return;
			}
			
		}
	}
}
int main()
{
	int n,source, dest, item;
	while(1)
	{
		scanf("%d",&n);
		switch(n)
		{
			case 1: scanf("%d%d",&source,&dest);
					insert(source, dest);
					max(root);
					break;
			case 2:	if(root==NULL)
						printf("EMPTY\n");
					else
					{
					scanf("%d%d",&source,&dest);
					item=find_overlap(root,source,dest);
					if(item==1)
						printf("Yes\n");
					else
						printf("No\n");
					}
					break;
			case 3: exit(0);
		}
	}
	return 0;
}

