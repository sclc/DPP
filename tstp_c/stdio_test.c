#include<stdio.h>
#define LOCAL
#define INF 1000000000

int main()
{
	printf("hhh going in in while\n");
#ifdef LOCAL
	freopen("./data.in","r",stdin);
	//freopen("data.out","w",stdout);
#endif	
	printf("going in in while\n");
	int x, n=0, min=INF, max=-INF, s=0;
	while (scanf("%d",&x) ==1)
	{
		printf("in while\n");
		printf("x is %d \n",x);
		s +=x;
		if(x<min) min=x;
		if(x>max) max=x;

		n++;
	}

	printf("%d, %d, %.3lf\n", min, max, (double)s/n);

	return 0;
}
