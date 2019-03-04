/*
 *  Title: gameControl.cpp
 *  Course: Computational Problem Solving 1 (CPET-121)
 *  Developer: Andrew Serra
 *  Date: 02/21/2019
 *  Description: Best implementation - Tic Tac Toe game
 *               functions that control game play
 */

#include "game.h"
#include <iostream>
#include <ctime>
#include <zconf.h>

// For debugging
#include <typeinfo>

std::string game_state_values = "123456789";
char user_marker = ' ';
char comp_marker = ' ';

// Gets input for coin toss choice
// Decides who starts
// Displays coin animation
void coinToss(bool& user_starts) {
    // Heads --> 0
    // Tails --> 1
    bool valid_selection;
    int coin_toss_choice_num;
    std::string coin_toss_choice;

    std::cout << "\nCoin toss to start the game!";

    // Repeats until user enters valid input
    do {
        std::cout << "\nHeads or Tails? ";
        std::cin >> coin_toss_choice;

        // Assign 0 if user picks heads
        if (coin_toss_choice == "Heads" || coin_toss_choice == "heads") {
            coin_toss_choice_num = 0;
            valid_selection = true;
        }
        // Assign 1 if user picks tails
        else if (coin_toss_choice == "Tails" || coin_toss_choice == "tails") {
            coin_toss_choice_num = 1;
            valid_selection = true;
        }
        // Display warning
        else {
            displayWarning("Invalid entry. Try again.");
            valid_selection = false;
        }
    } while(!valid_selection);

    // Coin animation
    std::cout <<  "Throwing coin.... -";
    for(int i=0; i<0; i++) {

        sleep(1);
        std::cout << "\rThrowing coin.... \\" << std::flush;
        sleep(1);
        std::cout << "\rThrowing coin.... |" << std::flush;
        sleep(1);
        std::cout << "\rThrowing coin.... /" << std::flush;
        sleep(1);
        std::cout << "\rThrowing coin.... -" << std::flush;
    }

    // If random number is equal to the user pick
    // User starts
    if (getRandomNumber(0, 2) == coin_toss_choice_num) {
        user_starts = true;
    }
    // Computer starts
    else {
        user_starts = false;
    }
}

// User decides which marker they would
// like to have
void userChooseMarker(void) {
    bool valid_selection = false;

    // Repeats until the user enters valid
    // character 'X' or 'O'
    do {
        // Let user choose marker
        std::cout << "\nChoose your marker ['X' / 'O']: ";
        std::cin >> user_marker;

        // If X assign marker
        if (user_marker == 'X' || user_marker == 'x') {
            // Set markers
            user_marker = 'X';
            comp_marker = 'O';
            valid_selection = true;
        }
        // If O assign marker
        else if (user_marker == 'O' || user_marker == 'o') {

            // Set markers
            user_marker = 'O';
            comp_marker = 'X';
            valid_selection = true;
        }
        // Warning message display
        else {
            displayWarning("Check your selection, has to be 'X' or 'O'");
        }
    } while (!valid_selection);
}

