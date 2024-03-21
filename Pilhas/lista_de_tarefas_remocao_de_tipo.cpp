/* Classe pilha estatica
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 */
#include <iostream>

using namespace std;

const int PILHAVAZIA = -1;
const int TAMANHOPILHA = 6;

struct Dado {
    string nome;
    char tipo;
    int valor;
};

// Imprime informações de um dado qualquer.
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
        // Constrói pilha vazia.
        Pilha();
        // Destrutor que desaloca memória.
        ~Pilha();
        // Retira e retorna o valor que estiver no topo da pilha.
        Dado Desempilhar(); 
        // Insere um elemento na pilha.
        void Empilhar(const Dado& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Imprime o valor que está no topo sem desempilhar.
        inline void Topo();
        // Informa se a pilha está Vazia.
        inline bool Vazia();
        // Informa se a pilha está Cheia.
        inline bool Cheia();
        void RemoverTipo(char t);
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

void Pilha::RemoverTipo(char t) {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");

    Pilha aux = Pilha();

    while(!this->Vazia()) {
        Dado aux2 = this->Desempilhar();

        if(aux2.tipo != t) {
            aux.Empilhar(aux2);
        }
    }

    while(!aux.Vazia()) {
        this->Empilhar(aux.Desempilhar());
    }
}


int main() {
    Pilha pilha;
    Dado info;
    char comando;
    char tipo;
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
                case 'x': 
                    cin >> tipo;
                    pilha.RemoverTipo(tipo);
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