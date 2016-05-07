/* * * * * * * * * * * * * * * * * * * * * * * * *
 * File Name : Board.cpp
 * Author   : Tim Schumacher - twschum
 * Creation Date : 07-05-2016
 * Last Modified : Sat 07 May 2016 07:36:42 PM EDT
 * * * * * * * * * * * * * * * * * * * * * * * * */

#include "Board.h"

#define BMASK 0x000000FF
#define GET_TYPE(HEX) ((HEX >> 24) & BMASK)
#define GET_COLOR(HEX) ((HEX >> 16) & BMASK)
#define GET_X(HEX) ((HEX >> 8) & BMASK)
#define GET_Y(HEX) (HEX & BMASK)

#define BLANK 0
#define SINK 1
#define PIPE 2

using namespace std;

// 0x tt cc xx yy ( type | color | x | y )-
Node::Node(uint32_t hexval)
    : x(GET_X(hexval)), y(GET_Y(hexval))
{
    type = GET_TYPE(hexval);
    if (GET_COLOR(hexval)) {
        colors.push_back(GET_COLOR(hexval));
    }
}

Node::~Node() {}

uint32_t Node::get_hex_encoding() const {

    uint32_t h;

    // x and y
    h = (uint32_t)y | ((uint32_t)x << 8);

    // type, color determined by number of colors
    // (blank if more than 1, color, type == 0)
    if (colors.size() > 1) {
        assert(type != SINK);
        h &= 0x0000FFFF;
    }
    else {
        assert(colors.size());
        h |= ((uint32_t)type << 24) | ((uint32_t)colors[0] << 16);
    }

    return h;
}

char Node::get_mark() const {
    if (type == BLANK) {
        return ' ';
    }
    else {
        assert(colors.size() == 1);
        return 'A' + colors[0] - 1; // colors start at 1
    }
}

void Node::add_color(uint8_t color) {
    assert(type != SINK);
    colors.push_back(color);
}

void Board::print() const {
    for (uint8_t i = 0; i < len; i++) {
        for (uint8_t j = 0; j < len; j++) {
            cout << " " << board[i][j].get_mark();
        cout << '\n';
        }
    }
}

Board::Board(istream& input) {

    input >> len;
    uint32_t hexval;
    input >> hexval;

    for (int j = 0; j < len; j++) {
        board.push_back( vector<Node>() );

        for (int i = 0; i < len; i++) {
            board.back().push_back( Node(0) );
        }
    }
}

Board::~Board() {}

