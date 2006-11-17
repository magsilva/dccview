CC= gcc
LIBS= -lkudzu -lpci
CFLAGS= -static

all:
	$(CC) dccview.c $(LIBS) $(CFLAGS) -o dccview
