/*
a1p5.c
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
	char name[100];
	char player_choice[10];
	int got_player_choice = 0;
	char player_turn = '0';
	int has_won = 0;
	unsigned short board_us = 0;
	char b3[10];
	FILE *fp = fopen("strategyfile", "rb+");
	struct strategy_struct temp_strategy_struct;

	printf("SHALL WE PLAY A GAME?\n");
	printf("PLEASE ENTER YOUR NAME: ");

	scanf("%s", name);
	printf("\nGREETINGS %s\n", name);

	/* loop until player inputs a valid choice */
	while (got_player_choice == 0){
		printf("Which side would you like to play (X/O)? ");
		scanf("%s", player_choice);
		printf("\n");
		if (player_choice[0] == 'X'){
			got_player_choice = 1;
			player_turn = '2';
		}
		else if (player_choice[0] == 'O'){
			got_player_choice = 1;
			player_turn = '1';
		}
	}
	if (player_turn == 1){
		printf("Ok, you will be O; I will be X.\n");
	}
	else{
		printf("Ok, you will be X; I will be O.\n");
	}

	draw_game_board(board_us);


	/* loops until a winning or braw state occurres */
	while (has_won == 0){
		b3fromus(b3, board_us);

		/* reads the best move for current board */
		read_strategy_file(fp, &temp_strategy_struct, board_us);

		/* checks who's turn it is */
		if (get_turn(b3) == player_turn){
			/* get's players move and plays that board */
			printf("My turn; chose a move [0-8]: ");
			do {
				scanf("%s", player_choice);
				board_us = next(board_us, player_choice[0]);
			} while (board_us == 0);
		}
		else{
			/* players the best move read from strategyfile */
			printf("My turn; my move is %d: \n", temp_strategy_struct.best_move);

			board_us = next(board_us, temp_strategy_struct.best_move + '0');
		}

		/* checks if board has a winning state */
		draw_game_board(board_us);
		if(winner(board_us) == '0' || (int)winner(board_us) == '1' || (int)winner(board_us) == '2'){
				has_won = 1;
		}
	}

	if (winner(board_us) != '0'){
		printf("I won!\n\n");
	}
	else{
		printf("The game is a tie.\n\n");
	}

	printf("A STRANGE GAME.\nTHE ONLY WINNING MOVE\nIS NOT TO PLAY.\n");

	return 0;
}