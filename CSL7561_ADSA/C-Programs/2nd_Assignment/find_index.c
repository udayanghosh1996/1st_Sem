#include<stdio.h>
#include<stdlib.h>
void find(int *a, int n, int f)
{
	int first=-1, last, i;
	for(i=0;i<n;i++)
	{
		if(*(a+i)==f && first==-1)
			first=i;
		if(*(a+i)==f)
			last=i;
	}
	printf("%d %d", first, last);
}
int main()
{
	int n,i,*a,f;
	scanf("%d",&n);
	a=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",a+i);
	scanf("%d",&f);
	find(a,n,f);
	return 0;
}
