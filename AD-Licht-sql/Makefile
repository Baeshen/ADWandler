#
# Makefile ADWandler-LDR Sensor
#

CC 	= gcc

OBJSQL 	= licht_sql.o
OBJNORM	= licht.o

LIBS 	=  -lwiringPi -lreadMCP -lmysqlclient

LINKS	= -L/usr/lib/mysql

CFLAGS 	= -Wall -O0 -g -I/usr/include/mysql

SQL 	= licht-sql
NORM 	= licht 

sql: $(OBJSQL)
	$(CC) -o $(SQL) $(OBJSQL) $(LIBS)

norm: $(OBJNORM)
	$(CC) -o $(NORM) $(OBJNORM) $(LIBS)

%.o: %.c
	$(CC) -c $(CFLAGS) $<

clean:
		rm *.o $(SQL) $(NORM)
