/*
 *  Title: tictactoe.cpp
 *  Course: Computational Problem Solving 1 (CPET-121)
 *  Developer: Andrew Serra
 *  Date: 02/21/2019
 *  Description: Best implementation - Tic Tac Toe game
 *               main function file
 */

#include <iostream>
#include "game.h"

int main(void) {

    std::cout << "Welcome to the game of Tic Tac Toe.\n"
              << "Below you will indicate your position (1 - 9) as shown in the table.\n\n\n";

    gameLoop();

    return 0;
}