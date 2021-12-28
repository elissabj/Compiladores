#include <map>
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

typedef map<char, vector< string>> GramaticaAumentada;
typedef map<string, int>TablaIrA;

struct ProduccionAumentada{
    char ladoIzquierdo;
    string ladoDerecho; 

    ProduccionAumentada(char ladoIzq, string ladoDer): ladoIzquierdo(ladoIzq), ladoDerecho(ladoDer){}
};

class LR0{

    private:

    vector<ProduccionAumentada*>producciones;           //Lista de Producciones

    public: 

    LR0(){}

    map<char,int> ir_A;

    void inserta(ProduccionAumentada *prod){
        producciones.push_back(prod);
    }

    int tam(){
        return int(producciones.size());
    }

    bool existeProduccion (string prod){

        for(auto it: producciones){
            
            string existente = string(&it->ladoIzquierdo, 1) + "->" + it->ladoDerecho;     //Genero todas las producciones existentes
            
            if(prod == existente){                                                              //Verifico si son iguales entonces ya lo tengo 
                return true;
            }
        }

        return false;
    }

    ProduccionAumentada* operator[](const int idx){                                             //Sobrecargo del operador [] para conocer la produccion
        return producciones[idx];
    }
};


void cerradura (char simbolo, LR0& item, GramaticaAumentada& gramatica){

    if(!isupper(simbolo)){      //Para No Terminal
        return;
    }

    string actualLadoIzq = string(&simbolo, 1);         //Para Termianl 

    for(int i = 0; i < gramatica[simbolo].size(); i++){
        string actualLadoDer = "." + gramatica[simbolo][i];

        if(!item.existeProduccion(actualLadoIzq + "->" + actualLadoDer)){       //Si no esta en el conjunto 
            item.inserta(new ProduccionAumentada(simbolo, actualLadoDer));      //Agregalo al conjunto
        }

    }


} 


void moverLR0 (vector<LR0>& elementosLR, GramaticaAumentada& gramatica, int& id, TablaIrA& irA){

    cout << "Estado" << id <<":\n"; //Estado actual a procesar

    for(int i = 0; i < elementosLR[id].tam(); i++){     //Para todos los simbolos hacer operacion Cerradura y Mover

        string ladoDer = elementosLR[id][i]->ladoDerecho;
        char simbolo = ladoDer[ladoDer.find('.')+1];
        cerradura(simbolo, elementosLR[id], gramatica);

    }

    string ladoDer;
    int siguientePos; 
    char simbolo, ladoIzq;
    ProduccionAumentada *produccion;

    for(int i = 0; i < elementosLR[id].tam(); i++){         

        ladoIzq = elementosLR[id][i]->ladoIzquierdo;
        ladoDer = elementosLR[id][i]->ladoDerecho;

        string produccionActual = string(&ladoIzq, 1) + "->" + ladoDer;
        simbolo = ladoDer[ladoDer.find('.')+1];

        if(simbolo == '\0'){                            //Si existe la produccion, sigue
            cout << &produccionActual[0] <<"\n";
            continue;
        }
        
        //Si no tiene un ir_A entonces, asignarle uno
        if(elementosLR[id].ir_A.find(simbolo) == elementosLR[id].ir_A.end()){

            if(irA.find(produccionActual) == irA.end()){    //Si no hay entonces crear uno nuevo y asignarlo 
                
                elementosLR.push_back(LR0());
                string nuevaDer = ladoDer;
                int aPos = nuevaDer.find('.');
                swap(nuevaDer[aPos], nuevaDer[aPos+1]);
                elementosLR.back().inserta(new ProduccionAumentada(ladoIzq, ladoDer));
                
                elementosLR[id].ir_A[simbolo] = elementosLR.size()-1;
                irA[produccionActual] = produccionActual.size()-1;


            }else{  //usamos la transicion existente
                elementosLR[id].ir_A[simbolo] = irA[produccionActual];
            }

            cout << &produccionActual[0] << " Ir ("  << simbolo <<") Estado = " <<irA[produccionActual] <<"\n";

        }else{

            int at = ladoDer.find('.');
            swap(ladoDer[at], ladoDer[at+1]);

            int siguienteElemento = elementosLR[id].ir_A[simbolo];

            if(!elementosLR[siguienteElemento].existeProduccion(string(&ladoIzq, 1) + "->" + ladoDer)){
                elementosLR[siguienteElemento].inserta( new ProduccionAumentada(ladoIzq, ladoDer));
            }

            swap(ladoDer[at], ladoDer[at+1]);
            cout << &produccionActual[0] <<"\n";

        }


    }


}

void leerEntrada (vector<LR0>& elementosLR, GramaticaAumentada& gramatica){

    string prod, ladoIzq, ladoDer;
    char delimitador[] = "->";
    int numProducciones;


    cin >> numProducciones;
    cin.ignore();

    for(int i = 0; i < numProducciones; i++){

        getline(cin, prod);
        if(i == 0){                                 //extiendo la gramatica
            gramatica['\''].push_back(prod);
            elementosLR[0].inserta(new ProduccionAumentada('\'', '.' + prod));
        }else{

            ladoIzq = strtok(&prod[0], delimitador);
            ladoDer = strtok(NULL, delimitador);

            gramatica[ladoIzq[0]].push_back(ladoDer);
            cout << ladoIzq.c_str() <<"->"<< ladoDer.c_str() <<"\n";

            elementosLR[0].inserta(new ProduccionAumentada(ladoIzq[0], "."+ladoDer));

        }
    }

return;
}


int main(){

    TablaIrA irA;
    GramaticaAumentada gramatica;
    vector<LR0> elementosLR = {LR0()};

    leerEntrada(elementosLR, gramatica);

    cout << "Tabla final LR(0)\n";
    for(int it = -1; it < int(elementosLR.size()); it++){
        moverLR0(elementosLR, gramatica, it, irA);
    }

    return 0;
}