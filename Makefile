build: 
	gcc -Wall info.h functii.h functii.c main.c -o poker_tournament

clean:
	rm -rf poker_tournament
