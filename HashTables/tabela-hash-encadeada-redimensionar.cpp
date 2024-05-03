//lucas scommegna

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

const int UMPRIMO = 7;


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


class lista {
    friend class tabelaHash;
    private:
        noh* primeiro; 
        unsigned short numElementos; 
    public:
        lista() {
            this->primeiro = NULL;
            this->numElementos = 0;
        } 
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
        } 
        unsigned short tamanho() { return numElementos; } 
        
        void insere(const string& c, const char& t,const int& v) {
            noh *aux = new noh(c, t, v);

            if(this->tamanho() == 0) {
                this->primeiro = aux;
            } else {
                aux->proximo = this->primeiro;
                this->primeiro = aux;
            }

            this->numElementos++;
        }
        
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
        
        lista* tabela;
        
        unsigned numPosicoes;
        
        unsigned funcaoHash(const string& s) {
            return funcaoHash(s, numPosicoes);
        } 
        
        unsigned funcaoHash(const string& s, int cap) {
            unsigned pos = 0;
            for (unsigned int i = 0; i < s.size(); ++i)
                pos = (UMPRIMO * pos + s[i]) % cap;
            return pos;
        }
    public:
        
        tabelaHash(unsigned cap = 100) {
            this->tabela = new lista[cap];

            this->numPosicoes = cap;
        }
        ~tabelaHash(){ 
            delete [] this->tabela;
        }
        
        bool insere(const string& c, char& t, const int& v) {
            unsigned pos = this->funcaoHash(c, this->numPosicoes);


            if(!this->tabela[pos].verificaOcorrencia(c)) {
                this->tabela[pos].insere(c, t, v);
                
                cout << "chave " << "'" << c << "'" <<  " inserida na posição " << pos << endl;

                return true;
            }

            return false;  
        }
       
        bool valor(const string& c, char& tipoBuscado, int& valorRetorno) {
            unsigned pos = this->funcaoHash(c, this->numPosicoes);

            if(this->tabela[pos].busca(c, tipoBuscado, valorRetorno)) {
                return true;
            }

            return false;
        }
        
        bool remove(const string& c) {
            unsigned pos = this->funcaoHash(c, this->numPosicoes);

            if(this->tabela[pos].verificaOcorrencia(c)) {
                return this->tabela[pos].remove(c);
            }

            return false;
        }
       
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
                case 'i': 
                    cin >> chave >> tipo>> valor;
                    if (!tabela.insere(chave, tipo, valor))
                        cout << "Erro na inserção: chave já existente!" << endl;
                    break;
                case 'r': 
                    cin >> chave;
                    if (!tabela.remove(chave))
                        cout << "Erro na remoção: chave não encontrada!" << endl;
                    break;
                case 'l': 
                    cin >> chave;
                    if (!tabela.valor(chave,tipo,valor))
                        cout << "Erro na busca: chave não encontrada!" << endl;
                    else
                        cout << "Tipo: " << tipo << " Valor: " << valor << endl;
                    break;
                case 'p': 
                    tabela.imprime();
                    break;

                case 'f': 
                    
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); 
    tabela.imprime();
    cout << endl;
    return 0;
}