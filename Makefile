FLAGS=-g -Wall -Wextra -std=c99
DEPS=$(wildcard ./headers/*.h)
all: ./bin/main clean

./bin/main: ./obj/main.o ./obj/carte.o ./obj/plateau.o ./obj/interface.o
	gcc $(FLAGS) -o $@ $^

./obj/%.o: ./src/%.c $(DEPS)
	gcc $(FLAGS) -o $@ -c $<

clean:
	rm -rf ./obj/*.o
