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
	char admid[20] = "\0";
	int status = 0;

	status = cgiFormString("admid",  admid, 20);
	if (status != cgiFormSuccess)
	{
		fprintf(cgiOut, "get admid error!\n");
		return 1;
	}

//	char sql[128] = "\0";
	MYSQL *db;
	//初始化
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}

	//连接数据库
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
/*
		sprintf(sql, "select * from information where id = '%s' and statu=0", admid);
		if (mysql_real_query(db, sql, strlen(sql) + 1) != 0)
		{
			fprintf(cgiOut, "%s\n", mysql_error(db));
			mysql_close(db);
			return -1;
		}else{*/
    FILE * fd;
    FILE * fq;
    char ch;
    fd=fopen("temp.txt","w");
    if (fd==NULL) {
      fprintf(cgiOut, "Cannot open file,temp.txt \n");
      return -1;
    }
    fputs(admid,fd);
    fclose(fd);

   fq=fopen("admindex.html", "r");
   if(fq==NULL){
       fprintf(cgiOut, "Cannot open file,admindex.html \n");
       return -1;
     }
     ch = fgetc(fq);
     while(ch != EOF){
       fprintf(cgiOut, "%c", ch);
       ch = fgetc(fq);
     }
   fclose(fq);
// }

	return 0;
}
