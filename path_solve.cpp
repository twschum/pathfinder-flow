/* * * * * * * * * * * * * * * * * * * * * * * * *
 * File Name : path_solve.cpp
 * Author   : Tim Schumacher - twschum
 * Creation Date : 06-05-2016
 * Last Modified : Sat 07 May 2016 07:36:03 PM EDT
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <inttypes.h>

#include "Board.h"

using namespace std;

//void read_board_file(char* filename, vector<uint32_t>& values) { }

void read_board(vector<uint32_t>& board) {

    // get the board size from stdin
    uint32_t tiles;
    cin >> tiles;

    // get the rest of the board
    uint32_t tile;
    for (uint32_t i = 0; i < tiles; i++) {
        cin >> tile;
        board.push_back(tile);
    }
}

int main(/*int argc, char** argv*/) {

    // usage: ./pathfind filename
    // where filename has whitespace seperated, hex
    // encoded numnbers representing the board
    // read from standard in if not provided
    //
    // do with streams instead

    Board board_one(cin);
    board_one.print();
}