// User's turn to play
// Get input and repeat if invalid choice
void userPlay(void) {

    int user_choice;

    // Repeats until there is a valid position
    // input from the user
    do {

        // Asks for input checks if entered
        std::cout << "\nEnter your position: ";
        if(std::cin >> user_choice) {
            continue;
        }

        // Added if type 'int' in not entered
        // by the user, prevents infinite loop
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (!isChoiceValid(user_choice, true));
}

// Computer's turn to play
// Random numbers decide the move
// Repeats if position occupied
void computerPlay(std::string& message) {

    int random_move;

    // Repeats until the computer gets a
    // random number that is unoccupied
    do {

        // Gets random number to play
        random_move = getRandomNumber(1, 9);

    } while (!isChoiceValid(random_move, false));

    // Set message to display to user when
    // game is drawn in gameLoop()
    message = "Computer plays position " + std::to_string(random_move);
}

// Changes the game_state_values string to add new move
// Returns true if value set successfully
bool setNewGameStateValue(int move, bool isUserChoice) {

    // Find the index of the entered move
    std::size_t index = game_state_values.find(std::to_string(move));

    // If index set, move valid
    // Else move cannot be found not valid.
    if (index != std::string::npos) {

        // If user's turn user marker choice of user
        if(isUserChoice) {
            game_state_values[index] = user_marker;
        }
        else {
            game_state_values[index] = comp_marker;
        }
        return true;
    }
    else {

        // If user's turn display warning
        if(isUserChoice) {
            displayWarning("Move not valid. Choose a spot containing a numerical value.");
        }

        return false;
    }
}

// Checks if the player choice is valid and free
// If not valid output warning
bool isChoiceValid(int choice, bool isUser) {

    // If user's turn, check value
    if(isUser) {
        if(choice >= 1 && choice <= 9) {

            // Check if the choice is occupied in game_state_values
            bool choice_successful = setNewGameStateValue(choice, isUser);

            return choice_successful;
        }
        else {

            // Display warning to user if position
            // is occupied
            displayWarning("Please enter a valid integer. Entered value must be a number shown on the game display.");

            return false;
        }
    }
    // No need to check range, computer is already set
    else {

        // Check if the choice is occupied in game_state_values
        bool choice_successful = setNewGameStateValue(choice, isUser);

        return choice_successful;
    }
}

// Check if there is a winner of the game.
// Displays the winner
void didGameEnd(bool& game_ended) {

    // Check every row
    for(int i=0; i <= 6; i += 3) {
        if(game_state_values[i] == game_state_values[i+1]
            && game_state_values[i+1] == game_state_values[i+2]) {

            // Game winner, display result
            game_ended = true;
            displayResult(game_ended, game_state_values[i]);
        }
    }

    // Check every column,
    // if previous conditions have not ended the game
    for(int i=0; i <= 2; i++) {
        if(game_state_values[i] == game_state_values[i+3]
           && game_state_values[i+3] == game_state_values[i+6]
           && game_ended == false) {

            // Game winner, display result
            game_ended = true;
            displayResult(game_ended, game_state_values[i]);
        }
    }

    // Check cross
    // Left
    // if previous conditions have not ended the game
    if(game_state_values[0] == game_state_values[4]
        && game_state_values[4] == game_state_values[8]
        && game_ended == false) {

        // Game winner, display result
        game_ended = true;
        displayResult(game_ended, game_state_values[0]);
    }
    // Right
    // if previous conditions have not ended the game
    else if(game_state_values[2] == game_state_values[4]
            && game_state_values[4] == game_state_values[6]
            && game_ended == false) {

        // Game winner, display result
        game_ended = true;
        displayResult(game_ended, game_state_values[2]);
    }

    // Check tie game,
    // if previous conditions have not ended the game
    if (game_ended == false) {

        // go through values to see if all values are filled
        for(int i=0; i < game_state_values.length(); i++) {

            if (game_state_values[i] != 'X' && game_state_values[i] != 'O') {

                // Number in game_state_values
                // Game continues, no tie game
                game_ended = false;
                break;
            }
            else if (i == game_state_values.length() - 1) {

                // No number left
                // Game winner, display result
                game_ended = true;
                displayResult(game_ended, ' ');
            }
        }
    }
}

// Displays the game result to the user
void displayResult(bool& game_state, char winner) {

    // Clear screan
    removeOldGameState();

    // Draw the game with final user input and display
    drawGame("");

    // If game ended, and user wins.
    if (game_state == true && winner == user_marker) {
        std::cout << "\n\nYou have won!";
    }
    // If game ended, and user loses.
    else if (game_state == true && winner == comp_marker) {
        std::cout << "\n\nYou have lost... Computer Wins.";
    }
    else {
        std::cout << "\n\nTie game!" << std::endl;
    }

}

// Displays warning message
void displayWarning(std::string message) {
    std::cout << "Warning: " << message << std::endl;
}

// Returns a random number in the specified range
int getRandomNumber(int min, int range) {

    int rand_val;

    rand_val = (rand() % range) + min;

    return rand_val;
}