/*
Faça um programa que abra um arquivo texto chamado "Meu_Arquivo.txt" e conte o número de caracteres não brancos nele. Escreva o resultado da contagem na saída padrão.
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ifstream file("Meu_Arquivo.txt");
    if (!file.is_open()) {
        cout << "Não foi possível abrir o arquivo." << endl;
        return 1;
    }

    char letra;
    int counter = 0;

    while (file.get(letra)) {
        if (!isspace(letra)) {
            counter++;
        }
    }

    file.close();

    cout << counter << endl;

    return 0;
}