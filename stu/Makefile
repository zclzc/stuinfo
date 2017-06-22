CC=gcc
AFLAGS=-Wall -g
LDFLAGS= -lmysqlclient
OBJS= man-cou-del.cgi del.cgi modscore.cgi sel.cgi selsc.cgi addc.cgi courseinfo.cgi addcourse.cgi topin.cgi tsel.cgi tcourse.cgi courseands.cgi managerstu.cgi man-stu-add.cgi man-stu-del.cgi man-cou-sel.cgi admopind.cgi mancourse.cgi man-cou-add.cgi manteacher.cgi man-tea-sel.cgi man-tea-del.cgi  man-tea-add.cgi


all:$(OBJS)

$(OBJS):%.cgi:%.c
	$(CC) $(AFLAGS) $< cgic.c -o $@ $(LDFLAGS)

.PHONY:clean
clean:
	rm ./.gitinore/*.cgi
install:
		sudo cp ./index.html /var/www/html/
		cp ./*.cgi /usr/lib/cgi-bin/sx
		cp  tindex.html mancourser.html admindex.html /usr/lib/cgi-bin/sx
		cp manteacher.html head.html  /usr/lib/cgi-bin/sx
		mv ./*.cgi ./.gitinore
