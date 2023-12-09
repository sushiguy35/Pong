main:
	gcc src/main.c -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	make run

run:
	./main