buildClient:
	gcc client.c client.h -std=c99 -Wextra -Wall -pedantic -lX11 -lm -o client
