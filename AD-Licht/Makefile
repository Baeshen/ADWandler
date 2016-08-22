#
# Makefile ADWandler-LDR Sensor
#

CC 	= gcc

OBJSQL 	= licht_sql.o
OBJNORM	= licht.o

#LIBS = -lpthread -lncurses -lcdk -lwiringPi -L./
LIBS 	=  -lwiringPi -lreadMCP -lmysqlclient

CFLAGS 	= -Wall -O0 -g

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
