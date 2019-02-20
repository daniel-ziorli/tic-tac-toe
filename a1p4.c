/*
a1p4.c
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
	unsigned short us;

	/* check if right amount of arguments were passed */
	if (argc != 2) {
        fprintf(stderr, "Erorr: Usage: %s [n]\n", argv[0]);
        exit(-1);
    }
	
	us = atoi(argv[1]);

    /* draws the best move board using inputed argument */
	draw_best_move_board(us);
	return 0;
}