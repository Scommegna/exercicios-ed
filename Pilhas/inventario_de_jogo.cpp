#include <iostream>
#include <stdexcept>

using namespace std;

struct Dado {
    string nome;
    char tipo;
    int valor;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado& umDado) {
    cout << "Nome: " << umDado.nome << " " << "Tipo: " << umDado.tipo << " " << "Valor: " << umDado.valor << endl;
}

class Noh {
    friend class Pilha;
    private:
        Dado mDado; // poderia ser outro tipo de variável
        Noh* mProx;
    public:
        Noh(Dado v) {
            mDado = v;
            mProx = NULL;
        }        
};

class Pilha {
    public:
        // Constrói pilha vazia.
        Pilha();
        // Destrutor que desaloca memória.
        ~Pilha();
        // Retira e retorna o valor que estiver no mPtTopo da pilha.
        // Escreve uma mensagem de erro se não for possível desempilhar.
        Dado Desempilhar(); // retorna o mPtTopo da Pilha.
        // Insere um valor na pilha.
        void Empilhar(const Dado& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Imprime o valor que está no mPtTopo sem desempilhar.
        inline void Topo();
        // Informa se a pilha está Vazia.
        inline bool Vazia();
    private:
        Noh* mPtTopo;
        int length;
};

Pilha::Pilha() {
    this->mPtTopo = NULL;
    this->length = 0;
}

Pilha::~Pilha() {
    if(this->length != 0) {
        this->LimparTudo();
    }
    delete this;
}

Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    else {
        Noh *aux = mPtTopo;
        Dado dado = aux->mDado;
        mPtTopo = aux->mProx;

        delete aux;
        this->length--;

        return dado;
    }
}

void Pilha::Empilhar(const Dado& d) {
   Noh *novo_no = new Noh(d);
   novo_no->mProx = this->mPtTopo;
   this->mPtTopo = novo_no;
   this->length++;
}

void Pilha::LimparTudo() {
    while(this->length != 0) {
        this->Desempilhar();
    }
}

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    else {
        imprimir_dado(this->mPtTopo->mDado);
    }
    
}

bool Pilha::Vazia() {
    return this->length == 0;
}


int main() {
    Pilha pilha;
    Dado info;
    char comando;
    do {
        try{
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
                    pilha.Topo();
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