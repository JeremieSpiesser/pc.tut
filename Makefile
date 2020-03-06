FLAGS=-Wall -Wextra -std=c99

all: main clean

main: main.o carte.o plateau.o interface.o
	gcc -g -o $@ $^ $(FLAGS)

%.o: %.c
	gcc -g -o $@ -c $< $(FLAGS)

clean:
	rm -rf *.o
