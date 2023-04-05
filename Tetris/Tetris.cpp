/*
    library for the logic of our tetris game.
    made by MRWRM, Columbia University.
    last updated on 4/5/2023 at 1:35pm
*/
#include <Arduino.h>
#include <Tetris.h>
#include <time.h>


Tetris::Tetris() {
    //shapes

    int square[2][2] {
        {1, 1},
        { 1,1 },
        };

    int l[2][3]{
        {1, 0, 0},
        { 1,1,1 },
        };

    int even_l[3][3]{
        {1, 0, 0},
        { 1,0,0 },
        { 1,1,1 },
    };

    int line[1][5]{
        {1, 1, 1, 1, 1},
        };

    int shapes[][][] = {
        square,
        l,
        even_l,
        line,
    };

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
}

int Tetris::AddMatrices(int matrix[16][8], int base_matrix[16][8], int x, int y){
    //matrice 1 is going to be our base frame (without the added piece)
    //matrice 2 is the added piece

    int shape[2] = { sizeof(matrix[0]), sizeof(matrix) };//first element is nnumber of rows, second is number of columns

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

int Tetris::RotateShape(int matrix[16][8], int base_matrix[16][8], int x, int y) { // x and y will be the coordinates for the top left corner
    int shape[2] = { sizeof(matrix[0]), sizeof(matrix) };
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

    return AddMatrices(base_matrix, matrix, x, y);
}

int Tetris::TransposeMatrix(int matrix[16][8]) {
    int shape[2] = { sizeof(matrix[0]), sizeof(matrix) };
    int result[shape[0][shape[1]];
    
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
    initialized_shape = shapes[index];
    
    int shape_half_length = sizeof(initialized_shape[0]) / 2; //we have taken lenghth as an int on purpose in order to have an integer o work with
    int x = 4 - shape_half_length;

    return AddMatrices(initialized_shape, base_matrix, x, 0); //shape is initialized at top middle
}
