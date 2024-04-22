/* 
 * Classe lista, uma lista dinamicamente encadeada
 * 
 * by Joukim, 2017-2019, Estruturas de Dados
 * alterado em 2023 by Renato
 */

#include <iostream>
#include <cstdlib>

using namespace std;


struct equipe{
    string nomeEquipe;
    string lider;
    string linguagem; 
    int qtdMembros;
};

class noh {
friend class lista;
private:
    equipe elenco; // poderia ser outro tipo de variável
    noh* proximo;
public:
    //noh();
    noh(equipe d);
};

// construindo time chamando seu construtor
noh::noh(equipe d){
    elenco = d;
    proximo = NULL;
}


// lista dinamicamente encadeada
class lista {
private:
    noh* primeiro;
    noh* ultimo;
    int tamanho;
    void removeTodos(); // remove todos os elementos da lista
     // imprime reverso a partir de um nó -> exemplo de uso de recursão
    //void imprimeReversoAux(noh* umNoh);
public:
    // construtores e destrutor
    lista();
    lista(const lista& umaLista);
    ~lista();
    // sobrecarga do operador de atribuição
    lista& operator=(const lista& umaLista);  
    // inserção, remoção e procura
    inline void insere(equipe elenco);
    void insereNoFim(equipe elenco);
    void insereNoInicio(equipe elenco);
    void insereNaPosicao(int posicao, equipe elenco);
    int procura(string valor); // retorna a posição do nó com va
    // métodos adicionais (impressão, vazia)
    void imprime();
    void imprimeReverso();
    inline bool vazia();
    void removeNoFim();
    void removeNoInicio();
    void removeEquipe(string equipe);
};


// constrói uma lista inicialmente vazia
lista::lista() {
    this->primeiro = NULL;
    this->ultimo = NULL;
    this->tamanho = 0;
}

// construtor de cópia
lista::lista(const lista& umaLista) {
    *this = umaLista;
}

// destrutor da lista (chama função privada auxiliar)
lista::~lista( ) {
    if(!this->vazia()) this->removeTodos();
}    

// remove todos os elementos da lista
void lista::removeTodos() {
    if(this->vazia()) throw runtime_error("Remoção em lista vazia!");

    while(!this->vazia()) {
        this->removeNoInicio(); 
    }
}    

// sobrecarga do operador de atribuição
lista& lista::operator=(const lista& umaLista){
    // limpa a lista atual
    removeTodos();
     // percorre a lista recebida como parâmetro, copiando os dados
    noh* aux = umaLista.primeiro;
    
    while (aux != NULL) {
        insereNoFim(aux->elenco);
        aux = aux->proximo;  
    }
    
    return *this; 
}  

// insere no final da lista
void lista::insereNoFim(equipe elenco) {
    noh *aux = new noh(elenco);

    if(this->vazia()) {
        this->primeiro = aux;
        this->ultimo = aux;
    } else {
        this->ultimo->proximo = aux;
        this->ultimo = aux;
    }

    this->tamanho++;
}

// insere no início da lista
void lista::insereNoInicio(equipe elenco) {
    noh *aux = new noh(elenco);

    if(this->vazia()) {
        this->primeiro = aux;
        this->ultimo = aux;
    } else {
        aux->proximo = this->primeiro;
        this->primeiro = aux;
    }

    this->tamanho++;
}

void lista::removeEquipe(string equipe) {
    if(this->vazia()) throw runtime_error("Lista vazia!");

    int pos = this->procura(equipe);

    if(pos == 0) {
        this->removeNoInicio();
    } else if(pos == this->tamanho - 1) {
        this->removeNoFim();
    } else {
        noh *aux = this->primeiro;
        noh *aux2 = this->primeiro->proximo;

        if(aux2->elenco.nomeEquipe == equipe) {
            aux->proximo = aux2->proximo;
            aux2->proximo = NULL;

            delete aux2;
        } else {
            int counter = 0;

            while(counter != pos - 1) {
                aux = aux->proximo;
                aux2 = aux2->proximo;
                counter++;
            }

            aux->proximo = aux2->proximo;
            aux2->proximo = NULL;

            delete aux2;
        }

        this->tamanho--;
    }
}

