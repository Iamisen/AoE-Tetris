/*
    library for the logic of our tetris game.
    made by MRWRM, Columbia University.
    last updated on 4/5/2023 at 1:35pm
*/

#ifndef Tetris_h
#define Tetris_h

#include <Arduino.h>

class Tetris {
public:
    Tetris();
    int AddMatrices(int base_matrix[16][8], int matrix[16][8], int x, int y);
    int RotateShape(int base_matrix[16][8], int matrix[16][8], int x, int y);
    int TransposeMatrix(int matrix[16][8]);
    int SpawnShape(int base_matrix[16][8]);
private:
    int square;
    int l;
    int even_l;
    int line;
};

#endif