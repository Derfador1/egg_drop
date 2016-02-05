#include "egg.h"

#include <stdio.h>
#include <string.h>

size_t pick_floor(int eggs, int floor);

int main(int argc, char *argv[])
{
	int floors = 0;
	int eggs = 0;

	if(argc != 3) {
		printf("To few arguments\n");
		return 0;
	}
	else if(argc == 3) {
	//else if(check_isdigit(char *argv[1], char *argv[2]))
		printf("%d\n", argc);
		floors = (int)strtod(argv[1], NULL); 
		eggs = strtol(argv[2], NULL, 10);
		printf("Number of floors %d\n", floors);
		printf("Number of eggs %d\n", eggs);
	}


	int counter = 0;
	egg **carton = malloc(sizeof(*carton) * eggs);

	for (counter = 0; counter < eggs; counter++) {
		carton[counter] = lay_egg();
	}

	size_t guess = floors/2;
	size_t prev_guess = guess;
	int total_count = 0;

	while(eggs != 0) {


		if(guess >= 100) {
			guess = floors;
		}
		
		egg_drop_from_floor(carton[eggs - 1], guess);

		if(egg_is_broken(carton[eggs - 1])) {
			printf("EGG CRACKED at floor %ld\n", guess);
			eggs--;

			if(total_count == 0) {
				guess = 1;
			}
			else if(eggs == 1) {
				guess = prev_guess + 1;
			}
		}
		else {
			printf("EGG SURVIVED at floor %ld\n", guess);
			prev_guess = guess;
			guess = pick_floor(eggs, guess);
		}



		total_count++;
	}

	printf("%zd is the maximum safe floor, found after %d drops\n", guess-1, total_count);

	/*
	drop from 50 
	if egg doesnt break drop from 75 
	set egg to 50 and increment by 1
	if it does break then set egg drop to 1 and begin counting up
	*/

	//free error here
	for (counter = 0; counter < eggs; counter++) {
		cook_egg(carton[counter]);
	}
	
	free(*carton);
	//only frees everything if make debug is called
}

size_t pick_floor(int eggs, int floor)
{
	if(eggs == 1) {
		return ++floor;
	}
	else if (eggs > 1) {
		return (floor + floor/2);
	}
	else {
		return (floor/2);	
	}
}
