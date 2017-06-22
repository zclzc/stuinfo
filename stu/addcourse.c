#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "cgic.h"


int cgiMain()
{

	fprintf(cgiOut, "Content-type:text/html;charset=utf-8\n\n");
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

 int ret;
 MYSQL *db;
 char sql[128] = "\0";
 char cid[10]="\0";
 char stuId[15]="\0";

 int status=0;
 status = cgiFormString("cid",  cid, 10);
 if (status != cgiFormSuccess)
 {
   fprintf(cgiOut, "get cid error!\n");
   return 1;
 }
 FILE * fp;
 fp=fopen("temp.txt", "r");
 fgets(stuId, 15, fp);
 fclose(fp);

 sprintf(sql, "insert into score values('%s','%s',0)",stuId,cid);
 fprintf(cgiOut, "<div class=\"container\"> <h2 class=\"text-center\">学生选课信息</h2>");

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
 fprintf(cgiOut, "add course ok!\n");
 sprintf(sql, "select * from sc where 学号 = '%s'", stuId);
 fprintf(cgiOut, "<div class=\"container\"> <h2 class=\"text-center\">学生选课信息</h2>");
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
