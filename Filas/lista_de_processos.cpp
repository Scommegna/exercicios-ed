/* Classe fila estatica
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 */
#include <iostream>

using namespace std;

const int FILAVAZIA = -1;
const int CAPACIDADE_FILA = 6;

struct Dado {
    string nome;
    string assunto;
    char tipo;
    int nProcesso;
};

// Imprime informações de um dado qualquer.
void imprimir_dado(const Dado& umDado){
    cout << "Nome: " << umDado.nome << " Assunto: " << umDado.assunto << " Tipo: " << umDado.tipo << " Processo: " << umDado.nProcesso << endl;
}

class Fila {
    private:
        Dado* mFila;
        int posPrimeiro, posUltimo, tam;
    public:
        // Constrói fila vazia.
        Fila();
        // Destrutor que desaloca memória.
        ~Fila();
        // Retira e retorna o elemento que estiver na primeira posição.
        Dado Desenfileirar(); 
        // Insere um elemento na fila.
        void Enfileirar(const Dado& d);
        // Apagar todos os dados da fila.
        void LimparTudo();
        // Imprime os valores do elemento que está na frente da fila, sem Desenfileirar.
        inline void PrimeiroDaFila();
        // Informa se a fila está Vazia.
        inline bool Vazia();
        // Informa se a fila está Cheia.
        inline bool Cheia();
};

Fila::Fila(){
    this->mFila = new Dado[CAPACIDADE_FILA];
    this->posPrimeiro = FILAVAZIA;
    this->posUltimo = FILAVAZIA;
    tam = 0;
}

Fila::~Fila() {
    if(!this->Vazia()) {
        this->LimparTudo();
    }

    delete [] this->mFila;
}

Dado Fila::Desenfileirar() {
    if (this->Vazia()) throw runtime_error("Erro: fila vazia!");
    Dado aux = this->mFila[posPrimeiro];

    if(this->posPrimeiro == this->posUltimo) {
        this->posPrimeiro = -1;
        this->posUltimo = -1;
    } else {
        this->posPrimeiro = (this->posPrimeiro + 1) % CAPACIDADE_FILA;
    }

    tam--;

    return aux;
}

void Fila::Enfileirar(const Dado& d) {
    if (this->Cheia()) throw runtime_error("Erro: fila cheia!");

    if(this->posPrimeiro == -1) {
        this->posPrimeiro++;
    }

    this->posUltimo = (this->posUltimo + 1) % CAPACIDADE_FILA;

    this->mFila[posUltimo] = d;

    tam++;
}

void Fila::LimparTudo() {
    while(!this->Vazia()) {
        this->Desenfileirar();
    }
}

void Fila::PrimeiroDaFila() {
    if (this->Vazia()) throw runtime_error("Erro: fila vazia!");
    imprimir_dado(this->mFila[posPrimeiro]);     
}

bool Fila::Vazia() {
    return this->tam == 0;
}

bool Fila::Cheia() {
    return this->tam == CAPACIDADE_FILA;
}


int main() {
    Fila fila;
    Dado info;
    char comando;
    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.assunto >> info.tipo >> info.nProcesso;
                    fila.Enfileirar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(fila.Desenfileirar());
                    break;
                case 'l': // limpar tudo
                    fila.LimparTudo();
                    break;
                case 'e': // espiar 
                    if(!fila.Vazia())               
                        fila.PrimeiroDaFila();
                    else
                        cout << "Erro: fila vazia!"<< endl;
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