CFLAGS = -Wall -Werror -Wextra

main: main.c
	gcc $(CFLAGS) -o main main.c

main2: main2.c
	gcc $(CFLAGS) -o main2 main2.c

clean:
	rm main main2