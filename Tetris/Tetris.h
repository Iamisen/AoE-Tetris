/*
    library for the logic of our tetris game.
    made by MRWRM, Columbia University.
    last updated on 4/5/2023 at 1:35pm
*/

#ifndef Tetris_h
#define Tetris_h

#include <Arduino.h>
#include <map>

class Tetris {
public:
    Tetris();
    int AddMatrices(Sprite block, int base_matrix[16][8]);
    int RotateShape(int base_matrix[16][8], Sprite block);
    int TransposeMatrix(int matrix[][]);
    int SpawnShape(int base_matrix[16][8]);
    int ClearMatrice(int block[5][5]);
    void Action(Sprite block, string action);
private:
    map shape;
    string shapes_keys;
    int square;
    int l;
    int even_l;
    int line;
};

#endif