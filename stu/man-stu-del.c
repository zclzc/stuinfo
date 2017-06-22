#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "cgic.h"


int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");

	fprintf(cgiOut, "<head><meta charset=\"utf-8\"><title>查询结果</title>\
		    <link rel=\"stylesheet\" href=\"/stu/public/css/bootstrap.min.css\">\
		</head>");
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
	char stuId[15] = "\0";
  int status=0;

  status = cgiFormString("stuId",stuId, 15);
  if (status != cgiFormSuccess)
  {
    fprintf(cgiOut, "get stuId error!\n");
    return 1;
  }

	int ret;
	MYSQL *db;
	char sql[128] = "\0";

  sprintf(sql, "update information set statu=1  where id='%s'",stuId);

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
 mysql_query(db, "set character set utf8");

	if ((ret = mysql_real_query(db, sql, strlen(sql) + 1)) != 0)
	{
		fprintf(cgiOut,"mysql_real_query fail:%s\n", mysql_error(db));
		mysql_close(db);
		return -1;
	}

	

	fprintf(cgiOut, "<div class=\"container\"> <h4 class=\"text-center\">学号为<strong> %s </strong> 的信息删除成功！</h4>",stuId);



	fprintf(cgiOut,"</div>");

	mysql_close(db);
	return 0;
}
