#include<stdio.h>
#include<stdlib.h>
void insertion_sort(int *a, int n)
{
	int i,j,temp;
	for(i=1;i<n;i++)
	{
		temp=*(a+i);
		for(j=i;j>0&&(temp<*(a+j-1));j--)
			*(a+j)=*(a+j-1);
		*(a+j)=temp;
	}
}
double diff(double avg, int a)
{
	if((avg-a)>0)
		return (avg-a);
	else 
		return (a-avg);
}
double cost(int *a, int n)
{
	double avg=0;
	double sum=0;
	int i;
	insertion_sort(a,n);
	if(n%2==0)
		avg=(*(a+(n-1)/2)+*(a+n/2))/2;
	else
		avg=*(a+n/2);
	for(i=0;i<n;i++)
		sum=sum+diff(avg,*(a+i));
	return sum;
}
int main()
{
	int n, *a,i,c;
	double cst;
	scanf("%d",&n);
	a=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",a+i);
	cst=cost(a,n);
	c=cst;
	printf("%d\n",c);
	return 0;
}
