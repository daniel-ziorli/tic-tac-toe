/*
a1p2.c
Name: Daniel Ziorli
Student ID: 1016491
Email: dziorli@uoguelph.ca
Date: 01/29/2018
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tictactoe.h"

int main(int argc, char *argv[])
{
	/* initialize variables */
	int i;
	FILE *fp = fopen("strategyfile", "wb+");

	struct strategy_struct temp_strategy_struct;
	temp_strategy_struct.best_move = -1;
	temp_strategy_struct.winner = ' ';

	/* loops through possible boards writing default -1 to best move and ' ' to winner */
	for (i=0; i < 19683; i++){
		write_strategy_file(fp, temp_strategy_struct, i);
	}
	fclose(fp);
	return 0;
}