buildClient:
	gcc client.c -std=c99 -Wextra -Wall -Werror -pedantic -lX11 -lm -o client
