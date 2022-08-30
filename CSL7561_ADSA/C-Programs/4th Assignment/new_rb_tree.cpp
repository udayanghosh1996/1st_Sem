#include<stdio.h>
#include<stdlib.h>
struct node
{
	struct node *parent;
	int val;
	char color;
	struct node *left;
	struct node *right;
};
struct node *root=NULL;
void in_order(struct node *ptr) // function to perform inorder traversal of the tree
{
	if(ptr!=NULL)
	{
		in_order(ptr->left);
		printf("%d%c ",ptr->val,ptr->color);
		in_order(ptr->right);
	}
}

void search(int item)
{
	struct node *ptr;
	if(root==NULL)
	{
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
		printf("ABSENT\n");
	else
		printf("PRESENT\n");
}
//void pre_order(struct node *ptr) // function to perform preorder traversal of the tree
//{
//	if(ptr!=NULL)
//	{
//		printf("%d ",ptr->val);
//		pre_order(ptr->left);
//		pre_order(ptr->right);
//	}
//}
int get_black_depth(struct node *pointer) //function to get black depth of an external node
{
	int depth=0;
	struct node *p;
	p=pointer;
	while(p!=NULL)
	{
		if(p->color=='B')
			depth++;
		p=p->parent;
	}
	return depth;
}
struct node* get_parent_sibling(struct node *pointer) // function to get parent's sibling of a node
{
	struct node *p;
	int val;
	p=pointer;
	val=p->val;
	if(p->parent!=root)
	{
		if(p->parent->val<p->parent->parent->val)
		{
			if(p->parent->parent->right!=NULL){
			return p->parent->parent->right;
			}
			else
				return NULL;
		}	
		else if(p->parent->val>p->parent->parent->val)
		{
			if(p->parent->parent->left!=NULL){
			return p->parent->parent->left;
			}
			else 
				return NULL;
		}
		else
			return NULL; 
	}
	else
		return NULL;
}
void recolor(struct node *pointer) // function to perform recolor operation
{
	if(pointer->color=='R')
		pointer->color='B';
	else
		pointer->color='R';
}
struct node* ll_rotation(struct node *pointer) // function to perform ll rotation
{
	struct node *p,*lchild;
	p=pointer;
	lchild=p->left;
	lchild->parent=p->parent;
	if(p!=root)
	{
		if(p->val>p->parent->val)
			p->parent->right=lchild;
		else
			p->parent->left=lchild;
	}
	p->left=lchild->right;
	lchild->right=p;
	p->parent=lchild;
	return lchild;
}
struct node* rr_rotation(struct node *pointer) // function to perform rr rotation
{
	struct node *p,*rchild;
	p=pointer;
	rchild=p->right;
	rchild->parent=p->parent;
	if(p!=root)
	{
		if(p->val>p->parent->val)
			p->parent->right=rchild;
		else
			p->parent->left=rchild;
	}
	p->right=rchild->left;
	rchild->left=p;
	p->parent=rchild;
	printf("exiting rr ");
	return rchild;
}
struct node* lr_rotation(struct node *pointer) // function to perform lr rotation
{
	printf("inside lr");
	struct node *p,*par,*child;
	par=pointer->parent;
	child=pointer->right->left;
	if(pointer!=root)
	{
		pointer->right->parent=par;
		par->left=pointer->right;
	}
	pointer->parent=par->left;
	par->left->left=pointer;
	pointer->right=child;
	p=par->left;
	printf("redirecting ll");
	//p=rr_rotation(pointer);
	p=ll_rotation(p->parent);
	return p;
}
struct node* rl_rotation(struct node *pointer) // function to perform rl rotaiton
{
	printf("inside rl");
	struct node *p,*par,*child;
	par=pointer->parent;
	child=pointer->left->right;
	if(pointer!=root)
	{
		pointer->left->parent=par;
		par->right=pointer->left;
	}
	pointer->parent=par->right;
	par->right->right=pointer;
	pointer->left=child;
	p=par->right;
	printf(" %d redirecting rr",p->parent->val);
	p=rr_rotation(p->parent);
	printf("%d ",p->parent->val);
	return p;
}
int get_rotation(struct node *pointer) // function to get which type of rotation is needed
{
	int rot=0;
	struct node *p;
	p=pointer;
	if(p->val<p->parent->val)
	{
		rot=1;
		if(p->parent->val>p->parent->parent->val)
			rot+=3;
	}
	else
	{
		rot=2;
		if(p->parent->val<p->parent->parent->val)
			rot+=1;
	}
	return rot;
}
void insert(int value) //overall insert function
{
	struct node *temp,*ptr;
	temp=(struct node*)malloc(sizeof(struct node));
	temp->val=value;
	temp->left=NULL;
	temp->right=NULL;
	if(root==NULL)
	{
		temp->color='B';
		temp->parent=NULL;
		root=temp;
		return;
	}
	temp->color='R';
	ptr=root;
	while(1)
	{
		if(ptr->val==value)
		{
			return;
		}
		if(value<ptr->val)
		{
			if(ptr->left!=NULL)
				ptr=ptr->left;
			else
			{
				ptr->left=temp;
				break;
			}
		}
		else
		{
			if(ptr->right!=NULL)
				ptr=ptr->right;
			else
			{
				ptr->right=temp;
				break;
			}
		}
		
	}
	temp->parent=ptr;
	if(temp->parent->color=='B')
		return;
	ptr=temp;
	while(ptr!=root)
	{
		if(get_parent_sibling(ptr)==NULL||get_parent_sibling(ptr)->color=='B')
		{
			if(get_rotation(ptr)==1) // when a node has left child only and new node is inserted as a left child of it's child node
			{
				ptr=ll_rotation(ptr->parent->parent);
				if(root->parent!=NULL)
					root=root->parent;
				if(ptr==root)
					ptr->color='B';
				else
					recolor(ptr);
				if(ptr->right!=NULL)
					recolor(ptr->right);
			}
			else if(get_rotation(ptr)==2) // when a node has right child only and new node is inserted as a right child of it's child node
			{
				ptr=rr_rotation(ptr->parent->parent);
				if(root->parent!=NULL)
					root=root->parent;
				if(ptr==root)
					ptr->color='B';
				else
					recolor(ptr);
				if(ptr->left!=NULL)
					recolor(ptr->left);
			}
			else if(get_rotation(ptr)==3)
			{
				ptr=lr_rotation(ptr->parent); // when a node has left child only and new node is inserted as a right child of it's child node
				if(ptr==root)
					ptr->color='B';
				else
					recolor(ptr);
				if(ptr->right!=NULL)
					recolor(ptr->right);
			}
			else if(get_rotation(ptr)==4) // when a node has right child only and new node is inserted as a left child of it's child node
			{
				ptr=rl_rotation(ptr->parent);
				if(ptr==root)
					ptr->color='B';
				else
					recolor(ptr);
				if(ptr->left!=NULL)
					recolor(ptr->left);
				
			}
			else
				continue;
		}
		else // when there is no parent sibling or color of parent sibling is red
		{
			recolor(ptr->parent);
			recolor(get_parent_sibling(ptr));
			if(ptr->parent->parent!=root)
				recolor(ptr->parent->parent);
			else 
				return;
			ptr=ptr->parent;
		}
		if(root->parent!=NULL)
			root=root->parent;
	}
	
}
struct node* get_sibling(struct node *pointer) //function to get sibling
{
	struct node *ptr;
	ptr=pointer;
	if(ptr->parent!=NULL)
	{
		if(ptr->val<ptr->parent->val)
			return ptr->parent->right;
		else
			return ptr->parent->left;
	}
	else
		return NULL;
}
void del_leaf(struct node *ptr) // function to delete leaf node
{
	if(ptr->val<ptr->parent->val)
		ptr->parent->left=NULL;
	else
		ptr->parent->right=NULL;
	free(ptr);
	return ;
}
struct node* del_lco(struct node *ptr) //function to delete a node having left child only
{
	struct node *temp;
	temp=ptr->parent;
	if(ptr->val<temp->val)
	{
		temp->left=ptr->left;
		free(ptr);
		return temp;
	}
	else
	{
		temp->right=ptr->left;
		free(ptr);
		return temp;
	}
}
struct node* del_rco(struct node *ptr) //function to delete a node having right child only
{
	struct node *temp;
	temp=ptr->parent;
	if(ptr->val<temp->val)
	{
		temp->left=ptr->right;
		free(ptr);
		return temp;
	}
	else
	{
		temp->right=ptr->right;
		free(ptr);
		return temp;
	}
}
int is_red_node(struct node *pointer)
{
	struct node *p;
	p=pointer;
	if(p!=NULL)
	{
		if(p->color=='R')
			return 0;
		else 
			return 1;
	}
	else
		return 1;
}
void del_case_2_1(struct node *parent, struct node *sibling) //funtion to rearrancge when node to deleted has red parent, black sibling and sibling has at least 1 red child
{
	struct node *sib_child,*p;
	if(sibling->val<parent->val)
	{
		if(sibling->right!=NULL && is_red_node(sibling->right))
		{
			p=lr_rotation(sibling);
			recolor(p);
		}
		else
		{
			p=ll_rotation(parent);
			recolor(p);
			recolor(p->left);
			recolor(p->right);
		}
	}
	else
	{
		if(sibling->left!=NULL && is_red_node(sibling->left))
		{
			p=rl_rotation(sibling);
			recolor(p);
		}
		else
		{
			p=rr_rotation(parent);
			recolor(p);
			recolor(p->left);
			recolor(p->right);
		}
	}
}
void del_case_2_2(struct node *parent, struct node *sibling) // function to rearrange when node to be deleted has red parent, black sibling and sibling doesn't have any red child
{
	recolor(parent);
	recolor(sibling);
}
void del_case_2_3(struct node *parent, struct node *sibling) // function to rearrange when node to be deleted has black parent and red sibling
{
	struct node *par, *sib, *p;
	if(sibling->val<parent->val)
	{
		p=rr_rotation(parent);
		recolor(p->left);
		recolor(p);
		par=p->left;
		sib=p->left->right;
	}
	else
	{
		p=ll_rotation(parent);
		recolor(p->right);
		recolor(p);
		par=p->right;
		sib=p->right->left;
	}
	if((sib->left!=NULL && is_red_node(sib->left))||(sib->right!=NULL && is_red_node(sib->right)))
		del_case_2_1(par,sib);
	else
		del_case_2_1(par,sib);
}
void del_case_2_4(struct node *parent, struct node *sibling) //function to rearrange when node to be deleted has black parent, black sibling and sibling has at least 1 red child
{
	struct node *p;
	if(sibling->val<parent->val)
	{
		if(sibling->left!=NULL && is_red_node(sibling->left))
		{
			p=ll_rotation(parent);
			recolor(p);
		}
		else
		{
			p=lr_rotation(sibling);
			recolor(p);
		}
	}
	else
	{
		if(sibling->right!=NULL && is_red_node(sibling->right))
		{
			p=rr_rotation(parent);
			recolor(p);
		}
		else
		{
			p=rl_rotation(sibling);
			recolor(p);
		}
	}
}
void del_case_2_5(struct node *parent, struct node *sibling) //function to rearrange when node to deleted has black parent, black sibling and sibling doesn't have any red child
{
	struct node *par,*sib;
	recolor(sibling);
	if(parent->parent==NULL)
		return;
	sib=get_parent_sibling(parent);
	par=parent->parent;
	if(!is_red_node(par))
	{
		if(!is_red_node(sib))
		{
			if(is_red_node(sib->left)||is_red_node(sib->right))
				del_case_2_4(par,sib);
			else
				del_case_2_5(par,sib);
		}
		else
			del_case_2_3(par,sib);
	}
	else
	{
		if(is_red_node(sib->left)||is_red_node(sib->right))
			del_case_2_1(par,sib);
		else
			del_case_2_2(par,sib);
	}
	
}
int find(int item)
{
	struct node *ptr;
	if(root==NULL)
	{
		return 0;
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
		return 0;
	return 1;
}
void del(int item) //overall delete function
{
	struct node *ptr, *p, *temp,*par,*sib;
	if(root==NULL)
	{
		return;
	}
	if(find(item))
	{
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
					ptr=ptr->left;
				}
				else
				{
					ptr=ptr->right;
				}
			}
			if(ptr==NULL)
			{
				printf("ABSENT\n");
				return;
			}
			if(ptr->left==NULL && ptr->right==NULL) // node is a leaf node
			{
				del_leaf(ptr);
				return;
			}
			if(ptr->left!=NULL && ptr->right==NULL) //node is having left child only
			{
				p=del_lco(ptr);
				recolor(p);
				return;
			}
			if(ptr->left==NULL && ptr->right!=NULL) //node is havig right child only
			{
				p=del_rco(ptr);
				recolor(p);
				return;
			}
			if(ptr->left!=NULL && ptr->right!=NULL) // if the node is an internal node, preprocessing
			{
				temp=ptr;
				ptr=ptr->right;
				while(ptr->left!=NULL)
				ptr=ptr->left;
				temp->val=ptr->val;
			}
			if(ptr->left==NULL && ptr->right==NULL && ptr->color=='R' ) // node is a leaf node and color is red
			{
				del_leaf(ptr);
				return;
			}
			if(ptr->left!=NULL && ptr->right==NULL && ptr->color=='B' && ptr->left->color=='R') //node is having left child only and color is red
			{
				p=del_lco(ptr);
				if(p!=root)
					recolor(p);
				return;
			}
			if(ptr->left==NULL && ptr->right!=NULL && ptr->color=='B' && ptr->right->color=='R') //node is havig right child only and color is red
			{
				p=del_rco(ptr);
				if(p!=root)
					recolor(p);
				return;
			}
			if(ptr->left==NULL && ptr->right==NULL && ptr->color=='B') // node is a leaf node and color is black
			{
				par=ptr->parent;
				sib=get_sibling(ptr);
				del_leaf(ptr);
				if(is_red_node(par) && !is_red_node(sib))
				{
					if((sib->left!=NULL && is_red_node(sib->left))||(sib->right!=NULL && is_red_node(sib->right))) // rearrancge when node to deleted has red parent, black sibling and sibling has at least 1 red child
						del_case_2_1(par,sib);
					else							// rearrange when node to be deleted has red parent, black sibling and sibling doesn't have any red child
						del_case_2_2(par,sib);
					if(root->parent!=NULL)
						root=root->parent;
					return;
				}
				if(!is_red_node(par) && is_red_node(sib)) // rearrange when node to be deleted has black parent and red sibling
				{
					del_case_2_3(par,sib);
					if(root->parent!=NULL)
						root=root->parent;
					return;
				}
				if(!is_red_node(par) && !is_red_node(sib)) //rearrange when node to be deleted has black parent, black sibling and sibling has at least 1 red child
				{
					if((sib->left!=NULL && is_red_node(sib->left))||(sib->right!=NULL && is_red_node(sib->right)))
					{
						del_case_2_4(par,sib);
					}
					else
						del_case_2_5(par,sib);
					if(root->parent!=NULL)
						root=root->parent;
					return;
				}
			}
		}
	}
	else
	{
		printf("ABSENT\n");
		return;
	}
}

int main()
{
	int n,item;
	while(1)
	{
		scanf("%d",&n);
		switch(n)
		{
			case 1: scanf("%d",&item);
					insert(item);
					break;
			case 3: if(root==NULL)
						printf("EMPTY\n");
					else
					{
						scanf("%d",&item);
						search(item);
					}
					break;
			case 2:	if(root==NULL)
						printf("EMPTY\n");
					else
					{
					scanf("%d",&item);
					del(item);
					}
					break;
			case 4: in_order(root);
					printf("\n");
					break;
			case 5: exit(0);
		}
	}
	return 0;
}

