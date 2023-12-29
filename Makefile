#Makefile for findit project 

CC=gcc
FILES = ./src/findit.c

all:
	$(CC) $(FILES) -o ./findit

clean:
	rm findit
