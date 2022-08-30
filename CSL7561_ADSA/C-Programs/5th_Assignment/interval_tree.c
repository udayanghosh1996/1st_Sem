#include<stdio.h>
#include<stdlib.h>
struct node
{
	struct node *parent;
	//int val;
	int val;
	int dest;
	int max;
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
		printf("%d-%d %d ",ptr->val,ptr->dest,ptr->max);
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
int is_red_node(struct node *pointer)
{
	struct node *p;
	p=pointer;
	if(p!=NULL)
	{
		if(p->color=='R')
			return 1;
		else 
			return 0;
	}
	else
		return 0;
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
	//printf("exiting rr ");
	return rchild;
}
struct node* lr_rotation(struct node *pointer) // function to perform lr rotation
{
	//printf("inside lr");
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
	//printf("redirecting ll");
	//p=rr_rotation(pointer);
	p=ll_rotation(p->parent);
	return p;
}
struct node* rl_rotation(struct node *pointer) // function to perform rl rotaiton
{
	//printf("inside rl");
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
	//printf(" %d redirecting rr",p->parent->val);
	p=rr_rotation(p->parent);
	//printf("%d ",p->parent->val);
	return p;
}
int get_max(int val, struct node *left, struct node *right)
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
void ins_case_2_1(struct node *ptr) //red parent black uncle parent is left child and node is left child
{
	struct node *par;
	par=ll_rotation(ptr->parent->parent);
	if(par!=root)
		recolor(par);
	recolor(par->right);
}
void ins_case_2_2(struct node *ptr) //red parent black uncle parent is left child and node is right child
{
	struct node *par;
	par=lr_rotation(ptr->parent);
	if(par!=root)
		recolor(par);
	recolor(par->right);
}
void ins_case_2_3(struct node *ptr) //red parent black uncle parent is right child and node is left child
{
	struct node *par;
	par=rl_rotation(ptr->parent);
	if(par!=root)
		recolor(par);
	recolor(par->left);
}
void ins_case_2_4(struct node *ptr) //red parent black uncle parent is right child and node is right child
{
	struct node *par;
	par=rr_rotation(ptr->parent->parent);
	if(par!=root)
		recolor(par);
	recolor(par->left);
}
void ins_case_2_5(struct node *ptr) // node to be inserted has red parent and red uncle
{
	recolor(ptr->parent);
	recolor(get_parent_sibling(ptr));
	if(ptr->parent->parent==root)
		return;
	recolor(ptr->parent->parent);
	ptr=ptr->parent;
	if(is_red_node(ptr->parent))
	{
		if(get_parent_sibling(ptr)==NULL || !is_red_node(get_parent_sibling(ptr)))
		{
			if(ptr->parent->val<ptr->parent->parent->val)
			{
				if(ptr->val<ptr->parent->val)
				{
					ins_case_2_1(ptr);
					return;
				}
				else
				{
					ins_case_2_2(ptr);
					return;
				}
			}
			else
			{
				if(ptr->val<ptr->parent->val)
				{
					ins_case_2_3(ptr);
					return;
				}
				else
				{
					ins_case_2_4(ptr);
					return;
				}	
			}
		}
		else
		{
			ins_case_2_5(ptr);
		}
	}
}
void insert(int source, int dest) //overall insert function
{
	struct node *temp,*ptr;
	temp=(struct node*)malloc(sizeof(struct node));
	temp->val=source;
	temp->dest=dest;
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
		if(ptr->val==source)
		{
			return;
		}
		if(source<ptr->val)
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
	if(is_red_node(ptr->parent))
	{
		if(get_parent_sibling(ptr)==NULL || !is_red_node(get_parent_sibling(ptr)))  
		{
			if(ptr->parent->val<ptr->parent->parent->val)
			{
				if(ptr->val<ptr->parent->val)//red parent black uncle parent is left child and node is left child
				{
					ins_case_2_1(ptr);
					if(root->parent!=NULL)
						root=root->parent;
					return;
				}
				else //red parent black uncle parent is left child and node is right child
				{
					ins_case_2_2(ptr);
					if(root->parent!=NULL)
						root=root->parent;
					return;
				}
			}
			else
			{
				if(ptr->val<ptr->parent->val)//red parent black uncle parent is right child and node is left child
				{
					ins_case_2_3(ptr);
					if(root->parent!=NULL)
						root=root->parent;
					return;
				}
				else //red parent black uncle parent is right child and node is right child
				{
					ins_case_2_4(ptr);
					if(root->parent!=NULL)
						root=root->parent;
					return;
				}	
			}
		}
		else // node to be inserted has red parent and red uncle
		{
			ins_case_2_5(ptr);
			if(root->parent!=NULL)
				root=root->parent;
				return;
		}
	}
	else
	{
		if(root->parent!=NULL)
			root=root->parent;
		return;
	}
}
struct node* overlap(struct node *pointer, int source, int dest)
{
//	struct node *ptr;
//	ptr=pointer;
//	while(ptr!=NUL)
//	{
//		if(source>ptr->max)
//			return NULL;
//		
//	}
	if(source>pointer->max)
		return NULL;
	if(source>=pointer->val||dest<=pointer->dest)
	{
		if(source>=pointer->val)
			return pointer;
		if(dest>=pointer->val)
			return pointer;
	}
	else if(source<pointer->left->max)
		return overlap(pointer->left,source,dest);
	else
		return overlap(pointer->right,source,dest);
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
	if(root->right==ptr)
	{
		root->right=NULL;
		free(ptr);
		return;
	}
	struct node *p;
	p=ptr->parent;
	//printf("in del leaf %d ",p->val);
	if(ptr->val<ptr->parent->val)
		p->left=NULL;
	else
		p->right=NULL;
	free(ptr);
	//printf("here %d\n",ptr);
	return ;
}
struct node* del_lco(struct node *ptr) //function to delete a node having left child only
{
	struct node *temp;
	if(ptr==root)
	{
		temp=ptr;
		root=ptr->left;
		free(temp);
		return root;
	}
	temp=ptr->parent;
	if(ptr->val<temp->val)
	{
		temp->left=ptr->left;
		free(ptr);
		return temp->left;
	}
	else
	{
		temp->right=ptr->left;
		free(ptr);
		return temp->right;
	}
}
struct node* del_rco(struct node *ptr) //function to delete a node having right child only
{
	struct node *temp;
	if(ptr==root)
	{
		temp=ptr;
		root=ptr->right;
		free(temp);
		return root;
	}
	temp=ptr->parent;
	if(ptr->val<temp->val)
	{
		temp->left=ptr->right;
		free(ptr);
		return temp->left;
	}
	else
	{
		temp->right=ptr->right;
		free(ptr);
		return temp->right;
	}
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
void del(int source, int dest) //overall delete function
{
	int item;
	struct node *ptr, *p, *temp,*par,*sib;
	if(root==NULL)
	{
		return;
	}
	if(overlap(root,source,dest)!=NULL)
	{
		item=overlap(root,source,dest)->val;
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
				//if(p!=root)
					recolor(p);
				return;
			}
			if(ptr->left==NULL && ptr->right!=NULL) //node is havig right child only
			{
				p=del_rco(ptr);
				//if(p!=root)
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
				temp->dest=ptr->dest;
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
			case 4: if(root==NULL)
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
					scanf("%d%d",&source,&dest);
					del(source,dest);
					max(root);
					}
					break;
			case 3: in_order(root);
					printf("\n");
					//printf("\n%d\n",root->val);
					break;
			case 5: exit(0);
		}
	}
	return 0;
}

