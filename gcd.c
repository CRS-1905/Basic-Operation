#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	unsigned long int a[32];
}int2048;

const int2048 ZERO={{0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL}},
ONE={{0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,0UL,1UL}};

void store(int2048 *b,char *str1);
int2048 sum(int2048,int2048,unsigned long int);
unsigned int compare(int2048 x,int2048 y);
void print(int2048 b);
int2048 division(int2048,int2048);
int2048 multi(int2048 m, int2048 n);
int2048 gcd(int2048,int2048);
int2048 left_shift(int2048 ,unsigned int );
int num_bit(int2048 b);

int main()
{
	int2048 x,y,z,t;
	unsigned int p;
	char str1[512],str2[512];
	
	x=ZERO;
	y=ZERO;
	z=ZERO;
	t=ZERO;
	
	printf("Enter The 1st Integer in hex:\n");
	scanf("%512s",str1);
	store(&x,str1);

	printf("Enter The 2nd Integer in hex:\n");
	scanf("%512s",str2);
	store(&y,str2);
	
	p=compare(x,y);
	
	if(p == 3)
	{
		z=x;
		x=y;
		y=z;
	}

	t=gcd(x,y);
	printf("The Required Gcd is Given By:\t");
	print(t);
		
	
}

void store(int2048 *b,char *str)
{
	int j,k,i,len;
	char ch;
	int flag=0;

	if(str != NULL)
	{
		if(str[0]=='-')
		{
			flag=1;
			str++;
		}

		len=strlen(str);
		j=31;k=0;

		for(i=0;i<len;i++)
		{

			 ch=str[len-1-i];

			if(ch >= 'a' && ch <= 'f')
				ch=ch-'a' + 10;
			
			if(ch >= 'A' && ch <= 'F')
				ch=ch-'A' + 10;

			if(ch >= '0' && ch <= '9')
				ch=ch-'0';
			
			unsigned long int c=(unsigned long int)ch;
			
			b->a[j]=(b->a[j])|(c<<k);
			
			if((i+1)%16 == 0)
				j--;

			k=(k+4)%64;
			
		}
	}

	if(flag == 1)
	{
		for(i=0;i<32;i++)
			b->a[i]=~(b->a[i]);
		*b=sum(*b,ONE,0UL);
	}
}

int2048 sum(int2048 b,int2048 b1,unsigned long int c)
{
	unsigned long int ch,ch1,sum,ch2;
	ch2=c;
	int2048 all_sum=ZERO;
	int i,j,k;
	for(i=31;i>=0;i--)
	{
		sum=0UL;
		for(j=0;j<64;j++)
		{
			ch= (b.a[i]>>j) & 1UL;
			ch1=((b1.a[i]>>j) & 1UL)^ch2;
			sum=sum | ((c ^ch ^ ch1)<<j);
			c=(ch & ch1)| ((ch^ch1)&c);

		}
		all_sum.a[i]=sum;
	}
	return all_sum;
}

unsigned int compare(int2048 x,int2048 y)
{
	int k,i,flag1=0,flag2=0;
	unsigned long int x1,y1,s1=0UL,product=1UL;
	
	if((x.a[0]>>63) ==1UL)
		flag1=1;
	if((y.a[0]>>63) == 1UL)
		flag2=1;
	if(flag1!=flag2)
	{
		if(flag1>flag2)
			return 3;
		else
			return 2;
	}

	else
	{
		k=63;
		for(i=0;i<32;)
		{
			x1=x.a[i]>>k;
			y1=y.a[i]>>k;
			s1=s1 | (x1 & (y1 ^ 1UL) & product);
			product=product & (x1 ^ y1 ^ 1UL);
			k--;
			if(k<0)
			{
				k=63;
				i++;
			}
		}
	
		if(product == 1)
			return 1;
		
		if(s1 == 1)
			return 2;
		else
			return 3;

	}

}

