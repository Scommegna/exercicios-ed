/*
*  Torneio
*
*  Realiza torneio simples de numeros inteiros
*
*  Made by Renato Ramos da Silva in 18/09/23
*
*/
#include <iostream>
#include <cstring>
#include <algorithm> 
using namespace std;

const int INVALIDO = -1;

class torneio{
private:
	int *heap;
	int tamanho;
	int capacidade;
    int inicioDados;
	inline int pai(int filho);
	inline int esquerda(int getPai);
	inline int direita(int getPai);
	void arruma();
	void compete(int i);
    void verBaseMaior();

public:
	torneio(int vet[], int tam);
	~torneio();
};

//Construtor da classe
torneio::torneio(int vet[], int tam){ 

}

// Destrutor da classe
torneio::~torneio(){

}

// Retorno a posição do nó pai de um determinado elemento
int torneio::pai(int filho){  

}

// Retorna o filho à esquerda de um determinado nó
int torneio::esquerda(int pai){ 

}

// Retorna o filho à direita do nó pai
int torneio::direita(int pai){ 

}

// Faz a competição por cada posição vencedora no vetor e imprime o vencedor
void torneio::arruma(){
    
}

// Faz a competição entre os elementos
void torneio::compete(int i){ 

}

int main(){
    int tam;
    cin >> tam;

    int vet[tam];
    for(int i = 0; i < tam; i++){
        cin >> vet[i];
    }

    torneio participantes(vet, tam);

    return 0;
}