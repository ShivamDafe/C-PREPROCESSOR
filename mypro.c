//---------My_preprocessor----------//

#include"header.h"

void main(int argc,char **argv)
{
	if(argc!=2)
	{
		printf("\033[31mUSAGE:\033[0m ./a.out file_name\n");
		return;
	}

	FILE *fp1;
	fp1=fopen(argv[1],"r");

	if(fp1==NULL)
	{
		printf("\033[31;1mfile erorr: \033[0m\033[1m%s:\033[0m File not found!\n",argv[1]);
		return;
	}
	int fsize,i=0;

	fseek(fp1,0,SEEK_END);
	fsize=ftell(fp1);
	rewind(fp1);

	char ch,str[fsize];

	while((ch=fgetc(fp1))!=EOF)
		str[i++]=ch;    //store file into array
	str[i-1]='\0';

	fclose(fp1);
	
	remove_comment(str);         	//remove single line and multi line comment
	header_inclusion(str,argv[1]);  //Include pre_define and user_define header file
	replace_macro(str);            //replace object like macros (macros without argmunet)

}




