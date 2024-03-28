/* Classe Fila encadeada
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 */
#include <iostream>
#include <stdexcept>

using namespace std;

struct Dado {
    string nome;
    int premio;
    char tipo;
    int tempo;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado& umDado) {
    cout << "Nome: " << umDado.nome << " Premio: " << umDado.premio << " Tipo: " << umDado.tipo << " tempo: " << umDado.tempo << endl;
}

class Noh {
    friend class Fila;
    private:
        Dado mDado; // poderia ser outro tipo de variável
        Noh* mProx;
    public:
        Noh(Dado v) {
            mDado = v;
            mProx = NULL;
        }        
};

class Fila {
    public:
        // Constrói Fila vazia.
        Fila();
        // Destrutor que desaloca memória.
        ~Fila();
        // Retira e retorna o elemento que estiver na frente da Fila.
        // Escreve uma mensagem de erro se não for possível desenfileirar.
        Dado Desenfileirar(); 
        // Insere um elemento na Fila.
        void Enfileirar(const Dado& d);
        // Apagar todos os dados da Fila.
        void LimparTudo();
        // Retorna o elemento que está na frente da Fila, sem desenfileirar.
        inline void Primeiro();
        // Informa se a Fila está Vazia.
        inline bool Vazia();
        void ImprimePremio(char t);
    private:
        Noh* mPtPrimeiro;
        Noh* mPtrUltimo;
        int size;
};

Fila::Fila() {
    this->mPtPrimeiro = NULL;
    this->mPtrUltimo = NULL;
    this->size = 0;   
}

Fila::~Fila() {
    while(!this->Vazia()) {
        this->LimparTudo();
    }
}

Dado Fila::Desenfileirar() {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
    Dado dado = this->mPtPrimeiro->mDado;
    Noh *aux = this->mPtPrimeiro;
    
    this->mPtPrimeiro = this->mPtPrimeiro->mProx;

    delete aux;

    size--;

    if(this->Vazia()) {
        this->mPtrUltimo = NULL;
    }

    return dado;
}

void Fila::Enfileirar(const Dado& d) {
   Noh *aux = new Noh(d);

   if(this->Vazia()) {
    this->mPtPrimeiro = aux;
   } else {
    this->mPtrUltimo->mProx = aux;
   }

   this->mPtrUltimo = aux;

   size++;
}

void Fila::LimparTudo() {
    while(!this->Vazia()) {
        this->Desenfileirar();
    }
}

void Fila::Primeiro() {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
    imprimir_dado(this->mPtPrimeiro->mDado);
}

bool Fila::Vazia() {
    return this->size == 0;
}

void Fila::ImprimePremio(char t) {
    Fila aux = Fila();
    int counter = 0;
    int sizeAux = this->size;

    while(sizeAux != 0) {
        Dado aux2 = this->Desenfileirar();

        if(aux2.tipo == t) {
            counter += aux2.premio;
            aux.Enfileirar(aux2);
        } else {
            this->Enfileirar(aux2);
        }

        sizeAux--;
    }

    while(!this->Vazia()) {
        aux.Enfileirar(this->Desenfileirar());
    }

    while(!aux.Vazia()) {
        this->Enfileirar(aux.Desenfileirar());
    }

    cout << counter << endl;
}


int main() {
    Fila fila;
    Dado info;
    char comando;
    char tipo;
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.premio >> info.tipo >> info.tempo;
                    fila.Enfileirar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(fila.Desenfileirar());
                    break;
                case 'l': // limpar tudo
                    fila.LimparTudo();
                    break;
                case 'e': // espiar                
                    fila.Primeiro();
                    break;
                case 'p':
                    cin >> tipo;
                    fila.ImprimePremio(tipo);
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
    while (not fila.Vazia()) {
        imprimir_dado(fila.Desenfileirar());
    }
    cout << endl;
    return 0;
}