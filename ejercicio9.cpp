#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "funciones/enteros.cpp"

using namespace std;

int*** mochilaDYN3D(int maxSize, int maxLines, int fileCount, int* fileSizes, int* fileLines, int* fileScores){
    int *** tab = new int**[fileCount + 1];
    for (int i=0; i<= fileCount; i++){
        tab[i] = new int*[maxSize + 1];
        for (int j=0; j<= maxSize; j++){
            tab[i][j] = new int[maxLines + 1]();
        }
    }

    for (int file = 1; file <= fileCount; file++){
        int size = fileSizes[file-1];
        int lines = fileLines[file-1];
        int score = fileScores[file-1];
        for (int currentSize = 1; currentSize <= maxSize; currentSize++){
            for (int currentLines = 0; currentLines <= maxLines; currentLines++){
                if (size > currentSize || lines > currentLines) 
                    tab[file][currentSize][currentLines] = tab[file-1][currentSize][currentLines];
                else {
                    int scoreWithout = tab[file-1][currentSize][currentLines];
                    int scoreWith = score + tab[file-1][currentSize-size][currentLines-lines];

                    tab[file][currentSize][currentLines] = max(scoreWith, scoreWithout);
                }
            }
        }
    }

    return tab;
}

int main()
{
    int N, S, L;
    cin >> N >> S >> L;

    int* fileSizes = new int[N+1]; 
    int* fileLines = new int[N+1]; 
    int* fileScores = new int[N+1];

    for (int i=0; i<N; i++){
        int t, l, p;
        cin >> t >> l >> p;
        fileSizes[i] = t;
        fileLines[i] = l;
        fileScores[i] = p;
    }

    int*** tab = mochilaDYN3D(S, L, N, fileSizes, fileLines, fileScores);

    cout << tab[N][S][L] << endl;

    return 0;
}

//El obligatorio de Estructuras de datos y algoritmos 3 es muy similar al de su materia antecesora, 
//con la pequeña diferencia de que no todos los ejercicios tienen el mismo puntaje.

//Un día antes de la entrega, el profesor le recuerda que la entrega de todos los archivos no debe 
//superar los S MB (megabytes) ni las L líneas de código entre todos ellos.

//Como usted olvidó este detalle y no tiene tiempo a refactorizar su código para que cumpla con las restricciones, 
//decide elegir aquellos ejercicios/archivos que le garanticen un mejor puntaje.

//De cada ejercicio/archivo, usted sabe su tamaño, cantidad de líneas de código y el puntaje.

//N
//S
//L
//t1 l1 p1
//t2 l2 p2
//...
//tN lN pN
//N: Es la cantidad de archivos.
//S: es el tamaño máximo que se puede subir para la entrega.
//L: es la cantidad máxima de lineas que puede tener la entrega.
//t l p: es t tamaño del archivo, l cantidad de lineas del archivo, y p puntos que vale ese ejercicio.