#!/usr/bin/env python
"""
Given a board via the specified JSON-schema, print it to the console
"""

import json
import sys

''' Hex encoding of node data - 2 bytes each
* tt blank, sink, pipe - 1 byte
* cc 32 colors - 1 byte white is 0/blank, colors after that
* x and y, 1 byte each
0x ttccxxyy ( type | color | x | y )-
0 = blank
1 = sink
2 = pipe
colors: 1 - (num), 0 for blanks
'''

blank_board = [
            0x00000000, 0x00000100, 0x00000200, 0x00000300, 0x00000400,
            0x00000001, 0x00000101, 0x00000201, 0x00000301, 0x00000401,
            0x00000002, 0x00000102, 0x00000202, 0x00000302, 0x00000402,
            0x00000003, 0x00000103, 0x00000203, 0x00000303, 0x00000403,
            0x00000004, 0x00000104, 0x00000204, 0x00000304, 0x00000404
            ]

board_one = [
            0x00000000, 0x00000100, 0x01010200, 0x00000300, 0x01020400,
            0x00000001, 0x01020101, 0x00000201, 0x00000301, 0x01040401,
            0x00000002, 0x01030102, 0x00000202, 0x01030302, 0x00000402,
            0x00000003, 0x01040103, 0x00000203, 0x00000303, 0x00000403,
            0x00000004, 0x00000104, 0x00000204, 0x00000304, 0x01010404
            ]

board_one_partial = [ 0x00000000, 0x00000100, 0x01010200, 0x02020300, 0x01020400,
            0x00000001, 0x01020101, 0x02020201, 0x02020301, 0x01040401,
            0x00000002, 0x01030102, 0x02030202, 0x01030302, 0x00000402,
            0x00000003, 0x01040103, 0x00000203, 0x00000303, 0x00000403,
            0x00000004, 0x00000104, 0x00000204, 0x00000304, 0x01010404
            ]

board_one_solved = [
            0x02010000, 0x02010100, 0x01010200, 0x02020300, 0x01020400,
            0x02010001, 0x01020101, 0x02020201, 0x02020301, 0x01040401,
            0x02010002, 0x01030102, 0x02030202, 0x01030302, 0x02040402,
            0x02010003, 0x01040103, 0x02040203, 0x02040303, 0x02040403,
            0x02010004, 0x02010104, 0x02010204, 0x02010304, 0x01010404
            ]

class cterm:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'

class Node(object):
    """
    Node in the board is the abstract base class for Sink and Pipe
    """
    _shape_ids = ['blank', 'sink', 'pipe']
    _shapes = {
            'blank': ' ',
            'sink': 'o',
            'pipe': '+',
            'pipe_virt': '|',
            'pipe_horiz': '-',
            }

    _color_ids = ['white', 'blue', 'yellow', 'red', 'green', 'purple']
    _colors = {
            'white': '\033[0m',
            'blue': '\033[94m',
            'yellow': '\033[93m',
            'red': '\033[91m',
            'green': '\033[92m',
            'pruple': '\033[95m',
            }

    def __init__(self, hex_value):
        self.hex_val = hex_value
        self.shape_id = hex_value >> 24
        self.color_id = (hex_value >> 16) & 0x000000ff
        self.x = (hex_value >> 8) & 0x000000ff
        self.y = hex_value & 0x000000ff

        self.shape = self._shape_ids[self.shape_id]
        self.color = self._color_ids[self.color_id]

    def __str__(self):
        return self._colors[self.color] + self._shapes[self.shape] + self._colors['white']


class Board(object):
    """
    A Board has a set size, and an array of Nodes, which are either pipe or sink
    """

    def __init__(self, size, node_list):
        self.board_size = size
        self.nodes = [Node(n) for n in node_list]

    def __str__(self):
        _str = '{} by {} board:\n'.format(self.board_size, self.board_size)
        for i in range(self.board_size):
            for j in range(self.board_size):
                _str += ' ' + str(self.nodes[(i*self.board_size) + j])
            _str += '\n'
        return _str

def main():

    one = Board(5, board_one)
    one_part = Board(5, board_one_partial)
    one_solved = Board(5, board_one_solved)

    #print one
    #print one_part
    #print one_solved

    print '5'
    for node in board_one:
        print node

if __name__ == "__main__":
    main()

