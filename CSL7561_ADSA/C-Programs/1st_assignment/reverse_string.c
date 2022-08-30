#include<stdio.h>
#include<stdlib.h>
void reverse(char *arr, int size)
{
	char *str;
	int i;
	str=(char*)malloc(size*sizeof(char));
	for(i=0;i<size;i++)
	{
		*(str+size-i-1)=*(arr+i);
	}
	for(i=0;i<size;i++)
	{
		*(arr+i)=*(str+i);
	}
}
int main()
{
	int size;
	char *arr;
	int i;
	printf("enter the size of the string\n");
	scanf("%d",&size);
	arr=(char*)malloc(size*sizeof(char));
	printf("enter the string\n");
	scanf("%s",arr);
	printf("string before reversal\n");
	for(i=0;i<size;i++)
		printf("%c",*(arr+i));
	printf("\n");
	reverse(arr,size);
	printf("string after reversal\n");
	for(i=0;i<size;i++)
		printf("%c",*(arr+i));
	printf("\n");
	return 0;
}
