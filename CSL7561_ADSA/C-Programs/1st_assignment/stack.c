#include<stdio.h>
#include<stdlib.h>
struct stack
{
	int top;
	int *val;
};
struct stack stack1;
struct stack* initialize(int size)
{
	struct stack *add;
	stack1.top=-1;
	stack1.val=(int*)malloc(size*sizeof(int));
	add=&stack1;
	printf("stack is created and size of the stack is %d\n",size);
	return add;
}
void push(struct stack *s, int item, int size)
{
	if(s->top==(size-1))
	{
		printf("Stack is full\n");
		return;
	}
	s->top++;
	s->val[s->top]=item;
	printf("item successfully inserterd in the stack\n");
}
void pop(struct stack *s)
{
	int item;
	if(s->top==-1)
	{
		printf("underflow occured\n");
		return;
	}
	item=s->val[s->top];
	s->top--;
	printf("popped item from the stack is %d\n",item);
}
void display(struct stack *s)
{
	int p;
	p=s->top;
	if(p==-1)
	{
		printf("empty stack\n");
	}
	else
	{
		while(p>-1)
		{
			printf("%d ->",s->val[p--]);
		}
		printf("end\n");
	}
}
int main()
{
	struct stack *s;
	int size,n,item;
	printf("enter the size of stack want to create\n");
	scanf("%d",&size);
	s=initialize(size);
	while(1)
	{
		printf("Please chose any option for stack operation\n");
		printf("1. Push\t\t2. Pop\n3. Display\t4. Exit\n");
		scanf("%d",&n);
		switch(n)
		{
			case 1: printf("enter the element to be pushed in the stack\n");
					scanf("%d",&item);
					push(s,item,size);
					break;
			case 2: pop(s);
					break;
			case 3: display(s);
					break;
			case 4: exit(0);
					break;
			default: printf("Wrong input. Choose correct option\n");
		}
	}
	return 0;
}

