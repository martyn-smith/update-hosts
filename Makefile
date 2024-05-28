prod:
	gcc -D PROD -o update-hosts src/main.c

test:
	gdd -D TEST -g -o update-hosts src/main.c