// insere em uma determinada posição da lista
void lista::insereNaPosicao(int posicao, equipe elenco){
    if(posicao < 0 || posicao > this->tamanho - 1) throw runtime_error("Posição Inexistente!");

    if(this->vazia()) {
        noh *valor = new noh(elenco);
        this->primeiro = valor;
        this->ultimo = valor;
        this->tamanho++;
    } else if(posicao == 0) {
        this->insereNoInicio(elenco);
    } else if(posicao == this->tamanho - 1) {
        this->insereNoFim(elenco);
    } else {
        noh *valor = new noh(elenco);
        
        noh *aux = this->primeiro;
        int counter = 0;

        while(counter != posicao - 1) {
            aux = aux->proximo;
            counter++;
        }

        valor->proximo = aux->proximo;
        aux->proximo = valor;
        
        this->tamanho++;
    }

}

//procura a posição de um determinado elemento
int lista::procura(string valor) {
    if (this->vazia()) {
        throw runtime_error("Lista vazia!");
    } 

    int pos = 0;
    noh *aux = this->primeiro;

    while(pos != this->tamanho) {
        if(valor == aux->elenco.nomeEquipe) {
            return pos;
        }
        aux = aux->proximo;
        pos++;
    }

    return -1;
}


// método básico que *percorre* uma lista, imprimindo seus elementos
// poderia percorrer fazendo outra ação (multiplicando valores, por exemplo)
void lista::imprime() {
    if (this->vazia()) {
        throw runtime_error("Lista vazia!");
    } 

    noh *aux = this->primeiro;

    while(aux != NULL) {
        cout << "(" << aux->elenco.nomeEquipe << ", " << aux->elenco.lider << ", " << aux->elenco.linguagem << ", " << aux->elenco.qtdMembros << ")" << endl; 

        aux = aux->proximo;
    }

}

// verifica se a lista está vazia
inline bool lista::vazia() {
    return (primeiro == NULL);
}
   
void lista::removeNoFim() {
    if(this->vazia()) throw runtime_error("Remoção em lista vazia!");

    noh *aux = this->primeiro;
    int counter = 0;

    while(counter != this->tamanho - 2) {
        aux = aux->proximo;
        counter++;
    }

    noh *aux2 = aux->proximo;

    aux->proximo = NULL;

    this->ultimo = aux;

    delete aux2;

    this->tamanho--;

    if(this->vazia()) {
        this->primeiro = NULL;
    }
}
    
void lista::removeNoInicio() {
    if(this->vazia()) throw runtime_error("Remoção em lista vazia!");

    noh *aux = this->primeiro;
    this->primeiro = aux->proximo;

    delete aux;

    this->tamanho--;

    if(this->vazia()) {
        this->ultimo = NULL;
    }
}

int main() {
    lista minhaLista;
    equipe info;
    char comando;
    int posicao;
    string nomeEquipe;
    int pos;

    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoInicio(info);
                    break;
                case 'h': // inserir
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNoFim(info);
                    break;             
                case 'm': // inserir
                    cin >> posicao;
                    cin >> info.nomeEquipe >> info.lider >> info.linguagem >> info.qtdMembros;
                    minhaLista.insereNaPosicao(posicao,info);
                    break;             
                case 's': // remover
                    cin >> nomeEquipe;
                    pos = minhaLista.procura(nomeEquipe);

                    if(pos == -1) {
                        cout << "Nao encontrado" << endl;
                    } else {
                        cout << pos <<endl;
                    }
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
                case 'x':
                    cin >> nomeEquipe;
                    minhaLista.removeEquipe(nomeEquipe);
                    break;
                case 'f': // finalizar
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