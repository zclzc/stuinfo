#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"
//char * head = "head.html";
//char * foot= "footer.html";

int cgiMain()
{
  fprintf(cgiOut, "Content-type:text/html;charset=utf-7\n\n");
  FILE * fq;
  char ch;
   fq=fopen("managerstu.html", "r");
   if(fq==NULL){
       fprintf(cgiOut, "Cannot open file,managerstu.html \n");
       return -1;
     }
     ch = fgetc(fq);
     while(ch != EOF){
       fprintf(cgiOut, "%c", ch);
       ch = fgetc(fq);
     }
   fclose(fq);
	return 0;
}
