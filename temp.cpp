/*Clint Scholtisek
 * CS201 end of semester project
 * 04/19/2021
 * Jon Genetti
 * This program is a simple tic-tac-toe game
 * The computer opponent uses randomization and win conditions
 */
#include <iostream>
using std::cout;
using std::cin;
using std::endl;
#include <vector>
using std::vector;
#include <string>
using std::string;
#include <random>
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;

//print tic-tac-toe board with slot values in place
void printboard(vector<string>& slot){
    for (int i = 0; i < 10; i++){
        if (!slot[i].empty()) {
            if (i % 3 == 0 and i != 0) {
                cout << slot[i] << endl;
                if (i != 9) cout << "---------------" << endl;
            }
            if (i % 3 != 0) {
                cout << " " << slot[i] << " " << " | ";
            }
        } else{
            if (i % 3 == 0 and i != 0) {
                cout << " " << endl;
                if (i != 9) cout << "---------------" << endl;
            }
            if (i % 3 != 0) {
                cout << "   " << " | ";
            }
        }
    }
    cout << endl;
}

//Check if a win condition is met and if so, print who won and by what condition
bool wincheck(vector<string>& slot, string& player_char){

    //check for horizontal win
    for (int i = 0; i < 9; i+=3) {
        if (slot.at(1+i) == slot.at(2+i) and slot.at(2+i) == slot.at(3+i)) {
            if (slot.at(1+i) == player_char) {
                //player win
                cout << "You win! (" << 1+i << ", " << 2+i << ", " << 3+i << ")" << endl;
                return true;
            } if (!slot.at(1+i).empty()) {
                //ai win
                cout << "AI win! (" << 1+i << ", " << 2+i << ", " << 3+i << ")" << endl;
                return true;
            } else{
                return false;
            }
        }
    }

    //check for vertical win
    for (int i = 0; i < 3; i+=1) {
        if (slot.at(1+i) == slot.at(4+i) and slot.at(4+i) == slot.at(7+i)) {
            if (slot.at(1+i) == player_char) {
                //player win
                cout << "You win! (" << 1+i << ", " << 4+i << ", " << 7+i << ")" << endl;
                return true;
            } if (!slot.at(1+i).empty()) {
                //ai win
                cout << "AI win! (" << 1+i << ", " << 4+i << ", " << 7+i << ")" << endl;
                return true;
            } else{
                return false;
            }
        }
    }

    //check for diagonal win
    for (int i = 0; i < 2; i+=1) {
        if (slot.at(1+2*i) == slot.at(5) and slot.at(5) == slot.at(9-2*i)) {
            if (slot.at(1+2*i) == player_char) {
                //player win
                cout << "You win! (" << 1+2*i << ", " << 5 << ", " << 9-2*i << ")" << endl;
                return true;
            } if (!slot.at(1+2*i).empty()) {
                //ai win
                cout << "AI win! (" << 1+2*i << ", " << 5 << ", " << 9-2*i << ")" << endl;
                return true;
            } else{
                return false;
            }
        }
    }
}

//function for determining what the best play is for the AI
//recognizes potential wins and potential losses and plays accordingly
//If no best play, plays random slot
int aiplayfunc(vector<string>& slot){
    //Generate random seed
    random_device rd;
    mt19937 gen{rd()};
    uniform_int_distribution<int> distrib{1, 9};
    int randval = distrib(gen);

    bool AI_loop = true;
    do {

        //Check horizontals for potential win or block
        for (int i = 0; i < 9; i+=3) {
            //if 2 and 3 are same play 1
            if (slot.at(2+i) == slot.at(3+i) and !slot.at(2+i).empty() and slot.at(1+i).empty()) {
                return 1+i;
            }
            //if 1 and 3 are same play 2
            if (slot.at(1+i) == slot.at(3+i) and !slot.at(1+i).empty() and slot.at(2+i).empty()) {
                return 2+i;
            }
            //if 1 and 2 are same play 3
            if (slot.at(1+i) == slot.at(2+i) and !slot.at(1+i).empty() and slot.at(3+i).empty()) {
                return 3+i;
            }
        }
        //Check verticals for potential win or block
        for (int i = 0; i < 3; i+=1) {
            //if 1 and 4 are same play 7
            if (slot.at(1+i) == slot.at(4+i) and !slot.at(1).empty() and slot.at(7+i).empty()) {
                return 7+i;
            }
            //if 4 and 7 are same play 1
            if (slot.at(4+i) == slot.at(7+i) and !slot.at(4).empty() and slot.at(1+i).empty()) {
                return 1+i;
            }
            //if 1 and 7 are same play 4
            if (slot.at(1+i) == slot.at(7+i) and !slot.at(1).empty() and slot.at(4+i).empty()) {
                return 4+i;
            }
        }

        //Check diagonals for potential win or block
        for (int i = 0; i < 2; i+=1) {
            //if slot 1 and 5 are same play 9
            if (slot.at(1+2*i) == slot.at(5) and !slot.at(5).empty() and slot.at(9-2*i).empty()) {
                return 9-2*i;
            }
            //if slot 5 and 9 are same play 1
            if (slot.at(5) == slot.at(9-2*i)and !slot.at(5).empty() and slot.at(1+2*i).empty()) {
                return 1+2*i;
            }
            //if slot 1 and 9 are same play 5
            if (slot.at(1+2*i) == slot.at(9-2*i) and !slot.at(1+2*i).empty() and slot.at(5).empty()) {
                return 5;

            }
        }

        //if none of checks pass, choose randomly
        //choose random different slot if slot taken
        if (slot.at(randval).empty()) {
            AI_loop = false;
            return randval;
        } else {
            randval = distrib(gen);
        }

    } while (AI_loop);
}

