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
		eggs = (int)strtod(argv[2], NULL);
		printf("Number of floors %d\n", floors);
		printf("Number of eggs %d\n", eggs);
	}


	int counter = 0;
	egg **carton = malloc(sizeof(*carton) * eggs);

	for (counter = 0; counter < eggs; counter++) {
		carton[counter] = lay_egg();
	}

	size_t guess = pick_floor(eggs, floors);

	while(eggs != 0) {
		printf("guess: %zd\n", guess);
		
		egg_drop_from_floor(carton[eggs - 1], guess);

		if(egg_is_broken(carton[eggs - 1])) {
			printf("EGG CRACKED at floor %ld\n", guess);
			eggs--;
		}
		else {
			printf("EGG SURVIVED at floor %ld\n", guess);
		}

		guess = pick_floor(eggs, guess);
	}

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
		printf("floor %d\n", floor);
		return ++floor;
	}
	else {
		printf("result %d\n", floor/2);
		return (floor/2);	
	}
}
