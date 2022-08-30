#include<stdio.h>
#include<stdlib.h>
void sort(int *a, int size)
{
	int i,j;
	int t;
	for(i=0;i<size-1;i++)
		for(j=i+1;j<size;j++)
			if(*(a+j)<*(a+i))
			{
				t=*(a+j);
				*(a+j)=*(a+i);
				*(a+i)=t;
			}
}
int binary_search(int *a,int max, int min, int f)
{
	int mid;
	mid=(max+min)/2;
	if(max>=min)
	{
		if(*(a+mid)==f)
			return 1;
		if(f<*(a+mid))
			return binary_search(a,mid-1,min,f);
			
		else if((f>*(a+mid)))
			return binary_search(a,max,mid+1,f);
		else
			return -1;
	}
	else return -1;
}
int main()
{
	int i, *a, n,f,c, ind;
	scanf("%d",&n);
	a=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",a+i);
	scanf("%d",&f);
	sort(a,n);
	printf("%d",binary_search(a,n-1,0,f));
	return 0;
}
