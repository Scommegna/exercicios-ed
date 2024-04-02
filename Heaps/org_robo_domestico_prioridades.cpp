#include <iostream>
#include <utility> 
#include <stdexcept> 

using namespace std;

//Lucas Scommegna - 202310208

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
    } else if((esquerda <= this->tamanho - 1) && (this->heap[esquerda] == this->heap[i])) {
        maior = this->heap[esquerda].energiaGasta < this->heap[i].energiaGasta ? esquerda : i;
    }

    if((direita <= this->tamanho - 1) && (this->heap[direita] > this->heap[maior])) {
        maior = direita;
    } else if((direita <= this->tamanho - 1) && (this->heap[direita] == this->heap[maior])) {
        maior = this->heap[maior].energiaGasta < this->heap[direita].energiaGasta ? maior : direita;
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
    } else if(this->heap[i] == this->heap[p]) {
        if(this->heap[i].energiaGasta < this->heap[p].energiaGasta) {
            swap(this->heap[i], this->heap[p]);
            this->corrigeSubindo(p);
        }
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


int main() {
    int capacidade;
    dado info;
    char comando;

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