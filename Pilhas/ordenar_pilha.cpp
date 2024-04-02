/* Classe pilha estatica
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 */
#include <iostream>

using namespace std;

// Imprime informações de um dado qualquer.
void imprimir_dado(const int& umDado){
    cout << umDado << " ";
}

class Pilha {
    private:
        int* mPilha;
        int posTopo;
        int tamanho;
    public:
        // Constrói pilha vazia.
        Pilha(int tam);
        // Destrutor que desaloca memória.
        ~Pilha();
        // Retira e retorna o valor que estiver no topo da pilha.
        int Desempilhar(); 
        // Insere um elemento na pilha.
        void Empilhar(const int& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Imprime o valor que está no topo sem desempilhar.
        int Topo();
        // Informa se a pilha está Vazia.
        inline bool Vazia();
        // Informa se a pilha está Cheia.
        inline bool Cheia();
        void Ordenar();
};

Pilha::Pilha(int tam){
    this->tamanho = tam;
    this->mPilha = new int[tamanho];

    this->posTopo = - 1;
}

Pilha::~Pilha() {
    if(!this->Vazia()) {
        this->LimparTudo();
    }
    delete [] this->mPilha;
}

int Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    else {
        int aux = this->mPilha[posTopo];
        this->posTopo--;

        return aux;
    }
}

void Pilha::Empilhar(const int& d) {
    if (this->Cheia()) throw runtime_error("Erro: pilha cheia!");
    else {
        this->posTopo++;
        this->mPilha[posTopo] = d;
    }        
}

void Pilha::LimparTudo() {
    while(this->posTopo != -1) {
        this->Desempilhar();
    }

}

int Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    else {
        return this->mPilha[this->posTopo];
    }  

}

bool Pilha::Vazia() {
    return this->posTopo == -1;
}

bool Pilha::Cheia() {
    return this->posTopo == tamanho - 1;
}

void Pilha::Ordenar() {
    Pilha aux(this->tamanho);

    while(!this->Vazia()) {
        int temp = this->Desempilhar();

        while(!aux.Vazia() && aux.Topo() > temp) {
            this->Empilhar(aux.Desempilhar());
        }

        aux.Empilhar(temp);
    }

    while(!aux.Vazia()) {
        this->Empilhar(aux.Desempilhar());
    }
}


int main() {
    int size = 0, value;
    

    cin >> size;

    Pilha pilha(size);

    for(int i = 0; i < size; i++) {
        cin >> value;
        pilha.Empilhar(value);
    }

    pilha.Ordenar();

    while (!pilha.Vazia()) {
        imprimir_dado(pilha.Desempilhar());
    }
    cout << endl;
    return 0;
}