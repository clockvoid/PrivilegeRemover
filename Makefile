
CC=gcc
LIBS=-lm
CFLAGS=-Wall -g
OBJS=prem.o
TARGET=prem
HEADERS=prem.h

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $(TARGET)

$(OBJS): $(HEADERS)

clean:
	rm -f *.o
