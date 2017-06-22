#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include "cgic.h"

int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
  int ret ;

  FILE * fd;
  char ch;

 fd=fopen("head.html", "r");
 if(fd==NULL){
     fprintf(cgiOut, "Cannot open file,head.html \n");
     return -1;
   }
   ch = fgetc(fd);

   while(ch != EOF){
     fprintf(cgiOut, "%c", ch);
     ch = fgetc(fd);
   }
 fclose(fd);

	MYSQL *db;
  char sql[128] = "\0";
	db = mysql_init(NULL);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_init fail:%s\n", mysql_error(db));
		return -1;
	}
	db = mysql_real_connect(db, "127.0.0.1", "root", "123456", "stu",  3306, NULL, 0);
	if (db == NULL)
	{
		fprintf(cgiOut,"mysql_real_connect fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}
  mysql_query(db, "set character set utf8");


 //做修改

 char stuId[15] = "\0";
 char cid[10]="\0";
 char score[5]="\0";
 int status = 0;

		status = cgiFormString("stuId",stuId, 15);
		if (status != cgiFormSuccess)
		{
			fprintf(cgiOut, "get stuId error!\n");
			return 1;
		}

		status = cgiFormString("cid",  cid, 10);
		if (status != cgiFormSuccess)
		{
			fprintf(cgiOut, "get scid error!\n");
			return 1;
		}
    status = cgiFormString("score",  score, 5);
    if (status != cgiFormSuccess)
    {
      fprintf(cgiOut, "get scid error!\n");
      return 1;
    }


	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);


	sprintf(sql, "update score set score= %d where id = '%s' and cid='%s' ",atoi(score),stuId,cid);
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	fprintf(cgiOut, "\n\n\n\n\n\n\t\t<h4> <br/><br/><br/><br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<strong>%s</strong>&nbsp;同学的选修的课程号为<strong>'%s'</strong>的成绩成功更新为<strong>%d</strong>！</h4>",stuId,cid,atoi(score));
	mysql_close(db);
	return 0;
}
