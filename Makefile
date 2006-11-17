CC= gcc
LIBS= -lkudzu -lpci
CFLAGS= -static

all:
	$(CC) dccView.c $(LIBS) $(CFLAGS) -o dccView
