//----Comment remove----//
#include"header.h"

void remove_comment(char *str)
{	
	int i;
	for(i=0;str[i];i++)
	{	
		if(str[i]=='/' && str[i+1]=='/')       //remove single line comment
		{	
			while(str[i]!='\n')
				str[i++]=' ';
		}

		if(str[i]=='/' && str[i+1]=='*')	//remove multi_line comment	
		{
			while(str[i+1]!='/')
				str[i++]=' ';
			str[i++]=' ';
			str[i]=' ';
		}	   
	}
}
