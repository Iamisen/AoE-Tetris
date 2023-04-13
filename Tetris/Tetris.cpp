/*
    library for the logic of our tetris game.
    made by MRWRM, Columbia University.
    last updated on 12/4/2023 at 8:00pm
*/

#include "Arduino.h"
#include <Tetris.h>
#include <time.h>

Tetris::Tetris() {
    bool block_falling = false;
    struct Sprite block;

/*
    map<std::string,signed int> actions;
    actions.insert(std::pair<string, signed int>("down", 1));
    actions.insert(std::pair<string, signed int>("right", 1));
    actions.insert(std::pair<string, signed int>("up", -1));
    actions.insert(std::pair<string, signed int>("left", -1));
*/
}

int Tetris::SliceMatrix(int row_start, int row_end, int column_start, int column_end, int block[5][5]){
    int i = 0; int j = 0;
    int x = 0; int y = 0;
    int result[row_end - row_start][column_end - column_start];

    for (i = row_start; i <= row_end; i++){
        for (j = column_start; j <= column_end; j++){
            result[x][y] = block[i][j];
            y++;
        }
        y = 0;
        x++;
    }

    return result;
}

int Tetris::ClearMatrice(int block[5][5]){
    int row = 5; int column = 5;
    bool iszero = true;
    int i = 0; int j = 0;
    for (i=0; i<5; i++){
        for (j=0; j<5; j++){
            if (block[i][j] == 1){
                iszero = false;
            }
        }
        if (iszero == true){
            row--;
        }

        for (j=0; j<5; j++){
            if (block[j][i] == 1){
                iszero = false;
            }
        }
        if (iszero == true){
            column--;
        }
        iszero = true; row = 5; column = 5;
    }
    
    return SliceMatrix(0,row,0,column,block);

    /*if (row == 0 && column == 0){
        return 0;
    }
    else if (row == 0){
        return SliceMatrix(0,5,0,column,block);
    }
    else if (column == 0){
        return SliceMatrix(0,row,0,5,block)
    }
    else {
        return SliceMatrix(0,row,0,column,block) block[0:row][0:column];
    }*/
}

int Tetris::AddMatrices(Sprite block, int base_matrix[16][8]){
    //matrice 1 is going to be our base frame (without the added piece)
    //matrice 2 is the added piece

    int matrix = block.shape;
    int result[16][8];

    for (int row=0; row<=16; row++){
        for (int column=0; column<=8; column++){
            if ((block.x <= row <= shape[0] + block.x) && (block.y <= column <= shape[1] + block.y)){
                int add = matrix[row - block.x][column - block.y];
                result[row][column] = base_matrix[row][column] + add;
                if (result[row][column] > 1){
                    return base_matrix;
                }
            }
        }
    }

    return result;
}

int Tetris::RotateShape(int base_matrix[16][8], Sprite block) { // x and y will be the coordinates for the top left corner
    int matrix = ClearMatrice(block.shape);
    int shape[2] = { sizeof(matrix), sizeof(matrix[0]) };
    int dumped_matrix[shape[0]][shape[1]] = { matrix };
    
    //make the matrix a squre by adding zeros
    if (shape[0] != shape[1]){
        int difference = abs(shape[0] - shape[1]);
        if (shape[0] > shape[1]){
            for (int i = 0; i <= difference; i ++){
                for (int j = 0; j <= shape[0]; j++) {
                    matrix[j][shape[1] + i] = 0;
                }
            }
        }
        if (shape[0] < shape[1]){
            for (int i = 0; i <= difference; i++) {
                for (int j = 0; j <= shape[0]; j++) {
                    matrix[shape[0] + i][j] = 0;
                }
            }
        }
    }

    matrix = TransposeMatrix(matrix);
    block.shape = matrix;

    return AddMatrices(base_matrix, block);
}

int Tetris::TransposeMatrix(int matrix[5][5]) {
    int result[shape[0]][shape[1]];
    
    for (int i = 0; i <= shape[0]; i++) {
        for (int j = 0; j <= shape[1]; j++) {
            result[i][j] = matrix[j][i];
        }
    }

    return result;
}

int Tetris::SpawnShape(int base_matrix[16][8]) {

    srand(time(0)); //initialiwe seed at current time
    int index = rand() % (sizeof(shapes)/sizeof(shapes[0]));
    block.shape = shapes[index]; //size of shapes over size of a pointer
    
    int shape_half_length = sizeof(block.shape[0]) / 2; //we have taken lenghth as an int on purpose in order to have an integer o work with
    block.x = 4 - shape_half_length;
    block.y = 0;

    return AddMatrices(block, base_matrix); //shape is initialized at top middle
}

void Tetris::Action(Sprite block, const char *action){
    if (action == "UP"){
        block.y--;
    }
    if (action == "DOWN"){
        block.y++;
    }
    if (action == "RIGHT"){
        block.x++;
    }
    if (action == "LEFT"){
        block.x--;
    }
}

//use const instead of sizeof