/*
tictactoe.h
Name: Daniel Ziorli
Student ID: 1016491
Email: dziorli@uoguelph.ca
Date: 01/29/2018
*/

#ifndef TICTACTOE_H
#define TICTACTOE_H

struct strategy_struct{
    char best_move;
    char winner;
};

int power(int base, int power);
unsigned short b3tous(char b3[10]);
void b3fromus(char b3[10], unsigned short us);
void boardtob3(char b3[10], char board[60]);
void boardfromb3(char board[60], char b3[10]);
unsigned short next (unsigned short us, char pos);
char winner(unsigned short us);
char get_move(char b3[10]);
char get_turn(char b3[10]);
void evaluate_move(FILE *fp, unsigned short us, struct strategy_struct *data);
void write_strategy_file(FILE *fp, struct strategy_struct data, int position);
void read_strategy_file(FILE *fp, struct strategy_struct *data, int position);
void draw_board(unsigned short us);
void draw_best_move_board(unsigned short us);
void draw_game_board(unsigned short us);

#endif