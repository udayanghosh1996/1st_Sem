#include<stdio.h>
#include<stdlib.h>
void discard_card(int people)   //card discarding method
{
	if(people<=52 && people>=2)
		printf("%d\n",52%people);
	else 
		printf("-1");
}
int main()
{
	int n, i, *people,*discard;
	scanf("%d",&n);
	people=(int*)malloc(n*sizeof(int));
	discard=(int*)malloc(n*sizeof(int));
	for(i=0;i<n;i++)
		scanf("%d",(people+i));
	for(i=0;i<n;i++)
		discard_card(*(people+i));
	return 0;
}
