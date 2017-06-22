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
 fclose(fd)	;
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
  mysql_options(db, MYSQL_SET_CHARSET_NAME,"set utf8");


 //做修改
 char name[20] = "\0";
 char age[16] = "\0";
 char stuId[15] = "\0";
 char sex[10]="\0";
 char grade[10]="\0";
 char scid[10]="\0";
 int status = 0;

		status = cgiFormString("name",  name, 20);
		if (status != cgiFormSuccess)
		{
			fprintf(cgiOut, "get name error!\n");
			return 1;
		}

		status = cgiFormString("age",  age, 16);
		if (status != cgiFormSuccess)
		{
			fprintf(cgiOut, "get age error!\n");
			return 1;
		}

		status = cgiFormString("stuId",stuId, 15);
		if (status != cgiFormSuccess)
		{
			fprintf(cgiOut, "get stuId error!\n");
			return 1;
		}

		status = cgiFormString("sex",  sex, 10);
		if (status != cgiFormSuccess)
		{
			fprintf(cgiOut, "get sex error!\n");
			return 1;
		}
		status = cgiFormString("grade",  grade, 10);
		if (status != cgiFormSuccess)
		{
			fprintf(cgiOut, "get grade error!\n");
			return 1;
		}

		status = cgiFormString("scid",  scid, 10);
		if (status != cgiFormSuccess)
		{
			fprintf(cgiOut, "get scid error!\n");
			return 1;
		}


	//fprintf(cgiOut, "name = %s, age = %s, stuId = %s\n", name, age, stuId);

mysql_options(db, MYSQL_SET_CHARSET_NAME,"utf8");
	sprintf(sql, "insert into information values('%s','%s','%s',%d,'%s',%d,0)",stuId,name,sex,atoi(age),scid,atoi(grade));
	mysql_options(db, MYSQL_SET_CHARSET_NAME,"set utf8");
	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}



	fprintf(cgiOut, "update student ok!\n");
	mysql_close(db);
	return 0;
}
