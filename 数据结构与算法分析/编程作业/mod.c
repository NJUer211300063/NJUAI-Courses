#include<stdio.h>
#include<string.h>
char a[100],b[100];//用两个字符串用来输入两个大数 
int x[100],y[100],z[100],m[100];//被除数  除数  商  余数 
int digit;//大数的位数 
void sub(int x[],int y[],int len1,int len2)//大数减法 
{
	int i;
	for(i=0;i<len1;i++)
	{
		if(x[i]<y[i])
		{
			x[i]=x[i]+10-y[i];
			x[i+1]--;
		}
		else
			x[i]=x[i]-y[i];
	}
	for(i=len1-1;i>=0;i--)//判断减法结束之后，被除数的位数 
	{
		if(x[i])
		{ 
			digit=i+1;
			break;		   
		} 
	}
}
int judge(int x[],int y[],int len1,int len2)
{
	int i;
	if(len1<len2)
		return -1;
	if(len1==len2)//若两个数位数相等 
	{
		for(i=len1-1;i>=0;i--)
		{
			if(x[i]==y[i])//对应位的数相等 
				continue;
			if(x[i]>y[i])//被除数 大于 除数，返回值为1 
				return 1;
			if(x[i]<y[i])//被除数 小于 除数，返回值为-1 
				return -1;
		}
		return 0;//被除数 等于 除数，返回值为0 
	}	
}
int main()
{
	int i,j=0,k=0,temp;
	int len1,len2,len;//len两个大数位数的差值   
	while(~scanf("%s %s",a,b))
	{
		len1=strlen(a);//被除数位数
		len2=strlen(b);//除数位数
		for(i=len1-1,j=0;i>=0;i--)//将字符串中各个元素倒序储存在数组中 
			x[j++]=a[i]-'0';
		for(i=len2-1,k=0;i>=0;i--)
			y[k++]=b[i]-'0';		    
		if(len1<len2)//当被除数位数 小于 除数位数时 
		{
			printf("商是：0\n");
			printf("余数是：");
			puts(a); 
		}
		else //当被除数位数 大于或者 除数位数时
		{
			len=len1-len2;//两个大数位数的差值
			for(i=len1-1;i>=0;i--)//将除数后补零，使得两个大数位数相同。被除数：4541543329 除数：98745,加零后:9874500000 
			{
				if(i>=len)
					y[i]=y[i-len];
				else
					y[i]=0;
			}
			len2=len1;//将两个大数数位相同 		
			digit=len1;	//将原被除数位数赋值给digit 
			for(j=0;j<=len;j++)
            {
				z[len-j]=0;
				while(((temp=judge(x,y,len1,len2))>=0)&&digit>=k)//判断两个数之间的关系以及位数与除数原位数的关系 
				{	
					sub(x,y,len1,len2);	//大数减法函数			    
					z[len-j]++;//储存商的每一位
					len1=digit;//重新修改被除数的长度
					if(len1<len2&&y[len2-1]==0)		
						len2=len1;//将len1长度赋给len2;						
				}
				if(temp<0)//若被除数 小于 除数，除数减小一位。例如：被除数：4541543329 除数：(原)98745,(加零后)9874500000，后退一位后:0987450000 
				{
					for(i=1;i<len2;i++)
						y[i-1]=y[i];
					y[i-1]=0;
					if(len1<len2) 
						len2--;			        				        
				}
			}
			printf("商是：");
			for(i=len;i>0;i--)//去掉前缀0 
			{
				if(z[i])
					break;
			}
			for(;i>=0;i--)
				printf("%d",z[i]);
			printf("\n");
			printf("余数是：");
			for(i=len1;i>0;i--)
			{
				if(x[i])
					break;
			}
			for(;i>=0;i--)
				printf("%d",x[i]);
			printf("\n");
		}
	}
	return 0;
}