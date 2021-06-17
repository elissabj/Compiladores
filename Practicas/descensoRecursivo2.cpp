/*
Tema: Analisis Sintactico por descenso recursivo
Ejercicio: 
    S -> a b S A
    S -> b A
    A -> a A
    A -> c

Entrada: 
    cadena
Salida:
    mensaje de aceptacion o error
*/
#include<iostream>
using namespace std;

bool otraS;
bool otraA;
bool consume (const string &palabra, int &pos, char tipoProd);
void produccionS (const string &palabra, int &pos, bool &valido_s);
void produccionA (const string &palabra, int &pos, bool &valido_s);

int main(){

    otraS = false;
    otraA = false;

    int pos = 0;
    bool valido_s = true;

    string palabra;
    cin >> palabra;    

    produccionS(palabra, pos, valido_s);
    (valido_s)? cout <<"Valido\n":cout <<"Error\n";

return 0; 
}

bool consume (const string &palabra, int &pos, char tipoProd){

    bool canConsume = true;

    if(tipoProd == 'S'){
        if(palabra[pos] == 'a' && palabra[pos+1] == 'b'){
            otraS = true;
            pos+= 2;
        }else if (palabra[pos] == 'b'){
            otraS = false;
            pos++;
        }else{
            canConsume = false;
        }
    }

    if(tipoProd == 'A'){
        if(palabra[pos] == 'a'){
            otraA = true;
            pos++;
        }else if(palabra[pos] == 'c'){
            otraA = false;
        }else{
            canConsume = false;
        }
    }

return canConsume;
}

void produccionS (const string &palabra, int &pos, bool &valido_s){
    char tipoProd = 'S';
    if(consume(palabra, pos, tipoProd)){
        if(otraS){
            produccionS(palabra,pos, valido_s);
        }else{
            produccionA(palabra,pos, valido_s);
        }
    }else{
        valido_s = false;
    }

return;
}

void produccionA (const string &palabra, int &pos, bool &valido_s){
    char tipoProd = 'A';
    if(consume(palabra, pos, tipoProd)){
        if(otraA){
            produccionA(palabra,pos, valido_s);
        }
    }else{
        valido_s = false;
    }

return;
}