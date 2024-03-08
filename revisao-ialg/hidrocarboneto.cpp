/*
Um hidrocarboneto é um composto químico formado por átomos de carbono e hidrogênio. Faça um programa que crie um registro chamado Hidrocarboneto contendo os campos inteiros C e H usados para guardar a quantidade de carbonos e hidrogênios, respectivamente, de um hidrocarboneto. No subprograma principal aloque dinamicamente um registro Hidrocarboneto e peça ao usuário as quantidades de carbono e hidrogênio do mesmo. Sabendo que massa molecular do carbono é 12 e do hidrogênio é 1, seu programa deverá calcular e exibir a massa molecular do composto.
*/

#include <iostream>

using namespace std;

struct Hidrocarboneto {
    int C;
    int H;
};

int main() {
    Hidrocarboneto *cadeia = new Hidrocarboneto;
    int massaMolecular = 0;

    cin >> cadeia -> C >> cadeia -> H;

    massaMolecular = cadeia->C * 12 + cadeia->H * 1;

    delete cadeia;

    cout << massaMolecular;

    return 0;
}