/*
Na teoria de sistemas define-se como elemento minimax de uma matriz o menor elemento da linha onde se encontra o maior elemento da matriz. Escreva um programa que receba uma matriz quadrada de inteiros, 10x10, e retorne seu elemento minimax, seguido de sua posição. Em caso de números iguais considere o que aparece primeiro.

Entradas:

Um matriz de inteiros de tamanho 10x10.
Saídas:

O menor elemento da linha que tem o maior elemento da matriz.
A linha e a coluna onde está o elemento do item anterior.

*/

#include <iostream>

using namespace std;

int main() {
    int matrix[10][10];
    int linhaMaior = 0, maiorValor = 0, menorValor = 0, colunaMenor = 0;

    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            cin >> matrix[i][j];

            if(i == 0 && j == 0) {
                linhaMaior = i;
                maiorValor = matrix[i][j];
            }

            if(matrix[i][j] > maiorValor) {
                linhaMaior = i;
                maiorValor = matrix[i][j];
            }
        }
    }

    for(int i = 0; i < 10; i++) {
        if(i == 0) {
            menorValor = matrix[linhaMaior][i];
            colunaMenor = i;
        }

        if(matrix[linhaMaior][i] < menorValor) {
            menorValor = matrix[linhaMaior][i];
            colunaMenor = i;
        }
    }

    cout << menorValor << endl << linhaMaior << " " << colunaMenor;




    return 0;
}