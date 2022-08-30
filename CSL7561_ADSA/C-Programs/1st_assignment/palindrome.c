#include<stdio.h>
#include<stdlib.h>
void reverse(char *src, char *des, int size)
{
	int i;
	for(i=0;i<size;i++)
		*(des+size-i-1)=*(src+i);
	
}
int main()
{
	int size,i,flag=0 ;
	char *src, *des;
	printf("enter the size of the string\n");
	scanf("%d",&size);
	src=(char*)malloc(size*sizeof(char));
	des=(char*)malloc(size*sizeof(char));
	printf("enter the string\n");
	scanf("%s",src);
	reverse(src,des,size);
	for(i=0;i<size;i++)
		if(*(src+i)!=*(des+i))
			flag++;
	if(flag==0)
		printf("the string is a palindrome\n");
	else
		printf("the string is not a palindrome\n");
	return 0;
}
