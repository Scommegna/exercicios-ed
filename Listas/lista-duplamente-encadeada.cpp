/* 
 * Classe listadup, uma lista dinamicamente duplamente encadeada
 * 
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 */

#include <iostream>
#include <cstdlib>

using namespace std;

struct acaoPrograma{
    int identificador;
    string nomeAcao;
    int tempoExecucao; 
    int tempoConsumido;
};


class noh {
friend class listadup;
private: 
    acaoPrograma acao; // poderia ser outro tipo de variável
    noh* proximo;
    noh* anterior;
public:
    //noh();
    noh(acaoPrograma d);
};

// construindo dado chamando seu construtor
noh::noh(acaoPrograma d){
    acao = d;
    proximo = NULL;
    anterior = NULL;
}


// lista dinamicamente encadeada
class listadup {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista    
public:
    listadup();
    listadup(const listadup& umaLista);
    ~listadup();
    // sobrecarga do operador de atribuição
    listadup& operator=(const listadup& umaLista);  
    // inserção, remoção e procura
    void insereNoFim(acaoPrograma acao);
    void insereNoInicio(acaoPrograma acao);
    void insereNaPosicao(int posicao, acaoPrograma acao);
    int procura(string valor); // retorna a posicao
    void imprime();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
};


// constrói uma lista inicialmente vazia
listadup::listadup() {
    this->primeiro = NULL;
    this->ultimo = NULL;

    this->tamanho = 0;
}

// construtor de cópia
listadup::listadup(const listadup& umaLista) {
    *this = umaLista;
}

// destrutor da lista (chama função privada auxiliar)
listadup::~listadup( ) {
    if(!this->vazia()) this->removeTodos();
}    

// remove todos os elementos da lista
void listadup::removeTodos( ) {
    if(this->vazia()) throw runtime_error("Remoção em lista vazia!");

    while(!this->vazia()) {
        this->removeNoInicio();
    }
}    

// sobrecarga do operador de atribuição
listadup& listadup::operator=(const listadup& umaLista){
    // limpa a lista atual
    removeTodos();
     // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->acao);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

// insere por no final da lista
void listadup::insereNoFim(acaoPrograma acao) {
    noh *novo = new noh(acao);

    if(this->vazia()) {
        this->primeiro = novo;
        this->ultimo = novo;
    } else {
        novo->anterior = this->ultimo;
        this->ultimo->proximo = novo;
        this->ultimo = novo;
    }

    this->tamanho++;
}

// insere no início da lista
void listadup::insereNoInicio(acaoPrograma acao) {
    noh *novo = new noh(acao);

    if(this->vazia()) {
        this->primeiro = novo;
        this->ultimo = novo;
    } else {
        novo->proximo = this->primeiro;
        this->primeiro->anterior = novo;
        this->primeiro = novo;
    }

    this->tamanho++;
}

// insere em uma determinada posição da lista
void listadup::insereNaPosicao(int posicao, acaoPrograma acao){
    if(posicao < 0 || posicao > this->tamanho - 1) throw runtime_error("Posição Inexistente!");

    if(posicao == 0) {
        this->insereNoInicio(acao);
    } else if(posicao == this->tamanho - 1) {
        this->insereNoFim(acao);
    } else {
        noh *valor = new noh(acao);
        int pos = 0;
        noh *aux = this->primeiro;

        while(pos != posicao - 1) {
            aux = aux->proximo;
            pos++;
        }

        valor->proximo = aux->proximo;
        aux->proximo->anterior = valor;
        valor->anterior = aux;
        aux->proximo = valor;

        this->tamanho++;
    }
}
                   

int listadup::procura(string valor) {
    if(this->vazia()) throw runtime_error("Nao encontrado");

    noh *aux = this->primeiro;
    int pos = 0;

    while(pos != this->tamanho) {
        if(aux->acao.nomeAcao == valor) {
            return pos;
        }

        aux = aux->proximo;
        pos++;
    }

    return -1;
}

// método básico que *percorre* uma lista, imprimindo seus elementos
void listadup::imprime() {
   if(this->vazia()) throw runtime_error("Lista vazia!");

   noh *aux = this->primeiro;

   while(aux != NULL) {
    cout << "(" << aux->acao.identificador << ", " << aux->acao.nomeAcao << ", " << aux->acao.tempoExecucao << ", " << aux->acao.tempoConsumido << ")" << endl;

    aux = aux->proximo;
   }

   aux = this->ultimo;

   while(aux != NULL) {
    cout << "(" << aux->acao.identificador << ", " << aux->acao.nomeAcao << ", " << aux->acao.tempoExecucao << ", " << aux->acao.tempoConsumido << ")" << endl;

    aux = aux->anterior;
   }
}

// verifica se a lista está vazia
inline bool listadup::vazia() {
    return (this->primeiro == NULL);
}

void listadup::removeNoInicio() {
    if(this->vazia()) throw runtime_error("Remoção em lista vazia!");

    noh *aux = this->primeiro;

    this->primeiro = aux->proximo;

    if(this->primeiro) {
        this->primeiro->anterior = NULL;
    }

    aux->proximo = NULL;
    delete aux;

    this->tamanho--;

    if(this->vazia()) {
        this->ultimo = NULL;
    }
}


void listadup::removeNoFim() {
    if(this->vazia()) throw runtime_error("Remoção em lista vazia!");

    noh *aux = this->ultimo;

    this->ultimo = aux->anterior;

    if(this->ultimo) {
        this->ultimo->proximo = NULL;
    }

    aux->anterior = NULL;
    delete aux;

    this->tamanho--;

    if(this->vazia()) {
        this->primeiro = NULL;
    }
}


int main() {
    listadup minhaLista;
    acaoPrograma info;
    char comando;
    int posicao;
    string nomeEquipe;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.identificador >> info.nomeAcao >> info.tempoExecucao >> info.tempoConsumido;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;             
                case 's': // procurar
                    cin >> nomeEquipe;
                    posicao = minhaLista.procura(nomeEquipe);
                    if(posicao == -1)
                        cout << "Nao encontrado"<< endl;
                    else
                        cout << posicao << endl;
                    break;                    
                case 'r': // remover
                    minhaLista.removeNoInicio();
                    break;
                case 'a': // remover
                    minhaLista.removeNoFim();
                    break;                                   
                case 'p': // limpar tudo
                    minhaLista.imprime();
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