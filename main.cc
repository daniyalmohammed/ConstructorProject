#include "board.h"
using namespace std;

void during_turn(Board b){
    string cmd;
    cout << "> ";
    while (cin >> cmd) {
        if (cmd == "board") { // prints the current board
            b.printBoard(); //DONE
        } 
        else if (cmd == "status") { // prints the current status of all builders in order from builder 0 to 3
            b.status(); //DONE
        } 
        else if (cmd == "residences") { // prints the residences the current builder has currently completed
            b.getRez(); //DONE
        } 
        else if (cmd == "build-road") { // attempts to build the road at <road#>
            int road;
            cin >> road;
            if (b.canBuildRoad(road)){
            b.buildRoad(road);
            }
            //DONE
        } 
        else if (cmd == "build-res") { // attempts to builds a basement at <housing#>
            int housing;
            cin >> housing;
            if (b.canBuild(housing)){
                b.build(housing);
            }
            //DONE
        } 
        else if (cmd == "improve") { // attempts to improve the residence at <housing#>
            int housing;
            cin >> housing;
            if (b.canImprove(housing)){
                b.improve(housing);
            }
            //DONE
        } 
        else if (cmd == "trade") { // attempts to trade with builder <colour> giving one resource of type <give> and receiving one resource of type <take>
            string colour;
            string give;
            string take;
            cin >> colour;
            cin >> give;
            cin >> take;
            b.trade(colour, give, take);
            //DONE
        } 
        else if (cmd == "next") { // passes control onto the next builder in the game. This ends the ”During the Turn” phase.
            b.next(); 
            break;
            //DONE
        } 
        else if (cmd == "save") { // saves the current game state to <file>
            string file;
            cin >> file;
            b.save(file);
        } 
        else if (cmd == "help") { // prints out the list of commands
            b.helpCommandsPrint();
            //DONE
        } 
        else {
            cout << "Invalid command." << endl;
        }
        cout << "> ";
    } 
}

void beginning_turn(Board b){
    string cmd;
    cout << "> ";
    while (cin >> cmd) {
        if (cmd == "load") { // sets the dice of the current builder to be loaded dice
            b.dice_modes[b.curTurn] = 0;
        } 
        else if (cmd == "fair") { // sets the dice of the current builder to be fair dice
            b.dice_modes[b.curTurn] = 1;
        } 
        else if (cmd == "roll") { // rolls the current builder’s dice. This ends the ”Beginning of the turn” phase and moves the builder to ”During the turn”.
            b.rollDice();
            break;
        }
        else {
            cout << "Invalid command." << endl;
        }
        cout << "> ";
    } 
}

int main(int argc, char** argv) {

    bool quit_game = false;
    while(!(quit_game))  {
    Board b;
    b.init();
    bool load = false;
    bool board = false;
    bool random_board = false;
    string file_name = "";
    string seed = "";
    for (int i = 1; i < argc; i++) {
        string option = argv[i];
	    if (option == "-load") {
            i++;
		    file_name = argv[i];
            load = true;
	    } else if (option == "-board") {
            i++;
            file_name = argv[i];
            board = true;
	    } else if (option == "-seed") {
            i++;
		    seed = argv[i];
	    } 
        else if (option == "-random-board") {
            random_board = true;
	    } 
    }

    b.seed(seed);
    if (load) {
        b.loadFile(file_name);
        b.printBoard();
        b.status();
		cout << "Builder " << b.colours[b.curTurn] << "'s turn." << endl;
    }
    else if (board) {
        b.loadBoard(file_name);
        b.printBoard();
		b.first8();

    }
    else if (random_board){
        b.randomBoard();
	    b.printBoard();
        b.first8();
    }
    else {
        b.printBoard();
        b.first8();
    }

    bool game_over = false;
    while(!(game_over)) {
        beginning_turn(b);
        during_turn(b);
        if (b.checkWin()) {
            while(1){
                string input;
                cout << "Would you like to play again?" << endl;
                cin >> input;
                if (input == "yes") {
                    quit_game = false;
                    break;
                }
                else if (input == "no") {
                    quit_game = true;
                    break;
                }
                else {
                    cout << "Invalid command." << endl;
                }
            }
        }
    }
    }
}