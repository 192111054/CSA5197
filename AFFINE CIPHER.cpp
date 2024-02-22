#include <stdio.h>
#include<string.h>
#include<ctype.h>
int main()
{
	int k,i;
	char s[100],c[100];
	printf("enter key value: ");
	scanf("%d",&k);
	printf("enter plain text: ");
	scanf("%s",&s);
		printf("the encryption is: ");
	for(i=0;i<strlen(s);i++)
{
		if (islower(s[i]))
		{
		c[i]=((s[i]-'a'+k)%26)+'a';
	}
	else if (isdigit(s[i]))
	{
		c[i]=((s[i]-'0'+k)%10)+'0';
		printf("%c",c[i]);
	}
else
{
	c[i]=((s[i]-'A'+k)%26)+'A';
printf("%c",c[i]);
}
}
printf("\nthe decryption is: ");
	for(i=0;i<strlen(c);i++)
{
		if (islower(c[i]))
		{
		s[i]=((c[i]-'a'-k+26)%26)+'a';
		printf("%c",s[i]);
	}
	else if (isdigit(c[i]))
	{
		int h,f;
		h=c[i]-'0'-k;
		if(h<0)
		{
			f=h+10;
			s[i]=(f%10)+'0';
		}
		else
		{
		s[i]=((c[i]-'0'-k)%10)+'0';	
		}
		printf("%c",s[i]);
	}
else
{
	s[i]=((c[i]-'A'-k+26)%26)+'A';
printf("%c",s[i]);
}
}
	return 0;
}