void print(int2048 b)
{
	int bal=0,i;
	if((b.a[0]>>63) == 1UL)
	{
		printf("-");
		for(i=0;i<32;i++)
			b.a[i] = ~b.a[i];
		b = sum(b,ONE,0);
	}
	for(i=0;i<32;i++)
	{
		if(bal == 0 && b.a[i]==0UL)
			continue;
		else if(bal == 0)
		{
			bal =1;
			printf("%lx",b.a[i]);
		}
		else	
			printf("%.16lx",b.a[i]);
								
	}
	if(bal == 0)
		printf("%lx",0UL);
	printf("\n");
}

int2048 gcd(int2048 x,int2048 y)
{
	int2048 q,r;
	q=ZERO;
	r=ZERO;
	
	if(compare(y,ZERO) == 1)
		return x;

	while(compare(y,ZERO)!=1)
	{
		q=division(x,y);
		r=sum(x,multi(y,q),1);
		x=y;
		y=r;
	}

	return x;
	
}

int2048 division(int2048 x,int2048 y)
{
	int flag1 =0,flag2 =0;
	int2048 quotient;
	int2048 remainder;
	unsigned int p;
	int n1,n2,n,i;
	
	quotient=ZERO;
	remainder=ZERO;
	p=compare(x,ZERO);
		if(p==3)
		{
			for(i=0;i<32;i++)
				x.a[i]=~x.a[i];
			x = sum(x,ONE,0);
			flag1=1;
		}
	p=compare(y,ZERO);
		if(p==3)
		{
			for(i=0;i<32;i++)
				y.a[i]=~y.a[i];
			y = sum(y,ONE,0);
			flag2=1;
		}
	p=compare(x,y);
	if(p == 3)
	{
		quotient=ZERO;
		remainder=x;
	}
	
	else
	{
		while(p!=3)
		{
			n1=num_bit(x);
			n2=num_bit(y);

			p=compare(x,left_shift(y,n1-n2));
			
			if(p == 3)
				n=n1-n2-1;
			else
				n=n1-n2;
		
			for(i=0;i<32;i++)
				quotient.a[i]= quotient.a[i] | left_shift(ONE,n).a[i];

			remainder=sum(x,left_shift(y,n),1);
			x=remainder;
			p=compare(x,y);

		}
	}
	if(flag1 != flag2)
	{
		for(i=0;i<32;i++)
			quotient.a[i] = ~quotient.a[i];
		quotient = sum(quotient,ONE,0);
	}
	if(flag1!=0)
	{
		for(i=0;i<32;i++)
			remainder.a[i] = ~remainder.a[i];
		remainder = sum(remainder,ONE,0);
	}
	
	return quotient;

}

int2048 multi(int2048 m, int2048 n)
{
	int i,j,k;
	int2048 mult;
	
	mult=ZERO;

	k=0;
	for(j=31;j>=0;)
	{	
		if((m.a[j]>>k)&1UL == 1UL)
			mult = sum(mult,n,0);
		n = left_shift(n,1);
		k = (k+1)%64;
		if(k == 0)
			j--;
	}
	return mult;
}

int2048 left_shift(int2048 b,unsigned int c)
{
	unsigned int c1,c2;
	int i,j;
	int2048 b1;
	
	b1=ZERO;

	c1=c/64;
	c2=c%64;
	
	if(c == 0)
		return b;
	
	if(c1 == 0)
	{
		b1=b;
	}

	else
	{
		i=0;
		while(i+c1<32)
		{
			b1.a[i]=b.a[i+c1];
			i++;
		}
		for(j=i;j<32;j++)
			b1.a[j]=0UL;
	}

	if(c2!=0)
	{
		for(i=0;i<31;i++)
			b1.a[i]=(b1.a[i] << c2) |(b1.a[i+1]>>(64-c2));
		b1.a[31]=b1.a[31]<<c2;
	}

	return b1;
}

int num_bit(int2048 b)
{
	int k=63,i,j;
	int s=0;
	unsigned long int t;

	for(i=0;i<32;)
	{
		if(b.a[i] == 0UL)
		{
			s=s+64;
			i++;
		}

		else
		{

			for(j=63;j>=0;j--)
			{
				if(b.a[i]>>j == 0UL)
					s=s+1;
				else
					break;
			}
			break;
		}
	}

	return 	(2048-s);
}



















