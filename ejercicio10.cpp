#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "funciones/enteros.cpp"

using namespace std;

struct Pos{
    int col;
    int row;
};

Pos getPosition(int position, int columns){
    int col = position / columns;
    int row = position % columns;
    return Pos{col, row};
}

bool areNoneRepeating(int* array, int length){
    for (int i=1; i<length; i++){
        if (array[i] > 1) return false;
    }
    return true;
}
bool areNoneRepeatingOrMissing(int* array, int length){
    for (int i=1; i<length; i++){
        if (array[i] != 1) return false;
    }
    return true;
}

bool checkArea(int** baseTable, int** answerTable, int rows, int columns, int numberToCheck, Pos position){
    int chunkWidth = columns / 3;
    int chunkHeight = rows / 3;
    int chunkCol = position.col / 3;
    int chunkRow = position.row / 3;

    cout << "w: " << chunkWidth << " h: " << chunkHeight <<endl;
    int* numbers = new int[chunkWidth*chunkHeight + 1];
    for (int col=(chunkCol*chunkWidth); col<(chunkCol+1)*chunkWidth; col++){
        for (int row=(chunkRow*chunkHeight); row<(chunkRow+1)*chunkHeight; row++){
            int val = (position.col == col && position.row == row) ? numberToCheck : baseTable[row][col];
            if (val == 0) val = answerTable[row][col];
            if (val == 0) return true;
            numbers[val] ++;
        }
    }
    cout << "checking " << numberToCheck << " ";
    for (int i=0;i<=max(rows, columns);i++){
         cout << i << ":" << numbers[i] << " ";
    }
    cout << endl;
    return areNoneRepeatingOrMissing(numbers, chunkWidth*chunkHeight + 1);
}
bool checkHorizontal(int** baseTable, int** answerTable, int rows, int columns, int numberToCheck, Pos position){
    int row = position.row;
    int* numbers = new int[max(rows, columns)+1];
    for (int col=0; col<columns; col++){
        int val = position.col == col ? numberToCheck : baseTable[row][col];
        if (val == 0) val = answerTable[row][col];
        if (val == 0) return true;
        numbers[val] ++;
    }
    return areNoneRepeating(numbers, max(rows, columns) + 1);
}
bool checkVertical(int** baseTable, int** answerTable, int rows, int columns, int numberToCheck, Pos position){
    int col = position.col;
    int* numbers = new int[max(rows, columns)+1];
    for (int row=0; row<rows; row++){
        int val = position.row == row ? numberToCheck : baseTable[row][col];
        if (val == 0) val = answerTable[row][col];
        if (val == 0) return true;
        numbers[val]++;
    }
    return areNoneRepeating(numbers, max(rows, columns) + 1);
}

bool answerValid (int** baseTable, int** answerTable, int rows, int columns, int numberToCheck, Pos position){
    return checkVertical(baseTable, answerTable, rows, columns, numberToCheck, position)
    && checkHorizontal(baseTable, answerTable, rows, columns, numberToCheck, position)
    && checkArea(baseTable, answerTable, rows, columns, numberToCheck, position);
}

bool hasData(int** baseTable, Pos position){
    return baseTable[position.row][position.col] != 0;
}

bool validPosition(int pos, int rows, int columns){
    return pos < rows*columns;
}

void storeSolutionInBase(int** baseTable, int** answerTable, int rows, int columns){
    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            int value = baseTable[i][j];
            if (value == 0) {
                baseTable[i][j] = answerTable[i][j];
            }
        }
    }
}

void backtracking(int** baseTable, int** answerTable, int rows, int columns, int currentPosition) {
    Pos pos = getPosition(currentPosition, columns);
	while (validPosition(currentPosition, rows, columns) && hasData(baseTable, pos)){
        currentPosition++;
        pos = getPosition(currentPosition, columns);
    }
    if(!validPosition(currentPosition, rows, columns)) { 
        storeSolutionInBase(baseTable, answerTable, rows, columns);
		return;
	} else {
        cout << pos.col << "|" << pos.row << endl;
        for(int i=1; i<=max(columns, rows); i++) {
			if(answerValid(baseTable, answerTable, rows, columns, i, pos)) {
				answerTable[pos.row][pos.col] = i;
				backtracking(baseTable, answerTable, rows, columns, currentPosition+1); 
				answerTable[pos.row][pos.col] = 0;
			}
        }
		
	}
}

int main()
{
    int rows, columns;
    cin >> rows >> columns;

    int** table = new int*[rows];
    int** answer = new int*[rows];
    for (int i=0; i<rows; i++){
        table[i] = new int[columns];
        answer[i] = new int[columns]();
        for (int j=0; j<columns; j++){
            int n;
            cin >> n;
            table[i][j] = n;
        }
    }

    backtracking(table, answer, rows, columns, 0);

    for (int i=0; i<rows; i++){
        for (int j=0; j<columns; j++){
            cout << table[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

//Un amigo experto en sudoku quiere hacer una competencia con usted en sudoku competitivo. 
//Este sudoku competitivo tiene una variación respecto al sudoku común. 
//Esta variación es que tiene tableros de distintas dimenciones, como por ejemplo 9x9, 12x9, 9x12, etc. 
//Dado que usted no es muy bueno en sudoku, pero no quiere perder contra su amigo decide hacer trampa. 
//Para ello, hara un programa que dado un tablero de sudoku, le imprime la solución del mismo.

//Las reglas del sudoku son las siguientes:

//En una fila no puede haber dos números repetidos.
//En una columna no puede haber dos números repetidos.
//Si dividimos el tablero en 9 bloques (de filas totales/3 filas * columnas totales/3 columnas), 
//en cada bloque no puede haber números repetidos. Y los números del 1 al k, sin saltearse ningún número.