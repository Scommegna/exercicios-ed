/*
    MaxHeap, para alteração de prioridade
    by joukim & bruno, 2019
    alterado em 2023 by Renato
*/

#include <iostream>
#include <utility> // para usar swap
#include <stdexcept> // para usar exceção com runtime_error

using namespace std;

struct dado {
    string nomeTarefa;
    char tipoTarefa;
    int energiaGasta;
    int tempoEstimado;
    int prioridade;
};

bool operator>(dado d1, dado d2) {
    return d1.prioridade > d2.prioridade;
}

bool operator<(dado d1, dado d2) {
    return d1.prioridade < d2.prioridade;
}

bool operator==(dado d1, dado d2) {
    return d1.prioridade == d2.prioridade;
}

ostream& operator<<(ostream& output,const dado& d) {
    output << "[" << d.nomeTarefa << "/" << d.tipoTarefa << "/" << d.energiaGasta << "/" << d.tempoEstimado << "/" << d.prioridade <<"]"; 
    return output;
}

class MaxHeap {
private:
    dado* heap;
    int capacidade;
    int tamanho;
    inline int pai(int i);
    inline int esquerdo(int i);
    inline int direito(int i); 
    void corrigeDescendo(int i); 
    void corrigeSubindo(int i);
public:
    MaxHeap(int cap);
    ~MaxHeap();
    void imprime();
    dado retiraRaiz();
    void insere(dado d);
    void alteraValor(string l, int v);
};

MaxHeap::MaxHeap(int cap) {
    this->capacidade = cap;
    this->tamanho = 0;

    this->heap = new dado[this->capacidade];
}

MaxHeap::~MaxHeap() {
   delete [] this->heap;
}

int MaxHeap::pai(int i) {
    return (int) (i - 1) / 2;
}
    
int MaxHeap::esquerdo(int i) {
    return (int) 2*i + 1;
}
    
int MaxHeap::direito(int i) {
    return (int) 2*i + 2;
}
    
void MaxHeap::corrigeDescendo(int i) {
    int esquerda = this->esquerdo(i);
    int direita = this->direito(i);
    int maior = i;

    if((esquerda <= this->tamanho - 1) && (this->heap[esquerda] > this->heap[i])) {
        maior = esquerda;
    }

    if((direita <= this->tamanho - 1) && (this->heap[direita] > this->heap[maior])) {
        maior = direita;
    }

    if(maior != i) {
        swap(this->heap[i], this->heap[maior]);
        this->corrigeDescendo(maior);
    }

}

void MaxHeap::corrigeSubindo(int i) {
    int p = this->pai(i);

    if(this->heap[i] > this->heap[p]) {
        swap(this->heap[i], this->heap[p]);

        this->corrigeSubindo(p);
    }
}
        
void MaxHeap::imprime() {
    if(this->tamanho == 0) throw runtime_error("Heap vazia!");
    for (int i=0; i<tamanho; i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

dado MaxHeap::retiraRaiz() {
    if(this->tamanho < 1) {
        throw runtime_error("Erro ao retirar raiz");
    }

    dado aux = this->heap[0];
    swap(this->heap[0], this->heap[this->tamanho - 1]);
    this->tamanho--;

    corrigeDescendo(0);

    return aux;
}


void MaxHeap::insere(dado d){
    if(this->tamanho == this->capacidade) {
        throw runtime_error("Erro ao inserir");
    }

    this->heap[this->tamanho] = d;
    this->corrigeSubindo(this->tamanho);
    this->tamanho++;
}

void MaxHeap::alteraValor(string l, int v) {
    MaxHeap aux = MaxHeap(this->capacidade);
    int auxCounter = this->tamanho;
    int auxCounter2 = this->tamanho;

    while(auxCounter != 0) {
        dado aux2 = this->retiraRaiz();

        if(aux2.nomeTarefa == l) {
            aux2.prioridade = v;
        }

        aux.insere(aux2);
        auxCounter--;
    }

    while(auxCounter != auxCounter2) {
        this->insere(aux.retiraRaiz());
        auxCounter++;
    }
}


int main() {
    int capacidade;
    dado info;
    char comando;
    int valor;
    string local;

    cin >> capacidade;
    MaxHeap meuHeap(capacidade);

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nomeTarefa >> info.tipoTarefa >> info.energiaGasta >> info.tempoEstimado >> info.prioridade;
                    meuHeap.insere(info);
                    break;
                case 'r': // remover
                    cout << meuHeap.retiraRaiz().nomeTarefa << endl;
                    break;
                case 'p': // limpar tudo
                    meuHeap.imprime();
                    break;
                case 'a':
                    cin >> local >> valor;
                    meuHeap.alteraValor(local, valor);
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
    cout << endl;
    return 0;
}