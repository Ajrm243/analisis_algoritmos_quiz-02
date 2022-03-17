#include <iostream>
#include <bits/stdc++.h>
#include <list>
#include <string>
#include <map>
#include <math.h>

#define MAX_COST 1000;
#define pruebaX1 int X[] = {5,2,6,3,8,7}    // M = 7
#define pruebaY1 int Y[] = {1,3,2,1}        // N = 5
#define pruebaX2 int X[] = {10,2,7,5}    // M = 5
#define pruebaY2 int Y[] = {2,9,2}        // N = 4

using namespace std;

typedef struct costDirection {
    int cost;
    int dirSize;
    string dir;
} costDirecionPointer;
costDirection costList[1000];

int cD_comparator(const void *v1, const void *v2) {
    const costDirection *p1 = (costDirection *)v1;
    const costDirection *p2 = (costDirection *)v2;
    cout << "p1: " + to_string(p1->cost) + " " + p1->dir + " " + to_string(p1->dirSize)
    << endl
    << "p2: " + to_string(p2->cost) + " " + p2->dir + " " + to_string(p2->dirSize)
    << endl
    ;
    if (p1->cost < p2->cost) {
        return +1;
    }
    else if (p1->cost > p2->cost) {
        return -1;
    }
    // ya son iguales, comparar tamaño de la direccion de costos
    else if (p1->dirSize < p2->dirSize){
        return +1;
    }
    else if (p1->dirSize > p2->dirSize){
        return -1;
    }
    else {
        return 0;
    }
}

int costo(int N, int M, int x[], int y[]) {
    // la idea es que siempre la cantidad de cortes será (NxM - 1)
    // idea matemática de https://math.stackexchange.com/questions/1896374/minimum-number-of-ways-of-dividing-an-m-times-n-chocolate-bar-into-square-piec
    int x_size = M - 1, y_size = N - 1;
    int Cx = 1, Cy = 1;
    int sizeCounter = 0;
    for (int i = 0; i < x_size; i++) {
        costList[i] = {x[i], x_size, "x"};
        sizeCounter++;
    }
    for (int i = sizeCounter; i < y_size + x_size; i++) {
        costList[i] = {y[i-x_size], y_size, "y"};
    }
    for (costDirection c : costList) {
        if (c.cost != 0) {
            cout << c.cost << c.dir << endl;
        }
    }
    cout << "after" << endl;
    qsort(&costList[0], sizeCounter, sizeof(costDirection), cD_comparator );
    for (costDirection c : costList) {
        if (c.cost != 0) {
            cout << c.cost << c.dir << endl;
        }
    }
}

void radixSort(int *arr, int n, int max) {
    int i, j, m, p = 1, index, temp, count = 0;
    // declaraciones +7 tiempos
    // p=1 y count=0 asignaciones +2 tiempos
    list<int> pocket[10];      //radix of decimal number is 10 | declaracion +1 tiempo
    // declaracion con asignacion +2 tiempos fuera del loop
    for(i = 0; i< max; i++) {   // comparacion y asignacion con operacion +3 tiempos
        m = pow(10, i+1);   // 1 llamada a funcion, 2 parametros, 1 operacion, 1 retorno y 1 asignacion +6 tiempos
        p = pow(10, i);     // 1 llamada, 2 parametros, 1 retorno y 1 asignacion +5 tiempos
        // declaracion con asignacion +2 tiempos fuera del loop
        for(j = 0; j<n; j++) {  // comparacion y asignacion con operacion +3 tiempos
            temp = arr[j] % m;  // 1 indexacion, 1 operacion y 1 asignacion +3 tiempos
            index = temp/p;      //find index for pocket array | 1 operacion y 1 asignacion +2 tiempos
            pocket[index].push_back(arr[j]);    // 2 indexaciones, 1 llamada, 1 parametro +4 tiempos
        }
        // ^ 12n tiempos
        count = 0; // 1 asignacion
        // declaracion con asignacion +2 tiempos fuera del loop
        for(j = 0; j<10; j++) {     // comparacion y asignacion con operacion +3 tiempos
            //delete from linked lists and store to array
            while(!pocket[j].empty()) {     // 1 comparacion por cada que el elemento de pocket no esté vacío
            // 1 comparacion, 1 indexacion, 1 llamada +3 tiempos
                arr[count] = *(pocket[j].begin());  // 2 indexaciones, 1 asignacion, 1 llamada y 1 parametro +5 tiempos
                pocket[j].erase(pocket[j].begin()); // 2 indexaciones, 2 llamadas, 1 parametro +5 tiempos
                count++;    // asignacion y operacion +2 tiempos
            }
        }
        // ^ 15 * 10 = 150 tiempos
    } // max(3+6+5+2 + 12n +150)
    // max(12n + 166) tiempos
    // f(n) = max(12n + 166)
    // O(n) = O(nm)
    // loop invariant
}

int main () {
    
    pruebaX2;
    pruebaY2;
    int resCosto = costo(4,5,X,Y);  // expected: 79

    return 0;
}