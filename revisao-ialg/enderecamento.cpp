/*
2. Implemente o código a seguir para verificar o uso do operador de endereçamento (&) e 
avalie os resultados obtidos. Se possível, avalie em computadores, sistemas operacionais e 
compiladores diferentes (ex: g++ e clang++).
*/

#include <iostream>

using namespace std;

int main(){
    int a=20;
    cout << &a << endl;

    int v[5];
    cout << v << endl;
    cout << &v << endl;
    cout << &v[0]<< endl;
		
	return 0;	
}
