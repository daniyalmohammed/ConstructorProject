#include "TextDisplay.h"
#include <iostream>
#include <vector>
#include "subject.h"
using namespace std;


TextDisplay::TextDisplay(int n):gridSize{n} {
    for (int j = 0; j < n; j++) {
        vector<char> row;
        for (int i = 0; i < n; i++) {
            row.push_back('-');
        }
        theDisplay.push_back(row);
    }  
}

// set up theGrid beased on the colour of the cell
void TextDisplay::notify(Subject<Info, State> &whoNotified) {
    int r = whoNotified.getInfo().row;
    int c = whoNotified.getInfo().col;
    Colour colour = whoNotified.getInfo().colour;
    if (colour == Colour::Black) {
        theDisplay[r][c] = 'B';
    } else if (colour == Colour::White) {
        theDisplay[r][c] = 'W';
    } else {
        theDisplay[r][c] = '-';
    }
}

// print out the textDisplay
std::ostream & operator<<(std::ostream &out, const TextDisplay &td) {
    for (int i = 0; i < td.gridSize; i++) {
        for (int j = 0; j < td.gridSize; j++) {
            out << td.theDisplay[i][j];     
        }
        out << endl;
    }
    return out;
}
