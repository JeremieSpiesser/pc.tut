FLAGS=-g -Wall -Wextra -std=c99

all: main clean

main: main.o carte.o plateau.o interface.o
	gcc $(FLAGS) -g -o $@ $^

%.o: %.c
	gcc $(FLAGS) -g -o $@ -c $<

clean:
	rm -rf *.o
