/*
    library for the logic of our tetris game.
    made by MRWRM, Columbia University.
    last updated on 12/4/2023 at 8:00pm
*/

#ifndef Tetris_h
#define Tetris_h
#include "Arduino.h"

struct Sprite {
    int *shape;
    int x;
    int y;
};

struct Table {
    int table_shape[5][5];
};

const int shape[2] = {5,5};

int base_matrix [16][8] = {
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0}
    };

Table my_square = {{
    {1, 1, 0, 0, 0},
    {1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    }};

Table my_l {{
    {1, 0, 0, 0, 0},
    {1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
    }};

Table my_even_l {{
    {1, 0, 0, 0, 0},
    {1, 0, 0, 0, 0},
    {1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0}
}};

Table my_line {{
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0},
    {1, 1, 1, 1, 1}
    }};

Table shapes[4] = {my_line, my_square, my_even_l, my_line};

class Tetris {
public:
    Tetris();
    int AddMatrices(Sprite block, int base_matrix[16][8]);
    int RotateShape(int base_matrix[16][8], Sprite block);
    int TransposeMatrix(int matrix[5][5]);
    int SpawnShape(int base_matrix[16][8]);
    int ClearMatrice(int block[5][5]);
    void Action(Sprite block, const char *action);
private:
    SliceMatrix(int row_start, int row_end, int column_start, int column_end, int block[5][5]);
};

#endif