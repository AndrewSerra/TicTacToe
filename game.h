/*
 *  Title: game.h
 *  Course: Computational Problem Solving 1 (CPET-121)
 *  Developer: Andrew Serra
 *  Date: 02/21/2019
 *  Description: Best implementation - Tic Tac Toe game
 *               header file for prototype functions
 */

#ifndef DEMO_GAME_H
#define DEMO_GAME_H

// Enables data type 'std::string'
#include <iostream>



// game.cpp
void removeOldGameState(void);
void drawGame(std::string);
void gameLoop(void);

// gameControl.cpp
void coinToss(bool&);
void userChooseMarker(void);
void userPlay(void);
void computerPlay(std::string&);
bool setNewGameStateValue(int, bool);
bool isChoiceValid(int, bool);
void didGameEnd(bool&);
void displayResult(bool&, char);
void displayWarning(std::string);
int getRandomNumber(int, int);

#endif //DEMO_HELPERFUNCTIONS_H
