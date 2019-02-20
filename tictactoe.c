/*
tictactoe.c
Name: Daniel Ziorli
Student ID: 1016491
Email: dziorli@uoguelph.ca
Date: 01/29/2018
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tictactoe.h"


int power(int base, int power){

	/* takes a base and raises it to the power. */
	int return_value = 1;
	int index = 0;
	for(index = 0; index < power; index++){
		return_value *= base;
	}
	return return_value;
}

unsigned short b3tous(char b3[10]){
	
	/* takes a b3 and returns the unsigned short value for the board. */
	unsigned short return_value = 0;
	int current_power = 8;
	int index = 0;

	for(index=0; index < 9; index++){
		return_value += (b3[index] - '0') * power(3, current_power);
		current_power--;
	}
	return return_value;
}

void b3fromus(char b3[10], unsigned short us ){

	/* takes a unsigned short and returns b3 value for the board. */
	int remainder = -1;
	int base_into_us = us;
	int index = 0;

	for(index=8; index >= 0; index--){
		remainder = base_into_us % 3;
		base_into_us /= 3;
		b3[index] = remainder + '0';
	}
	b3[9] = '\0';
}

void boardtob3(char b3[10], char board[60]){

	/* takes a board and returns b3 value for that board. */
	int index_of_board_info[9] = { 1, 5, 9, 25, 29, 33, 49, 53, 57};
	int index = 0;

	for (index=0; index < 9; index++){
		if(board[index_of_board_info[index]] == ' '){
			b3[index] = '0';
		}
		if(board[index_of_board_info[index]] == 'X'){
			b3[index] = '2';
		}
		if(board[index_of_board_info[index]] == 'O'){
			b3[index] = '1';
		}
	}
	b3[9] = '\0';
}

void boardfromb3(char board[60], char b3[10]){

	/* takes a b3 and returns string of the board. */
	int index_of_board_info[9] = { 1, 5, 9, 25, 29, 33, 49, 53, 57};
	int index = 0;
	strcpy(board, "   |   |   \n---+---+---\n   |   |   \n---+---+---\n   |   |   ");

	for (index=0; index < 9; index++){
		if(b3[index] == '0'){
			board[index_of_board_info[index]] = ' ';
		}
		if(b3[index] == '1'){
			board[index_of_board_info[index]] = 'O';
		}
		if(b3[index] == '2'){
			board[index_of_board_info[index]] = 'X';
		}
	}
}

unsigned short next (unsigned short us, char pos){

	/*
	looks at the next board if move is placed at the passed position, if
	the move is illegal a default board is returned. if the move is legal
	the next function will return the new board as a unsigned short.
	*/
	char b3[10];
	char next_move;
	b3fromus(b3, us);
	next_move = get_turn(b3);

	if (b3[pos - '0'] == '0'){
		b3[pos - '0'] = next_move;
		return b3tous(b3);
	}
	else{
		return 0;
	}


}

char winner(unsigned short us){

	/*
	looks at all possible win, tie states and checks if any
	return true. otherwise it will return ' ' meaning there are
	still possible moves to be made.
	*/
	int index = 0;
	char b3[10];
	int has_open_spot = 0;
	b3fromus(b3, us);

	for (index=0; index < 3; index++){
		if (b3[3 * index] == '2' &&  b3[3 * index + 1] == '2' && b3[3 * index + 2] == '2')
			return '2';
		else if (b3[3 * index] == '1' &&  b3[3 * index + 1] == '1' && b3[3 * index + 2] == '1')
			return '1';

		if (b3[index] == '2' &&  b3[3 + index] == '2' && b3[6 + index] == '2')
			return '2';
		else if (b3[index] == '1' &&  b3[3 + index] == '1' && b3[6 + index] == '1')
			return '1';
	}

	if (b3[4] == '2'){
		if ((b3[0] == '2' && b3[8] == '2') || (b3[2] == '2' && b3[6] == '2')){
			return '2';
		}
	}
	else if (b3[4] == '1'){
		if ((b3[0] == '1' && b3[8] == '1') || (b3[2] == '1' && b3[6] == '1')){
			return '1';
		}
	}

	for (index=0; index < 9; index++){
		if(b3[index] == '0'){
			has_open_spot = 1;
		}
	}
	if (has_open_spot == 1){
		return ' ';
	}
	else{
		return '0';
	}
	
}

