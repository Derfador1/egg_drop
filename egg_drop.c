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

}
