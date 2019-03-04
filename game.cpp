/*
 *  Title: game.cpp
 *  Course: Computational Problem Solving 1 (CPET-121)
 *  Developer: Andrew Serra
 *  Date: 02/21/2019
 *  Description: Best implementation - Tic Tac Toe game
 *               game drawing, clearing, and game loop file
 */
#include "game.h"
#include <iostream>
#include <iomanip>
#include <ctime>

#define NUM_ROWS 11
#define CELL_WIDTH 6

extern std::string game_state_values;
extern char user_marker;
extern char comp_marker;

// Clears the screen
// Work around to not use system("clear")
void removeOldGameState(void) {
    for (int i=0; i < 10; i++) {
        std::cout << "\n\n\n\n\n\n\n\n\n\n";
    }
}

void drawGame(std::string comp_move_message) {

    // Display computer move to user
    std::cout << comp_move_message << std::endl << std::endl;

    std::cout << std::setw(17) << "Tic Tac Toe\n\n"
              << "User (" << user_marker << ")   Computer (" << comp_marker << ")\n\n";

    // For loop for rows
    for(int i=0; i < NUM_ROWS; i++) {

        switch(i + 1) {
            case 2:
            case 6:
            case 10:
                // Rows that include box numbers, "X" or "O"
                for(int j=0; j <= 2; j++) {
                    // Determine which row we are on
                    // to display appropriate value
                    if (i + 1 == 2) {
                        std::cout << std::setw(CELL_WIDTH / 2) << std::right << game_state_values.at(j);
                    }
                    else if (i + 1 == 6) {
                        std::cout << std::setw(CELL_WIDTH / 2) << std::right << game_state_values.at(j + 3);
                    }
                    else if (i + 1 == 10) {
                        std::cout << std::setw(CELL_WIDTH / 2) << std::right << game_state_values.at(j + 6);
                    }

                    // If in last column do not put separator
                    if(j != 2) {
                        std::cout << std::setw(CELL_WIDTH / 2) << '|';
                    }
                    else {
                        std::cout << std::setw(CELL_WIDTH / 2) << ' ';
                    }
                }
                break;
            case 4:
            case 8:
                // Horizontal lines
                for(int j=0; j <= 2; j++) {
                    std::cout << std::setw(CELL_WIDTH) << std::setfill('-') << ' ';
                }
                break;
            default:
                // Iterate over columns
                for(int j=0; j <= 2; j++) {
                    std::cout << std::setw(CELL_WIDTH) << std::setfill(' ');

                    if(j != 2) {
                        std::cout << '|';
                    }
                }
                break;
        }
        // Line break for next row
        std::cout << std::endl;
    }
}

void gameLoop(void) {

    bool game_ended = false,
         user_starts;
    int loop_count = 0;

    std::string computer_move_message = "";

    // Use time as seed for more random results
    srand(time(NULL));

    // Allow user to choose a marker
    userChooseMarker();

    // Coin Toss
    coinToss(user_starts);

    // Game loop
    while (!game_ended) {

        if(loop_count == 0){

            // Display who won coin toss
            // Only runs first iteration
            if (user_starts) {
                std::cout << "\n\nUser won coin toss.\n\n";
            }
            else {
                std::cout << "\n\nComputer won coin toss.\n\n";
            }
        }

        if ((loop_count > 0 && user_starts) || (loop_count > 1 && !user_starts)) {

            // Clears screen by adding multiple new lines
            removeOldGameState();
        }

        // Check game ending possibility
        // after five moves
        if (loop_count >= 5) {
            didGameEnd(game_ended);

            if (game_ended == true) {
                break;
            }
        }

        // Change who starts game according to coin toss result
        if(loop_count % 2 != user_starts) {

            // Draw game using the current status and
            // user chosen marker
            drawGame(computer_move_message);
            userPlay();
        }
        else {
            computerPlay(computer_move_message);
        }

        ++loop_count;
    }
}