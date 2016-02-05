#include "egg.h"

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

size_t pick_floor(double floor);
bool check_isdigit(char *floors, char *eggs);
bool binary_search(double floors, int eggs, egg **carton);
bool quadratic_search(double floors, int eggs, egg **carton);

int main(int argc, char *argv[])
{
	double floors = 0;
	int eggs = 0;
	int eggs_counter = 0;

	if(argc != 3) {
		fprintf(stderr, "To few arguments\n");
		return 0;
	}
	else if(argc == 3) {
		if(check_isdigit(argv[1], argv[2])) {
			floors = strtod(argv[1], NULL); 
			eggs = strtol(argv[2], NULL, 10);
			eggs_counter = eggs;
			printf("Number of floors %.0lf\n", floors);
			printf("Number of eggs %d\n", eggs);
		}
		else {
			fprintf(stderr, "Error\n");
			exit(1);
		}
	}


	//if(floors <= .001 || eggs == 0) {
	//	fprintf(stderr, "One of the given inputs was not a valid number for this trial\n");
	//	exit(1);
	//}

	int counter = 0;
	egg **carton = malloc(sizeof(*carton) * eggs);

	for (counter = 0; counter < eggs; counter++) {
		carton[counter] = lay_egg();
	}

	if(eggs > log2(floors)) {
		binary_search(floors, eggs, carton);
	}
	else {
		quadratic_search(floors, eggs, carton);
	}

	for (counter = eggs_counter - 1; counter >= 0; --counter) {
		cook_egg(carton[counter]);
	}
	
	free(carton);
}

size_t pick_floor(double floor)
{
	double a = 0.5;
	double b = 0.5;
	double c = -floor;

	double guess = (-b+sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	return ceil(guess);
}

bool check_isdigit(char *floors, char *eggs)
{
	if(!isdigit(*floors)) {
		printf("Your arguments are invalid\n");
		return false;
	}
	else if (!isdigit(*eggs)) {
		printf("Your arguments are invalid\n");
		return false;
	}
	else {
		return true;
	}
}

bool quadratic_search(double floors, int eggs, egg **carton)
{
	printf("Quadratic search\n");
	size_t step = pick_floor(floors);

	if(eggs == 1) {
		step = 1;
	}

	size_t guess = 0;
	size_t last_good_floor = 0;
	int total_count = 0;
	int limit = 0;

	while(eggs >= 1) {
		guess += step;

		if(guess > floors) {
			printf("Limit is to great\n");
			limit = 1;
			break;
		}
	
		egg_drop_from_floor(carton[eggs - 1], guess);

		if(egg_is_broken(carton[eggs - 1])) {
			printf("EGG CRACKED at floor %ld\n", guess);
			eggs--;



			if(guess - last_good_floor == 1) {
				break;
			}

			if(eggs == 1) {
				step = 1;
			}
			else {
				step = pick_floor(guess - last_good_floor);
			}

			if(eggs == 0) {
				printf("There is no safe floor\n");
				return true;
			}

			guess = last_good_floor;

		}
		else {
			printf("EGG SURVIVED at floor %ld\n", guess);
			last_good_floor = guess;
			if(step > 1) {
				--step;
			}
		}

		total_count++;
	}

	if(limit == 0) {
		printf("%zd is the maximum safe floor, found after %d drops\n", last_good_floor, total_count);
	}
	else {
		printf("I can not give you a safe dropping floor limit\n");
	}

	return true;
}

bool binary_search(double floors, int eggs, egg **carton)
{
	//seperate into there own functions
	//if(eggs > log(floors)) {
	printf("Binary search\n");
	size_t guess = floors/2;
	size_t last_good_floor = 0;
	size_t step = 0;
	int total_count = 0;
	int limit = 0;

	if(eggs == 1) {
		guess = 1;
	}


	while(eggs >= 1) {

		if(guess > floors) {
			printf("Limit is to great\n");
			limit = 1;
			break;
		}

		egg_drop_from_floor(carton[eggs - 1], guess);
		step = guess - last_good_floor;
		if(step < 2) {
			step = 2;
		}

		if(egg_is_broken(carton[eggs - 1])) {
			printf("EGG CRACKED at floor %ld\n", guess);
			eggs--;
			size_t tmp = last_good_floor + (step/2);

			if(tmp == guess) {
				printf("You passed your limit\n");
				break;
			}
			else {
				guess = tmp;
			}


		}
		else {
			printf("EGG SURVIVED at floor %ld\n", guess);
			last_good_floor = guess;
			guess = guess + (step/2);
		}

		total_count++;
	}

	if(limit == 0) {
		printf("%zd is the maximum safe floor, found after %d drops\n", last_good_floor, total_count);
	}
	else {
		printf("Your at the end of the building, your max safe drop is %zd\n", last_good_floor);
	}

	return true;
}
