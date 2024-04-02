#include <iostream>
#include <stdexcept>

using namespace std;

//Lucas Scommegna - 202310208
struct Dado {
    string nome;
    char tipo;
    int valor;
};

void imprimir_dado(const Dado& umDado) {
    cout << "Nome: " << umDado.nome << " " << "Tipo: " << umDado.tipo << " " << "Valor: " << umDado.valor << endl;
}

class Noh {
    friend class Pilha;
    private:
        Dado mDado; 
        Noh* mProx;
    public:
        Noh(Dado v) {
            mDado = v;
            mProx = NULL;
        }        
};

class Pilha {
    public:
        Pilha();
        ~Pilha();
        Dado Desempilhar();
        void Empilhar(const Dado& d);
        void LimparTudo();
        inline void Topo();
        inline bool Vazia();
        void Ordenar();
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

void Pilha::Ordenar() {
    Dado aux;
    Pilha aux2 = Pilha();

    while(!this->Vazia()) {
        aux = this->Desempilhar();

        while(!aux2.Vazia() && aux2.mPtTopo->mDado.valor > aux.valor) {
            this->Empilhar(aux2.Desempilhar());
        }

        aux2.Empilhar(aux);
    }

    while(!aux2.Vazia()) {
        this->Empilhar(aux2.Desempilhar());
    }
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
                case 'o':
                    pilha.Ordenar();
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