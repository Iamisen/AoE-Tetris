/*
    library for the logic of our tetris game.
    made by MRWRM, Columbia University.
    last updated on 8/4/2023 at 3:50am
*/
#include <Arduino.h>
#include <Tetris.h>
#include <time.h>
#include <string>
#include <iostream>
#include <map>

struct Sprite {
    int *shape;
    int x;
    int y;
}

struct Table {
    int table[5][5];
}

Tetris::Tetris() {
    //shapes

    Table square {
        {1, 1, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        };

    Table l{
        {1, 0, 0, 0, 0},
        {1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        };

    Table even_l{
        {1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
    };

    Table line{
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1},
        };

    map<std::string,Table> shapes;
    shapes.insert(std::pair<string,Triple>("square",square));
    shapes.insert(std::pair<string,Triple>("l",l));
    shapes.insert(std::pair<string,Triple>("even_l",even_l));
    shapes.insert(std::pair<string,Triple>("line",line));
    
    string shapes_key[4] = {
        "square",
        "l",
        "even_l",
        "line",
    };

    bool block_fallong = false;
    struct Sprite block;

/*
    map<std::string,signed int> actions;
    actions.insert(std::pair<string, signed int>("down", 1));
    actions.insert(std::pair<string, signed int>("right", 1));
    actions.insert(std::pair<string, signed int>("up", -1));
    actions.insert(std::pair<string, signed int>("left", -1));
*/

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
        {0,0,0,0,0,0,0,0},
    };
}

int Tetris::ClearMatrice(int[5][5] block){
    int row = 5; int column = 5;
    bool iszero = true;
    for (i=0, i<5, i++){
        for (j=0, j<5, j++){
            if (block[i][j] == 1){
                iszero = false;
            }
        }
        if (iszero == true){
            row--;
        }

        for (j=0, j<5, j++){
            if (block[j][i] == 1){
                iszero = false;
            }
        }
        if (iszero == true){
            column--;
        }
        iszero = true; row = 5; column = 5;
    }
    
    if (row == 0 && column == 0){
        return matrix[0][0];
    }
    else if (row == 0){
        return matrix[0][0:column];
    }
    else if (column == 0){
        return matrix[0:row][0];
    }
    else {
        return block[0:row][0:column];
    }
}

int Tetris::AddMatrices(Sprite block, int base_matrix[16][8]){
    //matrice 1 is going to be our base frame (without the added piece)
    //matrice 2 is the added piece

    int matrix = block.shape;
    int shape[2] = { sizeof(matrix), sizeof(matrix[0]) };//first element is nnumber of rows, second is number of columns

    int result[16][8];

    for (int row=0; row<=16; row++){
        for (int column=0; column<=8; column++){
            if ((x <= row <= shape[0] + x) && (y <= column <= shape[1] + y)){
                result[row][column] = base_matrix[row][column] + matrix[row - x][column - y];
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

int Tetris::TransposeMatrix(int matrix[][]) {
    int shape[2] = { sizeof(matrix), sizeof(matrix[0]) };
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
    int index = rand() % sizeof(shapes);
    block.shape = shapes[shapes_key[index]];
    
    int shape_half_length = sizeof(initialized_shape[0]) / 2; //we have taken lenghth as an int on purpose in order to have an integer o work with
    block.x = 4 - shape_half_length;
    block.y = 0;

    return AddMatrices(block, base_matrix); //shape is initialized at top middle
}

void Tetris::Action(Sprite block, string action){
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