int main() {
    //initialize slot vector
    vector<string> slot(10);

    //Intro
    cout << "Welcome to Tic Tac Toe" << endl;
    cout << "This is the board layout" << endl;
    cout << " 1  |  2  |  3\n"
            "---------------\n"
            " 4  |  5  |  6\n"
            "---------------\n"
            " 7  |  8  |  9" << endl;


    //Choose X or O
    string player_char;
    char ai_char;
    //do loop for valid character input
    do {
        cout << "Choose character (x or o)" << endl;
        //do loop in case empty character input
        do {
            getline(cin, player_char);
            if (player_char.empty()) {
                cout << "Please enter a valid character (x or o)" << endl;
            }
        } while(player_char.empty());
        //Convert input to lowercase first character
        player_char = ::tolower(player_char.at(0));

        //assign AI opponent opposite character
        if (player_char == "x" or player_char == "o") {
            cout << "You chose " << player_char << endl;
            if (player_char == "x") {
                ai_char = 'o';
            } else{
                ai_char = 'x';
            }
        } else{
            cout << "Error, please enter x or o" << endl;
        }
    } while(player_char != "x" and player_char != "o");

    //play
    string playerpos;
    bool turnloop = true;
    int loopnum = 0;
    bool playerposloop;
    //loop for each turn
    do {
        //Player play
        //loop if selected slot is taken
        do {
            playerposloop = true;
            //loop if input is not number
            do {
                cout << "Place your character! (1-9)" << endl;
                getline(cin, playerpos);
                if (!(playerpos == "1" or playerpos == "2" or playerpos == "3" or
                      playerpos == "4" or playerpos == "5" or playerpos == "6" or
                      playerpos == "7" or playerpos == "8" or playerpos == "9")) {
                    cout << "Please enter a valid integer 1-9" << endl;
                }
            } while (!(playerpos == "1" or playerpos == "2" or playerpos == "3" or
                       playerpos == "4" or playerpos == "5" or playerpos == "6" or
                       playerpos == "7" or playerpos == "8" or playerpos == "9"));

            //check if spot is taken
            if (slot.at(stoi(playerpos)).empty()) {
                slot.at(stoi(playerpos)) = player_char;
                playerposloop = false;
            } else {
                cout << "Selected slot is already taken! Please choose a different slot" << endl;
            }
        } while(playerposloop);
        printboard(slot);

        //skip tie check if win condition is met
        bool skiptie = false;

        //check if wincon is met before AI plays
        if (wincheck(slot,player_char)){
            turnloop = false;
            skiptie = true;
        }

        //AI play
        if (loopnum != 4 and turnloop) {
            int aiplay = aiplayfunc(slot);
            slot.at(aiplay) = ai_char;
            cout << "AI plays slot " << aiplay << endl;
            printboard(slot);
        }

        //check if wincon is met after AI plays
        if (turnloop){
            if(wincheck(slot,player_char)) {
                turnloop = false;
                skiptie = true;
            }
        }

        loopnum += 1;
        //if slots are all filled, stop game
        if (loopnum == 5){
            turnloop = false;
            //check if no winner
            if (!skiptie) {
                cout << "Tie game!" << endl;
            }
        }
    } while(turnloop);

    //play again
    string playagain;
    cout << "Play again? (Y or N)" << endl;
    //do loop for valid y or n input
    do {
        //do loop in case play again input string is empty
        do {
            getline(cin, playagain);
            if (playagain.empty()) {
                cout << "Please enter Y or N" << endl;
            }
        } while(playagain.empty());

        //convert playagain string to lower case first character
        playagain = ::tolower(playagain.at(0));
        if (playagain == "y") {
            main();
        }
        if (playagain == "n") {
            cout << "Thanks for playing!" << endl;
            return 0;
        } else {
            cout << "Please enter Y or N" << endl;
        }
    } while (playagain != "y" and playagain != "n");

    return 0;
}