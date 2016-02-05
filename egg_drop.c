#include "egg.h"

#include <stdio.h>
#include <string.h>

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

	for (counter = 0; counter < eggs; counter++) {
		cook_egg(carton[counter]);
	}
	
	free(carton);
	//only frees everything if make debug is called
}
