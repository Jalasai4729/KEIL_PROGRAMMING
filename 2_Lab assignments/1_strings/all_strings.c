void my_strstr(char ms[],char ss[],int s1);
void my_strcmp (char ms[],char ss[],int c1);
void my_itoa (int num,int n1);
int main()
{
	char ms[10]="jalasai";
	char ss[10]="sai";
	int s1,c1,n1;
	int num=123;
	//int r1=0,r2=0,r3=0;
	my_strstr(ms,ss,s1);//substring calling
//	if(r1==1)
	//	r1=1;
//	else
//			r1=-1;

	my_strcmp(ms,ss,c1); //string comparision calling
	//if(r2==1)
		//r2=1;
	//else if(r2==2)
	//	r2=2;
	//else if (r2==-1)
	//	r2=-1;
	//else
		//r2=0;
	
	my_itoa(num,n1);//int calling
//	if(r3==1)
	//{
		//r3=num;
//	}
	
	while(1)
	{
		;
	}
	
}
void my_strstr(char ms[],char ss[],int s1)//substring defination
{
	int i=0,j=0,temp=0;
	//int s1;
 for (i=0;ms[i]!='\0';i++)
	{
		if(ms[i]==ss[j])
		{
			temp++;
			j++;
		}
	}
	j=0;
	while(ss[j])
	{
		j++;
	}
	if (temp==j)
		s1=1;
	else
	s1=0;
}
		

void my_strcmp(char ms[],char ss[],int c1)//comparision defination
{
	int i=0,j=0;
	//int c1;
	while(ms[i])
	{
		i++;
	}
	while(ss[j])
	{
	j++;
	}
	if(i==j)
	  {
	   for (i=0,j=0;ms[i];i++,j++)
	     {
		     if (ms[i]>ss[j])
		        	c1=1;
		     else if(ms[i]<ss[j])
			        c1=2;
       	}
	         c1=0;
    }
	//else
		c1=-1;
}
void my_itoa(int num,int n1)//num defination
{
	int i=0,j=0,rem=0;
	char numstr[10];
  while(num)
	{		
	 rem=num % 10;
		numstr[j]=rem - '0';
		num=num/10;
	}
	for (i=0;i<j/2;i++)
	{
		//temp=numstr[j];
	numstr[i]=numstr[j+i-1];
	}
	n1=1;
}
		