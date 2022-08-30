#include<stdio.h>
#include<stdlib.h>
struct node
{
	struct node *left;
	struct node * middle;
	int key[4];
	int pos;
	struct node *right;
	struct node *parent;
};
struct node *root=NULL;
struct node* create_node()
{
	struct node *ptr;
	ptr=(struct node*)malloc(sizeof(struct node));
	ptr->pos=0;
	ptr->left=NULL;
	ptr->middle=NULL;
	ptr->right=NULL;
	return ptr;
}
void sort(struct node *ptr, int pos)
{
	int i, j, temp;
	for(i=0;i<pos;i++)
	{
		for(j=i+1;j<pos;j++)
		{
			if(ptr->key[i]>ptr->key[j])
			{
				temp=ptr->key[i];
				ptr->key[i]=ptr->key[j];
				ptr->key[j]=temp;
			}
		}
	}
}
void insert(int val)
{
	int hold;
	struct node *temp,*ptr;
	if(root==NULL)
	{
		temp=create_node();
		temp->key[temp->pos++]=val;
		temp->parent=NULL;
		root=temp;
		return;	
	}
	ptr=root;
	if(ptr->pos<4)
	{
		ptr->key[ptr->pos++]=val;
		if(ptr->pos>1)
			sort(ptr,ptr->pos);
		return;
	}
	if(ptr->left==NULL)
	{
		temp=create_node();
		if(val<ptr->key[0])
		{
			temp->key[temp->pos++]=val;
			ptr->left=temp;
			temp->parent=ptr;
			return;
		}
		temp->key[temp->pos++]=ptr->key[0];
		ptr->key[0]=val;
		sort(ptr,ptr->pos);
		ptr->left=temp;
		temp->parent=ptr;
		return;
	}
	if(ptr->left!=NULL && ptr->left->pos!=4)
	{
		if(val<ptr->key[0])
		{
			ptr->left->key[ptr->left->pos++]=val;
			sort(ptr->left,ptr->left->pos);
			return;
		}
		ptr->left->key[ptr->left->pos++]=ptr->key[0];
		ptr->key[0]=val;
		sort(ptr,ptr->pos);
		sort(ptr->left,ptr->left->pos);
		return;
	}
	if(ptr->left->pos==4 && ptr->middle==NULL)
	{
		temp=create_node();
		temp->parent=ptr;
		ptr->middle=temp;
	}
	if(val<ptr->key[0] && ptr->left->pos==4)
	{
		hold=ptr->left->key[3];
		ptr->left->key[3]=val;
		sort(ptr->left,ptr->left->pos);
		ptr->middle->key[ptr->middle->pos++]=ptr->key[2];
		ptr->key[2]=hold;
		sort(ptr,ptr->pos);
		return;
	}
	if(val>ptr->key[0] && val<ptr->key[3])
	{
		if(val>ptr->key[2])
		{
			ptr->middle->key[ptr->middle->pos++]=val;
			sort(ptr->middle,ptr->middle->pos);
			return;
		}
		hold=ptr->key[2];
		ptr->key[2]=val;
		sort(ptr,ptr->pos);
		ptr->middle->key[ptr->middle->pos++]=hold;
		sort(ptr->middle,ptr->middle->pos);
		return;
	}
}
void inorder(struct node *ptr)
{
	//printf("inside inorder");
	int i;
	if(ptr!=NULL)
	{
		inorder(ptr->left);
		for(i=0;i<ptr->pos;i++)
		{
			//printf("in loop ");
			printf("%d ",ptr->key[i]);
			if(i==2)
				inorder(ptr->middle);
		}
		inorder(ptr->right);
	}
}
void del(int val)
{
	struct node *ptr;
	int i,flag;
	ptr=root;
	if(val<ptr->key[0])
	{
		ptr=ptr->left;
		flag=2;
	}
	for(i=0;i<ptr->pos;i++)
		if(ptr->key[i]==val && ptr==root)
		{
			flag=1;
			break;
		}
	if(flag==1)
	{
		ptr->key[i]=ptr->middle->key[ptr->middle->pos---1];
		return;
	}
	if(flag!=2)
		ptr=ptr->middle;
	for(i=0;i<ptr->pos;i++)
		if(ptr->key[i]==val)
			break;
	ptr->key[i]=ptr->key[ptr->pos-1]+1;
	sort(ptr,ptr->pos);
	ptr->pos--;
	return;	
}
int main()
{
	int n, choice,*a, i , order, val;
	scanf("%d",&order);
	scanf("%d",&n);
	a=(int*)malloc(n*sizeof(int));
	while(1)
	{
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:	for(i=0;i<n;i++)
						scanf("%d",a+i);
					for(i=0;i<n;i++)
						insert(*(a+i));
					//printf("\n");
					break;
			case 2: scanf("%d",&val);
					del(val);
					//printf("\n");
					break;
			case 3: inorder(root);
					//printf("\n");
					break;
			case 4: exit(0);
		}
	}
	return 0;
}
