//---Header file inclusion---//
#include"header.h"

void header_inclusion(char *str,char *fname)
{
	int i,j;
	char ch;
	FILE *fp2,*fp3;
	fp2=fopen("i.i","w");

	for(i=0;str[i];i++)
	{	
		char file[25]="";
	
		if(str[i]=='#'&& strncmp(str+i,"#include",8)==0)
		{	
			i=i+8;	
			if(str[i]=='<'|| str[i]=='"')  //default user define
			{	
				j=0;
				if(str[i]=='<')         //predefine header file 
				{
					strcpy(file,"/usr/include/");
					j=13;
				}
				i++;
				while(str[i]!='>'&& str[i]!='"')
					file[j++]=str[i++];

				fp3=fopen(file,"r");        //open header file
				
				if(fp3==NULL)
				{		
					printf("\033[1m%s:%s\033[0m \033[31mfatal error: \033[0m%s: No such file or directory\n",fname,__TIME__,file);
        				printf("\t| #include\033[31m<%s>\n\033[0m",file);
        				printf("\t|         \033[31m^~~~~~~~\n\033[0mcompilation terminated.\n");
					return;
				}

				while((ch=fgetc(fp3))!=EOF)       //paste the header file into .i file
					fputc(ch,fp2);
				fclose(fp3);
			}
		}		

	}
	fclose(fp2);

}
