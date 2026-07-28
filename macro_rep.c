//---Replacement of Macros---//
#include"header.h"

void replace_macro(char *str)
{
	int i,j,k,spec=0;
	FILE *fp2,*fp;
	fp2=fopen("i.i","a+");         //Preprocessor output file
 	char keyword[]="int char float double long short if else switch case default continue return goto break static auto register extern struct union typedef enum for while do sign unsign const volatile sizeof void";
    char num[]="1234567890";
    char spechar[]="@#$%&!~-+=[]{}|<>/.:",ch;
	
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
				while(str[i]!=' ' && str[i]!='\n')       //Collect macro_name
					name[j++]=str[i++];
				if(str[i]=='\n')                //if macro defination not written
				{
					str[i-1]=' ';
					i=i-2;
				}
				for(j=0;spechar[j];j++)
                	if(strchr(name,spechar[j]))
                        	spec=1;
                if(strstr(keyword,name) || strchr(num,name[0]) || spec)
                {
                	printf("\033[1m%s:%s:\033[0m \033[31merror:\033[0m macro name must be identifiers\n\t| #define \033[33m%s\n\t|\t  ^~~~\n\033[0m",fname,__TIME__,name);
                    return;
                }
				j=0,i++;
				while(str[i]!='\n')           //collect macro defination   
				{
					if(str[i]=='\\')
					i=i+2;

					while(str[i+1]==' '||str[i+1]=='\t')
						i++;
					if(str[i]=='\t')
						str[i]=' ';
					def[j++]=str[i++];    //store macro defination
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
