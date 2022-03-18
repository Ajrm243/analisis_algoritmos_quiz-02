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

// este struct me sirve para alinear todos los elementos en un solo arreglo pero manteniendo de cuál dirección provienen
typedef struct costDirection {
    int cost;
    int dirSize;
    string dir;
} costDirecionPointer;
costDirection costList[1000];

int cD_comparator(const void *v1, const void *v2) {
    const costDirection *p1 = (costDirection *)v1;
    const costDirection *p2 = (costDirection *)v2;
    /*
    cout << "p1: " + to_string(p1->cost) + " " + p1->dir + " " + to_string(p1->dirSize)
    << endl
    << "p2: " + to_string(p2->cost) + " " + p2->dir + " " + to_string(p2->dirSize)
    << endl
    ;
    */
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
    // para minimizar los cortes se tienen que priorizar primero aquellos que tengan mayor coste
    // entonces si hay un max de costo en x o y, se hace ese primero, luego se hace el siguiente corte más caro,
    // en 2 cortes de igual costo se prioriza el corte que esté asociado al array más largo de los 2 de entrada
    // de esta manera se hace la minimización de costos
    // mantienen el tamaño de los arreglos x e y
    int x_size = M - 1, y_size = N - 1;
    // cuentan cuantas sub-divisiones existen
    int Cx = 1, Cy = 1;
    // tiene track del tamaño de la lista a manejar
    int sizeCounter = 0;
    // track del costo
    int cost = 0;
    // llena el arreglo
    for (int i = 0; i < x_size; i++) {
        costList[i] = {x[i], x_size, "x"};
        sizeCounter++;
    }
    // llena el arreglo
    for (int i = sizeCounter; i < y_size + x_size; i++) {
        costList[i] = {y[i-x_size], y_size, "y"};
        sizeCounter++;
    }
    // sortea para hacer los calculos usando la función de comparación definida arriba
    qsort(&costList[0], sizeCounter, sizeof(costDirection), cD_comparator);

    // itera por la selección de los elementos sorteados
    for (int i = 0; i < sizeCounter; i++) {

        if (costList[i].dir.compare("y") == 0) {
            // es un corte en Y
            // aumente por el costo multiplicado por las sub-divisiones en X
            cost += (costList[i].cost * Cx);
            Cy++;
        }
        else {
            // es un corte en X
            // aumente por el costo multiplicado por las sub-divisiones en Y
            cost += (costList[i].cost * Cy);
            Cx++;
        }

    }

    return cost;
}

int costo2(int N, int M, int x[], int y[]) {

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
    // loop invariant => pocket[10] siempre tiene 10 elementos pero cuando está vacío le dice al algoritmo que ya terminó de ingresar elementos
}

int main () {
    
    pruebaX2;
    pruebaY2;
    int resCosto = costo(4,5,X,Y);  // expected: 79
    cout << "result: " + to_string(resCosto) << endl;

    return 0;
}