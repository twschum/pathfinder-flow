/* * * * * * * * * * * * * * * * * * * * * * * * *
 * File Name : path_solve.cpp
 * Author   : Tim Schumacher - twschum
 * Creation Date : 06-05-2016
 * Last Modified : Fri 06 May 2016 10:18:56 PM EDT
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include <istream>
#include <inttypes.h>
#include <vector>

using namespace std;

class Node {
public:
    Node(uint32_t);
    ~Node();

    const uint8_t type;
    const uint8_t color;
    const uint8_t x;
    const uint8_t y;
private:
};

typedef vector< vector<Node> > board_grid_t;

class Board {
public:
    Board(istream);
    ~Board();

    void print() const;

private:
    board_grid_t board;
};
