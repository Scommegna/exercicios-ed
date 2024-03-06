/*
1. Implemente o código a seguir para verificar o uso do operador sizeof e avalie os 
resultados obtidos. Se possível, avalie em computadores, sistemas operacionais e 
compiladores diferentes (ex: g++ e clang++).
*/

#include <iostream>

using namespace std;

int main(){
        cout << "char " << sizeof(char) << endl;
        cout << "short " << sizeof(short) << endl;
        cout << "int " << sizeof(int) << endl;
        cout << "long " << sizeof(long) << endl;
        cout << "long long " << sizeof(long long) << endl;
        
        cout << "float " << sizeof(float) << endl;
        cout << "double " << sizeof(double) << endl;
        cout << "long double " << sizeof(long double) << endl;

        cout << "bool " << sizeof(bool) << endl;


        cout << "bool " << sizeof(int*) << endl;
        cout << "bool " << sizeof(string) << endl;
                
        return 0;
}