#include<stdio.h>
#include<stdlib.h>
void sort(char *a, int size)
{
	int i,j;
	char t;
	for(i=0;i<size-1;i++)
		for(j=i+1;j<size;j++)
			if(*(a+j)<*(a+i))
			{
				t=*(a+j);
				*(a+j)=*(a+i);
				*(a+i)=t;
			}
}
void lowercase(char *a, int size)
{
	int i;
	for(i=0;i<size;i++)
		if(*(a+i)>='A' && *(a+i)<='Z')
			*(a+i)+=32;
}
int main()
{
	int l1, l2, i, flag=0;
	char *str1, *str2;
	printf("enter the size of string a\n");
	scanf("%d",&l1);
	str1=(char*)malloc(l1*sizeof(char));
	printf("enter the string a\n");
	scanf("%s",str1);
	printf("enter the size of string b\n");
	scanf("%d",&l2);
	str2=(char*)malloc(l2*sizeof(char));
	printf("enter the string b\n");
	scanf("%s",str2);
	if(l1!=l2)
	{
		printf(" string a and string b are not anagrams\n");
	}
	else
	{
		lowercase(str1,l1);
		lowercase(str2,l2);
		sort(str1,l1);
		sort(str2,l2);
		for(i=0;i<l1;i++)
		{
			if(*(str1+i)!=*(str2+i))
				flag=1;
			if(flag!=0)
				break;
		}
		if(flag==0)
			printf("string a and string b are anagrams\n");
		else
			printf("string a and string b are not anagrams\n");
	}
	return 0;
}

