/*
Houve uma pane no sistema de contagem de tempo das Olimpíadas, e Comitê Olímpico Internacional (COI), pediu para você fazer um programa que, dado o tempo de cada atleta em uma prova da corrida de 100m rasos, calcule a diferença de tempo de todos os competidores para o primeiro colocado.

Seu programa deverá usar um registro para guardar o tempo (ponto flutuante) dos oito atletas da prova e os dados passados pelo usuário devem ser guardados em um registro alocado dinamicamente. Seu programa deverá então encontrar o primeiro colocado, e calcular a diferença de tempo dos demais atletas para o tempo dele (essas diferenças de tempo também devem ser guardadas em memória alocada dinamicamente). Ao exibir as diferenças de tempo, no caso do atleta que ganhou a prova (cuja diferença seria zero), escreva o tempo dele na prova.

*/

#include <iostream>

struct Tempos {
    float tempo[8];
};

using namespace std;

int main() {
    float diff[8], menorTempo = 0.0;
    int indexMenor = 0;
    Tempos *tempos = new Tempos;

    for (int i = 0; i < 8; i++)
    {
        cin >> tempos -> tempo[i];

        if(i == 0) {
            menorTempo = tempos -> tempo[i];
            indexMenor = i;
        }

        if(tempos->tempo[i] < menorTempo) {
            menorTempo = tempos->tempo[i];
            indexMenor = i;
        }
    }

    for (int i = 0; i < 8; i++)
    {
        if(i != indexMenor) {
            diff[i] = tempos->tempo[i] - menorTempo;
        } else {
            diff[i] = menorTempo;
        }

        cout << diff[i] << endl;
    }
    


    delete tempos;
    

    return 0;
}