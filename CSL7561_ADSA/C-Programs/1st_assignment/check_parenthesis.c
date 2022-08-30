#include<stdio.h>
#include<stdlib.h>
struct stack
{
	int top;
	char *val;
};
struct stack stack1;
struct stack* initialize(int size)
{
	struct stack *add;
	stack1.top=-1;
	stack1.val=(char*)malloc(size*sizeof(char));
	add=&stack1;
	return add;
}
int push(struct stack *s, char item, int size)
{
	if(s->top==(size-1))
	{
		printf("Stack is full\n");
		return s->top;
	}
	s->top++;
	s->val[s->top]=item;
	return s->top;
}
int pop(struct stack *s, char c)
{
	if(s->top==-1)
	{
		return -2;
	}
	if(s->val[s->top]!=c)
		return s->top;
	s->top--;
	return s->top;
}
int main()
{
	int i, size, top;
	char *exp;
	struct stack *s;
	printf("enter the length of the expression\n");
	scanf("%d",&size);
	exp=(char*)malloc(size*sizeof(char));
	printf("enter the expression\n");
	scanf("%s",exp);
	s=initialize(size);
	for(i=0;i<size;i++)
	{
		if(*(exp+i)=='(')
			top=push(s,'1',size);
		if(*(exp+i)==')')
			top=pop(s,'1');
		if(*(exp+i)=='{')
			top=push(s,'2',size);
		if(*(exp+i)=='}')
			top=pop(s,'2');
		if(*(exp+i)=='[')
			top=push(s,'3',size);
		if(*(exp+i)==']')
			top=pop(s,'3');
		if(top==-2)
			break;
	}
	if(top==-1)
		printf("expression have balanced parenthesis\n");
	else if(top==-2)
		printf("expression doesn't have balanced parenthesis\n");
	else
		printf("expression have wrong combination of parenthesis\n");
	return 0;
}
