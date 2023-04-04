//shapes
byte SQUARE[2][2] = {
  {1,1},
  {1,1},
};

byte L[2][3] = {
  {1,0,0},
  {1,1,1},
}
byte EVEN_L[3][3] = {
  {1,0,0},
  {1,0,0},
  {1,1,1},
}
byte LINE[1][5] = {
  {1,1,1,1,1},
}


byte AddMatrices(byte &matrix1, byte &matrix2, int x, int y){
    //matrice 1 is going to be our base frame (without the added piece)
    //matrice 2 is the added piece

    int shape[2] = {sizeof(matrix[0]), sizeof(matrix)}

    for (row=0, row<=16, row++){
        for (column=0, column<=9, column++){
            if ((x <= row <= shape[0] + x) && (y <= column <= shape[1] + y)){
                matrix1[column][row] = matrix1[column][row] + matrix2[column - y][row - x]
                if (matrix1[column][row] > 1){
                    return 0;
                }
            }
        }
    }

    return matrix1;
}

byte RotateShape(byte &matrix, byte &base_matrix, int x, int y){
    int shape[2] = { sizeof(matrix[0]), sizeof(matrix) };
    byte dumped_matrix[shape[0]][shape[1]] = matrix;
    if (shape[0] != shape[1]){
        int difference = abs(shape[0] - shape[1]);
        if (shape[0] > shape[1]){
            for (i = 0, i <= difference, i ++){
                matrix[shape[1]+1][i] = 1;
            }
        }
        if (shape[0] < shape[1]){
            for (i = 0, i <= difference, i++){
                matrix[i][shape[0]+1] = 1;
            }
        }
    }
    if(){
        
    }
    return matrix;
}