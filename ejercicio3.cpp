#include <cassert>
#include <string>
#include <iostream>
#include <limits>

using namespace std;

bool isALessThanB(int* array, int a, int b){
    return array[a] < array[b];
}

void swap(int* array, int indexFirst, int indexSecond){
    int aux = array[indexFirst];
    array[indexFirst] = array[indexSecond];
    array[indexSecond] = aux;
}

int parent(int index){
    return index/2;
}
int childLeft(int index){
    return index*2;
}
int childRight(int index){
    return index*2 + 1;
}

//Sink
void siftDown(int* array, int index, int count){
    int childLeftIndex = childLeft(index);
    int childRightIndex = childRight(index);
    int minIndex = index;

    if (childLeftIndex <= count && isALessThanB(array, minIndex, childLeftIndex))
        minIndex = childLeftIndex;
    if (childRightIndex <= count && isALessThanB(array, minIndex, childRightIndex))
        minIndex = childRightIndex;

    if (minIndex != index)
    {
        swap(array, index, minIndex);
        siftDown(array, minIndex, count);
    }
}

int main()
{
    int count;
    cin >> count;

    //READ
    int* array = new int[count+1];
    int num;
    for (int i = 1; i <= count; i++) 
    {
        cin >> num;
        array[i] = num;
    }

    //HEAPIFY
    for (int start = count; start >= 1; start--)
    {
        //Hundo el primero considerando que el heap llega solo hasta heapEnd
        siftDown(array, start, count);
    };

    //SORT
    for (int end = count; end >= 1; end--) 
    {
        swap(array, 1, end);
        siftDown(array, 1, end-1);
    }

    //PRINT
    for (int i = 1; i <= count; i++) 
    {
        cout << array[i] << endl;
    }

    return 0;
}

//Dado un conjunto de números enteros, se requiere implementar un algoritmo de ordenamiento utilizando la técnica de heapificación (heapify). 
//El objetivo es ordenar los números de menor a mayor eficientemente.
//- La primera línea contiene un número entero positivo N (2 ≤ N ≤ 10^5), el largo del conjunto de números.
//- Las siguientes N líneas contienen los números del conjunto.
//Imprimir N líneas con los números ordenados en orden creciente.
//Utilizar obligatoriamente la técnica de heapify.
//Complejidad esperada: O(N log N)