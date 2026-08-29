void cbv(int n,int m)
{
	int temp=n;
	n =  m;
	m = temp;
}
void cbr (int *p1, int *p2)
{
	int temp =*p1;
	*p1=*p2;
	*p2 =temp;
}
int main()
{
	int n=10,m=20;
	cbv(n,m);
	cbr(&n,&m);
	while(1)
	{
		;
	}
}		