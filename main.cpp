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
        //Convert input to lowercase first character (x or o)
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
    return 0;
}