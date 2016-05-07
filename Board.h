/* * * * * * * * * * * * * * * * * * * * * * * * *
 * File Name : path_solve.cpp
 * Author   : Tim Schumacher - twschum
 * Creation Date : 06-05-2016
 * Last Modified : Sat 07 May 2016 07:36:40 PM EDT
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include <inttypes.h>
#include <vector>
#include <iostream>

#include <cassert>

using namespace std;

class Node {
public:
    Node(uint32_t);
    ~Node();

    const uint8_t x;
    const uint8_t y;

    // Each Node can be encoded in hex
    // 0x tt cc xx yy ( type | color | x | y )-
    uint32_t get_hex_encoding() const;

    // add a possible color to the node
    // must be a blank node
    void add_color(uint8_t color);

    // character representation of the node
    char get_mark() const;

private:
    uint8_t type;
    vector<uint8_t> colors;
};

typedef vector< vector<Node> > board_grid_t;

class Board {
public:
    /*
     * Board initializes from given input stream
     * First is board size N (NxN), followed by the entries
     */
    Board(istream&);
    ~Board();

    void print() const;

private:
    board_grid_t board;
    uint8_t len;
};
