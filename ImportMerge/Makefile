CFLAGS=-c -Wall -I../../Common -I../data -w 
LFLAGS=-Wall -O2 -w
LIBS=-lpthread
CC=g++
OBJS=Main.o AnsiString.o StringBuffer.o Data.o Exception.o JSONUtil.o StringUtil.o DataUtil.o

all: merge

merge: $(OBJS)
	$(CC) $(LFLAGS) -o merge $(OBJS) $(LIBS)

Main.o: Main.cpp
	$(CC) $(CFLAGS) Main.cpp

Data.o: ../data/Data.cpp
	$(CC) $(CFLAGS) ../data/Data.cpp

DataUtil.o: ../data/DataUtil.cpp
	$(CC) $(CFLAGS) ../data/DataUtil.cpp

AnsiString.o: ../../Common/AnsiString.cpp
	$(CC) $(CFLAGS) ../../Common/AnsiString.cpp

StringBuffer.o: ../../Common/StringBuffer.cpp
	$(CC) $(CFLAGS) ../../Common/StringBuffer.cpp

StringUtil.o: ../../Common/StringUtil.cpp
	$(CC) $(CFLAGS) ../../Common/StringUtil.cpp

Exception.o: ../../Common/Exception.cpp
	$(CC) $(CFLAGS) ../../Common/Exception.cpp

JSONUtil.o: ../../Common/JSONUtil.cpp
	$(CC) $(CFLAGS) ../../Common/JSONUtil.cpp

clean:
	rm -f *.o *.exe *.obj *.tds
