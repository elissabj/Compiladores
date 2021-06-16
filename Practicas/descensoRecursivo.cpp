/*
Tema: Analisis Sintactico por descenso recursivo
Ejercicio: 
    A -> a B a
    B -> b A b 
    B -> c 

Entrada: 
    cadena
Salida:
    mensaje de aceptacion o error
*/

#include<iostream>
using namespace std;

bool tengo_c;
bool consume (const string &palabra, int &pos, char tipoProd);
void produccionA (const string &palabra, int &pos, bool &valido_s);
void produccionB (const string &palabra, int &pos, bool &valido_s);

int main(){

    bool valido_s = true;
    tengo_c = false;
    
    string palabra;
    int pos = 0;

    cin >> palabra;
    produccionA(palabra, pos, valido_s);

    (valido_s && tengo_c)? cout <<"Valido\n":cout <<"Error\n";

return 0;
}

bool consume (const string &palabra, int &pos, char tipoProd){

    if (tipoProd == 'A'){
        if(palabra[pos] == 'a'){
            pos++;
            return true;
        }
    }

    if (tipoProd == 'B'){
        if(palabra[pos] == 'b'){
            pos++;
            return true;
        }

        if(palabra[pos] == 'c'){

            if (pos == palabra.size()/2){
                tengo_c = true;
            }else{
                tengo_c = false;
            }

            pos++;
            return true;
        }
    }
    
return false;
}

void produccionA (const string &palabra, int &pos, bool &valido_s){
    char tipoProd = 'A';
    if(consume(palabra, pos, tipoProd)){
        if (pos != palabra.size()){
            produccionB(palabra, pos, valido_s);
        }
    }else{
        valido_s = false; 
    }

return;
}

void produccionB (const string &palabra, int &pos, bool &valido_s){
    char tipoProd = 'B';
    if(consume(palabra, pos, tipoProd)){
        if (pos != palabra.size()){
            produccionA(palabra, pos, valido_s);
        }
    }else{
        valido_s = false;
    }

return;
}