char get_move(char b3[10]){

	/* gets the currents boards move and returns it as a char. */
	int index = 0;
	int sum_of_moves = 0;

	for (index=0; index < 9; index++){
		if (b3[index] == '2' || b3[index] == '1'){
			sum_of_moves += 1;
		}
	}

	return sum_of_moves + '0';
}

char get_turn(char b3[10]){

	/* gets the currents boards turn and returns it as a char. */
	int sum_of_moves;
	sum_of_moves = get_move(b3) - '0';
	if (sum_of_moves % 2 == 0){
		return '2';
	}
	else{
		return '1';
	}
}

void evaluate_move(FILE *fp, unsigned short current_board_us, struct strategy_struct *data){

	/* 
	first begins to loop over every possible next move checking if there is a win
	state for the current player (current player can make a winning move) and writes to file
	and return. if it deosnt find a winning move it looks for a tieing move and writes to file. if there
	is no tieing or winning state it will return any legal move that can be made and sets winning value
	to other player and writes to file.
	*/
	int index;
	unsigned short next_board_us;
	struct strategy_struct temp_strategy_file;
	char current_board_b3[10];
	char current_player;
	int found_tie = 0;
	int tie_move;
	int legal_move;

	b3fromus(current_board_b3, current_board_us);
	current_player = get_turn(current_board_b3);

	for (index = 0; index < 9; index++){
		next_board_us = next(current_board_us, index + '0');

		if (next_board_us > 0){

			read_strategy_file(fp, &temp_strategy_file, next_board_us);

			if(temp_strategy_file.winner == current_player){
				data->winner = temp_strategy_file.winner;
				data->best_move = index;
				return;
			}
			else if (temp_strategy_file.winner == '0'){
				found_tie = 1;
				tie_move = index;
			}
			else{
				legal_move = index;
			}
		}
	}

	if (found_tie == 1){
		data->winner = '0';
		data->best_move = tie_move;
	}
	else{
		data->best_move = legal_move;
		if (current_player == '2'){
			data->winner = '1';
		}
		else{
			data->winner = '2';
		}
		
	}
}

void write_strategy_file(FILE *fp, struct strategy_struct data, int position){

	/* writes startegy_struct data as binary to strategyfile. */
	fseek(fp, (position * sizeof(struct strategy_struct)), SEEK_SET);
	fwrite(&data, sizeof(struct strategy_struct), 1, fp);
}

void read_strategy_file(FILE *fp, struct strategy_struct *data, int position){

	/* reads startegy_struct data from strategyfile. */
	fseek(fp, (position * sizeof(struct strategy_struct)), SEEK_SET);
	fread(data, sizeof(struct strategy_struct), 1, fp);
}

void draw_board(unsigned short us){

	/* 
	draws tictactoe board with the board number, base 3 representation, the
	current move, the current move, the winner if one exists and finally
	all the possible boards at positions 0-8.
	*/
	int index;
	char b3[10];
	char b[60];

	b3fromus(b3, us);

	printf("Board number: %d\n", us);
	printf("Board b3: %s\n", b3);

	boardfromb3(b, b3);
	printf("Board pic:\n%s\n", b);

	printf("Move: %c\n", get_move(b3));
	printf("Turn: %c\n", get_turn(b3));
	printf("winner: %c\n", winner(b3tous(b3)));

	for (index = 0; index < 9; index++){
		printf("%d -> %d\n", index, next(us, index + '0'));
	}
}

void draw_best_move_board(unsigned short us){

	/* draws tictactoe board with winning state and best move also displayed. */
	int index;
	char b3[10];
	char b[60];
	struct strategy_struct temp_strategy_struct;

	FILE *fp = fopen("strategyfile", "rb+");
	read_strategy_file(fp, &temp_strategy_struct, us);

	b3fromus(b3, us);

	printf("Board number: %d\n", us);
	printf("Board b3: %s\n", b3);

	boardfromb3(b, b3);
	printf("Board pic:\n%s\n", b);

	printf("Move: %c\n", get_move(b3));
	printf("Turn: %c\n", get_turn(b3));
	printf("Winner: %c\n", winner(us));
	printf("best_move=%d, winner=%c\n",  temp_strategy_struct.best_move, temp_strategy_struct.winner);

	for (index = 0; index < 9; index++){
		printf("%d -> %d\n", index, next(us, index + '0'));
	}
}

void draw_game_board(unsigned short us){

	/* draws tictactoe board. */
	char b3[10];
	char b[60];

	b3fromus(b3, us);

	boardfromb3(b, b3);
	printf("\n%s\n\n", b);
}