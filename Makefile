
CC=gcc
LIBS=-lm
CFLAGS=-Wall -g
SRC=main.c prem.c
OBJS=$(SRC:%.c=%.o)
TARGET=prem
HEADERS=prem.h

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) -c $<

clean:
	rm -f $(TARGET) $(OBJS)

prem.o: prem.c prem.h
main.o: main.c prem.h
