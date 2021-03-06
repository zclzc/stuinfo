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
	char id[15] = "\0";

	FILE * fp;
	fp=fopen("temp.txt", "r");
	fgets(id, 15, fp);
	fclose(fp);
	int ret;
	MYSQL *db;
	char sql[128] = "\0";

	if (id[0] == '*')
	{
		sprintf(sql, "select y.* from student y,information x where y.学号=x.id and x.statu=0");
	}
	else
	{
		sprintf(sql, "select y.*  from student y,information x where y.学号= '%s' and x.id= '%s' and x.statu=0", id,id);
	}


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

	MYSQL_RES *res;
	res = mysql_store_result(db);
	if (res == NULL)
	{
		fprintf(cgiOut,"mysql_store_result fail:%s\n", mysql_error(db));
		return -1;
	}

	fprintf(cgiOut, "<div class=\"container\"> <h2 class=\"text-center\">个人信息</h2>");

	fprintf(cgiOut,"<table class=\"table table-striped table-bordered\"><tr>");
	int i = 0;

	unsigned int fields;
	fields = mysql_num_fields(res);//返回mysql_store_result的记录个数

	MYSQL_FIELD *mysql_filed;
	mysql_filed = mysql_fetch_fields(res);//返回集合中列的定义（即获取每列的属性名）
	for (i = 0; i < fields ; i++)
	{
		fprintf(cgiOut, "<th>%s</th>", mysql_filed[i].name);
	}
	fprintf(cgiOut,"</tr>");

	//访问每一条记录的值
	MYSQL_ROW  row;
	unsigned long  *len;

	while ((row = mysql_fetch_row(res)) != NULL)//返回集合中的一行
	{
		fprintf(cgiOut,"<tr>");
		len = mysql_fetch_lengths(res);//返回当前行中每一个字段值的长度
		for (i = 0; i < fields ; i++)
		{
			fprintf(cgiOut,"<td>%.*s</td>", (int)len[i], row[i]);
		}
		fprintf(cgiOut,"</tr>");
	}
	fprintf(cgiOut,"</table></div>");

	mysql_close(db);
	return 0;
}
