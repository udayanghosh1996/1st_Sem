#include<stdio.h>
#include<stdlib.h>
int linear_search(int *a,int n, int f)
{
	int i, index=-1;
	for(i=0;i<n;i++)
		if(*(a+i)==f)
			return 1;
	return -1;
}
int main()
{
	int i, *a, n,f;
	scanf("%d",&n);
	a=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",a+i);
	scanf("%d",&f);
	printf("%d",linear_search(a,n,f));
	return 0;
}
