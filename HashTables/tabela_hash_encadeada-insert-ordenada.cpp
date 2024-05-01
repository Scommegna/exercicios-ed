/* 
 * Tabela tabelaHash usando lista explícita
 * by Joukim, 2019
 * Atualizado por Renato, 2023
 */

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7;

// Um noh guarda um par (chave / valor) 
class noh {
    friend class lista;
    friend class tabelaHash;
    private:
        string chave;
        char tipo;
        int valor;
        noh* proximo;
        noh(const string& c = "", const char& t = 'a', const int& v=0, noh* prox = NULL):
            chave(c), tipo(t), valor(v), proximo(prox) { }
};

// Uma lista guarda todos os Nos cuja chave foi mapeada na mesma posição.
class lista {
    friend class tabelaHash;
    private:
        noh* primeiro; // primeiro nó da lista
        unsigned short numElementos; // quantidade de valores na lista
    public:
        lista() {
            this->primeiro = NULL;
            this->numElementos = 0;
        } // Construtor
        ~lista() {
            if(this->tamanho() != 0) {
                noh *aux = this->primeiro;

                while(this->tamanho() != 0) {
                    this->primeiro = this->primeiro->proximo;
                    delete aux;
                    aux = this->primeiro;
                    this->numElementos--;
                }
            }
        } // Destrutor
        unsigned short tamanho() { return numElementos; } // Consulta do Tamanho
        // Adiciona um novo par (chave, valor) na lista
        // Insere no início, para não precisar de ponteiro para o fim
        void insere(const string& c, const char& t,const int& v) {
            noh *aux = new noh(c, t, v);

            if(this->tamanho() == 0) {
                this->primeiro = aux;
            } else if(aux->chave < this->primeiro->chave) {
                aux->proximo = this->primeiro;
                this->primeiro = aux;
            } else {
                noh *aux2 = this->primeiro;
                noh *aux3 = this->primeiro;

                while(aux2 != NULL && aux->chave > aux2->chave) {
                    aux3 = aux2;
                    aux2 = aux2->proximo;
                }

                aux->proximo = aux2;
                aux3->proximo = aux;
            }

            this->numElementos++;
        }
        // Remove o noh com dada chave da lista.
        // Se a chave não existe, retorna informação.
        bool remove(const string& c) {
            if(this->tamanho() == 0) {
                return false;
            } 

            noh *aux = this->primeiro;

            if(aux->chave == c) {
                this->primeiro = aux->proximo;
                delete aux;
                this->numElementos--;

                return true;
            }

            noh *ant = this->primeiro;
            aux = this->primeiro->proximo;
            

            while(aux != NULL) {
                if(aux->chave == c) {
                    ant->proximo = aux->proximo;
                    aux->proximo = NULL;
                    delete aux;

                    this->numElementos--;

                    if(this->numElementos == 0) {
                        this->primeiro = NULL;
                    }

                    return true;
                }

                aux = aux->proximo;
                ant = ant->proximo;
            }

            
            return false;
            
        }
        // Busca um elemento na lista, retorna falso se não encontrado
        // o valor buscado é retornado por passagem por referência
        // na variável valorBuscado
        bool busca(const string& c, char& tipoBuscado, int& valorBuscado) {
            if(this->tamanho() == 0) {
                return false;
            } 

            noh *aux = this->primeiro;

            while(aux != NULL) {
                if(aux->chave == c) {
                    tipoBuscado = aux->tipo;
                    valorBuscado = aux->valor;

                    return true;
                }

                aux = aux->proximo;
            }

            return false;
        }
        // Verifica se já tem algum dado na lista com 
        // uma dada chave
        bool verificaOcorrencia(const string& c) {
            if(this->tamanho() == 0) {
                return false;
            } 

            noh *aux = this->primeiro;

            while(aux != NULL) {
                if(aux->chave == c) {
                    return true;
                }

                aux = aux->proximo;
            }

            return false;
        }
        // Imprime o conteúdo da lista, para fins de depuração
        void imprime() {
            noh* atual = primeiro;
            while (atual != NULL) {
                    cout << "[" << atual->chave << "/"
                         << atual->valor << "]";
                    atual = atual->proximo;
            }
        }
};


class tabelaHash {
    private:
        // vetor de ponteiros para lista
        lista* tabela;
        // quantidade de posições na tabela hash
        unsigned numPosicoes;
        // converte uma chave (string) num endereço da tabela 
        // - versão simples
        unsigned funcaoHash(const string& s) {
            return funcaoHash(s, numPosicoes);
        } 
        // converte uma chave (string) num endereço da tabela 
        // - versão para redimensionamento
        unsigned funcaoHash(const string& s, int cap) {
            unsigned pos = 0;
            for (unsigned int i = 0; i < s.size(); ++i)
                pos = (UMPRIMO * pos + s[i]) % cap;
            return pos;
        }
    public:
        // construtor padrão
        tabelaHash(unsigned cap = 100) {
            this->tabela = new lista[cap];

            this->numPosicoes = cap;
        }
        ~tabelaHash(){ 
            delete [] this->tabela;
        }
        // Insere um nó com dada chave e valor.
        bool insere(const string& c, char& t, const int& v) {
            unsigned pos = this->funcaoHash(c, this->numPosicoes);


            if(!this->tabela[pos].verificaOcorrencia(c)) {
                this->tabela[pos].insere(c, t, v);
                
                cout << "chave " << "'" << c << "'" <<  " inserida na posição " << pos << endl;

                return true;
            }

            return false;  
        }
        // Retorna um valor associado a uma dada chave.
        // Se a chave não existe, retorna "NÃO ENCONTRADO!".
        bool valor(const string& c, char& tipoBuscado, int& valorRetorno) {
            unsigned pos = this->funcaoHash(c, this->numPosicoes);

            if(this->tabela[pos].busca(c, tipoBuscado, valorRetorno)) {
                return true;
            }

            return false;
        }
        // Retira do hash um nó com dada chave.
        bool remove(const string& c) {
            unsigned pos = this->funcaoHash(c, this->numPosicoes);

            if(this->tabela[pos].verificaOcorrencia(c)) {
                return this->tabela[pos].remove(c);
            }

            return false;
        }
        // Imprime o conteúdo interno do hash (para fins de depuração)
        void imprime() {
            for (unsigned i = 0; i < numPosicoes; i++) {
                cout << i << ": ";
                tabela[i].imprime();
                cout << endl;
            }
        }
};

int main() {
    int tamanhoTH;
    cin >> tamanhoTH;
    tabelaHash tabela(tamanhoTH);
    char comando;
    string chave;
    char tipo = 'a';
    int valor = -1;    
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> chave >> tipo>> valor;
                    if (!tabela.insere(chave, tipo, valor))
                        cout << "Erro na inserção: chave já existente!" << endl;
                    break;
                case 'r': // remover
                    cin >> chave;
                    if (!tabela.remove(chave))
                        cout << "Erro na remoção: chave não encontrada!" << endl;
                    break;
                case 'l': // remover
                    cin >> chave;
                    if (!tabela.valor(chave,tipo,valor))
                        cout << "Erro na busca: chave não encontrada!" << endl;
                    else
                        cout << "Tipo: " << tipo << " Valor: " << valor << endl;
                    break;
                case 'p': // mostrar estrutura
                    tabela.imprime();
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
    tabela.imprime();
    cout << endl;
    return 0;
}