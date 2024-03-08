/*
Faça um programa para receber nove números inteiros positivos, armazená-los em um vetor, calcular e exibir no dispositivo de saída padrão aqueles números que são primos e suas respectivas posições no vetor. Se nenhum número primo for fornecido, nenhuma mensagem precisará ser exibida.

Entradas:

Nove números inteiros positivos a serem armazenados em um vetor.
Saídas:

Sequência de números primos e suas respectivas posições (índices no vetor). Obs.: Aqueles números que forem primos e suas respectivas posições deverão ser exibidos aos pares.

*/

bool conferePrimo(int num) {
    int counter = 1;

    while(counter < num) {
        if(num % counter == 0 && counter != 1) {
            return false;
        }

        counter++;
    }

    return true;
}

#include <iostream>

using namespace std;

int main() {
    int vetor[9];

    for(int i = 0; i < 9; i++) {
        cin >> vetor[i];
    }

    for (int i = 0; i < 9; i++)
    {
        if(conferePrimo(vetor[i])) {
            cout << vetor[i] << " " << i << endl;
        }
    }
    


    return 0;
}