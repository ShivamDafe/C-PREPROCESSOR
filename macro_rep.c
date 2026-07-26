//---Replacement of Macros---//
#include"header.h"

void replace_macro(char *str)
{
	int i,j,k;
	char ch;
	FILE *fp2,*fp;
	fp2=fopen("i.i","a+");         //Preprocessor output file

	for(i=0;str[i];i++)
	{	
		char name[25]="";
		char def[50]="";
		
		if(str[i]=='#'&& strncmp(str+i,"#define",7)==0)   //#define name def
		{	
			i=i+7;	
			if(str[i]==' ')
			{
				j=0;
				while(str[i]==' ')       //search for macro name
					i++;
				while(str[i]!=' ')       //Collect macro_name
					name[j++]=str[i++];
				
				j=0; i++;
				
				while(str[i]!='\n')    
				{
					if(str[i]=='\\')
					i=i+2;

					while(str[i+1]==' '||str[i+1]=='\t')
						i++;
					if(str[i]=='\t')
						str[i]=' ';
					def[j++]=str[i++];    //Collect macro defination
				}
			}
			
			fp=fopen("temp","w+");         //open temp file for replacement of macros
			int flag1=0,flag2=0;
			int len=strlen(name);

			for(j=i;str[j];j++)
			{
				if(str[j]=='"'||str[j]=='\'')         //checking for "string" or 'char'
					flag1=!flag1;
				if(flag1==0)
				{	
					if((str[j]==name[0] && strncmp(str+j,name,strlen(name))==0))
					{	
						flag2=0;
						if((str[j+len]>='a' && str[j+len]<='z')||(str[j-1]>='a' &&str[j-1]<='z'))
							flag2=!flag2;		
						if(flag2==0)
						{
							k=0;	
							while(def[k])
							{	
								fputc(def[k],fp);    //replace macros with defination
								k++;
							}	
							j=j+(strlen(name));
						}
				
					}
				}
				fputc(str[j],fp);
			}
			rewind(fp);
			k=0;
			while((ch=fgetc(fp))!=EOF)      //updating string
				str[k++]=ch;
			str[k]='\0';
			i=-1;                          //check for next macros			
		}
	}
	rewind(fp);
	while((ch=fgetc(fp))!=EOF)   //updating .i file
		fputc(ch,fp2);

	fclose(fp);
	fclose(fp2);
}
