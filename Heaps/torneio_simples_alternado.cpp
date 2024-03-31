#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

class torneio
{
private:
    int *heap;
    int tamanho;
    int capacidade;
    int inicioDados;
    inline int pai(int filho);
    inline int esquerda(int getPai);
    inline int direita(int getPai);
    void arruma();
    void compete(int i, bool muda);

public:
    torneio(int vet[], int tam);
    ~torneio();
    void verBaseMaior();
};

torneio::torneio(int vet[], int tam)
{
    this->capacidade = 1;
    while (capacidade < tam)
    {
        this->capacidade *= 2;
    }

    this->capacidade = this->capacidade - 1 + tam;

    this->heap = new int[this->capacidade];
    inicioDados = this->capacidade - tam;

    memcpy(&heap[inicioDados], vet, tam * sizeof(int));

    this->tamanho = tam;
    arruma();
}

torneio::~torneio()
{
    delete [] this->heap;
}

int torneio::pai(int filho)
{
    return (filho - 1) / 2;
}

int torneio::esquerda(int pai)
{
    return 2 * pai + 1;
}

int torneio::direita(int pai)
{
    return 2 * pai + 2;
}

void torneio::arruma()
{
    bool muda = true;
    for (int i = inicioDados - 1; i >= 0; i--)
    {
        compete(i, muda);
        muda = !muda;
    }
}

void torneio::compete(int i, bool muda)
{
    int esq = esquerda(i);
    int dir = direita(i);
    int maior = -1;


    if (muda == true) {
        if (esq < capacidade)
        {
            if ((dir < this->capacidade) && (this->heap[dir] > this->heap[esq]))
            {
                maior = dir;
            }
            else
            {
                maior = esq;
            }
                this->heap[i] = this->heap[maior];
        }
        else
        {
            this->heap[i] = -1;
        }
    } else {
        if (esq < capacidade)
        {
            if ((dir < this->capacidade) && (this->heap[dir] < this->heap[esq]))
            {
                maior = dir;
            }
            else
            {
                maior = esq;
            }
                this->heap[i] = this->heap[maior];
        }
        else
        {
            this->heap[i] = -1;
        }
    }
    
}

void torneio::verBaseMaior()
{
    cout << this->heap[0];
}

int main()
{
    int tam;
    cin >> tam;
    

    int vet[tam];
    for (int i = 0; i < tam; i++)
    {
        cin >> vet[i];
    }

    torneio participantes(vet, tam);

    participantes.verBaseMaior();

    return 0;
}