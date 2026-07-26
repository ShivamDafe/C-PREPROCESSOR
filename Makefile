#----Makefile----#

CC = gcc
CFLAG = -Wall

Files = mypro.o remove_com.o header_inc.o macro_rep.o
exe = prepro

$(exe): $(Files)
	$(CC) $(Files) -o $(exe)

mypro.o: mypro.c header.h
	$(CC) $(CFLAG) -c mypro.c

remove_com.o: remove_com.c header.h
	$(CC) $(CFLAG) -c remove_com.c

header_inc.o: header_inc.c header.h
	$(CC) $(CFLAG) -c header_inc.c

macro_rep.o: macro_rep.c header.h
	$(CC) $(CFLAG) -c macro_rep.c


clear:
	rm -f $(Files) $(exe)   #remove all .o file and execuatable file

