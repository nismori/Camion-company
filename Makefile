all: exec

t.o: t.c t.h
    gcc -c t.c -o t.o

s.o: s.c s.h
    gcc -c s.c -o s.o

exec: s.o t.o
    gcc t.o s.o -o exec
