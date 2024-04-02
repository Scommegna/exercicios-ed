#include <iostream>

using namespace std;

const int PILHAVAZIA = -1;
const int TAMANHOPILHA = 6;

//Lucas Scommegna - 202310208
struct Dado {
    string nome;
    char tipo;
    int valor;
};


void imprimir_dado(const Dado& umDado){
    cout<< "Nome: " << umDado.nome << " ";
    cout<< "Tipo: " << umDado.tipo << " ";
    cout<< "Valor: " << umDado.valor << endl;
}

class Pilha {
    private:
        Dado* mPilha;
        int posTopo;
    public:
        Pilha();
        ~Pilha();
        Dado Desempilhar(); 
        void Empilhar(const Dado& d);
        void LimparTudo();
        inline void Topo();
        inline bool Vazia();
        inline bool Cheia();
};

Pilha::Pilha(){
    this->mPilha = new Dado[TAMANHOPILHA];
    this->posTopo = PILHAVAZIA;
}

Pilha::~Pilha() {
    if(!this->Vazia()) {
        this->LimparTudo();
    }
    delete [] this->mPilha;
}

Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    else {
        Dado aux = this->mPilha[posTopo];
        this->posTopo--;

        return aux;
    }
}

void Pilha::Empilhar(const Dado& d) {
    if (this->Cheia()) {
        Pilha aux = Pilha();

        while(!this->Vazia()) {
            if(this->posTopo == 0) {
                imprimir_dado(this->Desempilhar());
            } else {
                aux.Empilhar(this->Desempilhar());
            }
        }

        while(!aux.Vazia()) {
            this->Empilhar(aux.Desempilhar());
        }

        this->posTopo++;
        this->mPilha[posTopo] = d;
    }
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

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    else {
        imprimir_dado(this->mPilha[this->posTopo]);
    }  

}

bool Pilha::Vazia() {
    return this->posTopo == PILHAVAZIA;
}

bool Pilha::Cheia() {
    return this->posTopo == TAMANHOPILHA - 1;
}


int main() {
    Pilha pilha;
    Dado info;
    char comando;
    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.tipo >> info.valor;
                    pilha.Empilhar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(pilha.Desempilhar());
                    break;
                case 'l': // limpar tudo
                    pilha.LimparTudo();
                    break;
                case 'e': // espiar 
                    if(!pilha.Vazia())               
                        pilha.Topo();
                    else
                        cout << " Pilha vazia!"<< endl;
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    while (not pilha.Vazia()) {
        imprimir_dado(pilha.Desempilhar());
    }
    cout << endl;
    return 0;
}