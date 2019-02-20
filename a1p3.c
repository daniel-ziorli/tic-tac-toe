/*
a1p3.c
Name: Daniel Ziorli
Student ID: 1016491
Email: dziorli@uoguelph.ca
Date: 01/29/2018
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tictactoe.h"


int main(int argc, char *argv[]){

	/* initialize variables */
	FILE *fp;
	int index;
	char input_move;

	char current_move;
	struct strategy_struct temp_strategy_struct;

	char b3[10];

	/* check if right amount of arguments were passed */
	if (argc != 2) {
        fprintf(stderr, "Erorr: Usage: %s [n]\n", argv[0]);
        exit(-1);
    }

    input_move = *argv[1];
	fp = fopen("strategyfile", "rb+");

    /* loops through every possible tictactoe board */
	for (index = 0; index < 19683; index ++){
		b3fromus(b3, index);
		current_move = get_move(b3);

		/* checks if current boards move matches the argument move */
		if (current_move == input_move){

			/* checks if board has a win state otherwise evaluates */
			if (winner(index) != ' '){
				temp_strategy_struct.winner = winner(index);
				temp_strategy_struct.best_move = -1;
			}
			else{
				evaluate_move(fp, index, &temp_strategy_struct);
			}
			/* writes data to strategyfile */
			write_strategy_file(fp, temp_strategy_struct, index);
		}
	}
	fclose(fp);
	return 0;
}