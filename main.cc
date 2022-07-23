#include <iostream>
#include <string>
#include "board.h"
using namespace std;

int main() {
    Board b;
    string cmd;
    cout << ">" << endl;
    while (cin >> cmd) {
        if (cmd == "board") { // prints the current board
            b.printBoard(); //DONE
        } 
        else if (cmd == "status") { // prints the current status of all builders in order from builder 0 to 3
            b.status(); //DONE
        } 
        else if (cmd == "residences") { // prints the residences the current builder has currently completed
            //NOT DONE
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
            //DONE
        } 
        else if (cmd == "save <file>") { // saves the current game state to <file>
            //NOT DONE
        } 
        else if (cmd == "help") { // prints out the list of commands
            b.helpCommandsPrint();
            //DONE
        } 
        //else if (cmd == "quit") {
        //    break;
        //} 
        else {
            cout << "Invalid command." << endl;
        }
        cout << ">" << endl;
    }    
}