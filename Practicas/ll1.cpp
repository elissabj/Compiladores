#include<iostream>
#include<vector>
#include<list>
#include<set>
#include<map>

using namespace std;

set<string>Terminal;
pair<string,int> simboloInicial; 
map <pair<string,int>, set<string> > tablaFinal;
map <pair<string,int>, vector<string> > gramatica;
map<string, vector<int> > produccionesCorrespondientes;


void iniciaProceso(void);
void lecturaProd (int &NP);
void imprimeTablaFinal(void);
void lectura (int &NT, int &T, int &NP);
void iniciaAceptacionDeCadena (string &cadena);
void primero(vector<string> producciones, vector<string> & auxiliarFinal, int idx);
void siguiente(string &produccionAProcesar, vector<string> & auxiliarFinal, int idx);

bool esAceptada(vector<string> &cadena);
bool esEpsilon (string &defineTipoProduccion);
bool esTerminal (string &defineTipoProduccion);
bool hayCiclo(pair<string,int> &parte_izq, string produccionAProcesar);

int tipoRegla(pair<string, int> &produccionActual, string &produccionAProcesar );
vector< pair <string, int> > buscarProducciones(string & produccionABuscar);
vector< pair <string, int> > produccionesPosibles(string & produccionABuscar, string & str);


int main(){
  
  int no_terminales, terminales, no_produccion;
  lectura(no_terminales, terminales, no_produccion);
  
  lecturaProd(no_produccion);
  iniciaProceso();
  imprimeTablaFinal();
  
  string cadena;
  iniciaAceptacionDeCadena(cadena);

return 0;
}

void lectura (int &NT, int &T, int &NP){

  string aux;
    
  cout <<"Ingresa # de No Terminales\n";
  
  cin >> NT;     
  for (int i = 0; i < NT; i++){
    cin >> aux;
  }

  cout <<"Ingresa # de Terminales\n";
  
  cin >> T;
  for (int i = 0; i < T; i++){
    cin >> aux;
    Terminal.insert(aux);
  }

  aux = "$";
  Terminal.insert(aux);
  
  cout <<"Ingresa # de Producciones con formato NT -> NT T # \n";
  cin >> NP;

return;
}

void lecturaProd (int &NP ){
    
  cin.ignore();
  string produccion;
  string parte_izq = "";
  string parte_der = "";
    
  for(int i = 0; i < NP; i++){
        
    getline(cin, produccion);
    bool esPrimeraParte = true;
   	
   	vector<string> reglas_gramaticales;

    for (int j = 0; j < produccion.size(); j++){

      if(produccion[j] == '-' && produccion[j+1] == '>'){
        esPrimeraParte = false; j+=2;
      }
          
      if(esPrimeraParte){
        if(produccion[j] !=' '){
          parte_izq += produccion[j];
        }
      }
         
      if(!esPrimeraParte){
       	if(produccion[j] != ' '){
          parte_der += produccion[j];
        }else{
          if(!parte_der.empty()){
            reglas_gramaticales.push_back(parte_der);
          }
          parte_der = "";
        }
      }

    }
        
    reglas_gramaticales.push_back(parte_der);
    gramatica[ {parte_izq, i+1} ] = reglas_gramaticales;
    produccionesCorrespondientes[parte_izq].push_back(i+1);
    if(i == 0){
      simboloInicial.first = parte_izq;
      simboloInicial.second = i+1;
    }

    parte_der = "";
    parte_izq = "";
  
  }

return;
}


bool esTerminal (string &defineTipoProduccion){
  return Terminal.count(defineTipoProduccion);
}

bool esEpsilon (string &defineTipoProduccion){
  return (defineTipoProduccion == "#") ?  true: false; 
}

void iniciaProceso(void){
  
  for(auto it_produccion: gramatica){
    
    vector<string> auxiliarFinal;
    set<string> transcision;

    if(it_produccion.second[0] == "#"){
      string produccion = it_produccion.first.first;
    	siguiente(produccion, auxiliarFinal, 0);
    }else{
    	primero(it_produccion.second, auxiliarFinal, 0);
    }
    
    
    for(string produccion : auxiliarFinal){
      transcision.insert(produccion);
    }

    tablaFinal[{it_produccion.first.first, it_produccion.first.second}] = transcision;
  }

return;
}

void primero(vector<string> producciones, vector<string> & auxiliarFinal, int idx){

  if(esTerminal(producciones[idx]) ){
    auxiliarFinal.push_back(producciones[idx]);
  }else{
    for(int i = 0; i < produccionesCorrespondientes[ producciones[idx] ].size(); i++){
      int num_prod = produccionesCorrespondientes[ producciones[idx] ] [i];
      primero( gramatica[{producciones[idx], num_prod}], auxiliarFinal, 0);
    }
  }

return; 
}

vector< pair <string, int> > buscarProducciones(string & produccionABuscar){
  
  vector< pair <string, int> > produccionesEncontradas;

  for(auto it: gramatica){
  	for(string aparece: it.second){
      if(aparece == produccionABuscar){
      	produccionesEncontradas.push_back(it.first);
      }
    }
  }
  
  return produccionesEncontradas;
}

int tipoRegla(pair<string, int> &produccionActual, string &produccionAProcesar ){
  
  if(produccionActual.second == simboloInicial.second){
  	return 1;
  }
  
  auto prod_der = gramatica[produccionActual];
  if(prod_der[prod_der.size()-1] == produccionAProcesar){
  	return 3;
  }
  
return 2; 
}

bool hayCiclo(pair<string,int> &parte_izq, string produccionAProcesar){
  vector<string> parte_der = gramatica[ parte_izq ];
  for(string it_gramatica: parte_der){
    if (it_gramatica == parte_izq.first){
      return true;
    }
  }
return  false;
}                                
  

void siguiente(string &produccionAProcesar, vector<string> & auxiliarFinal, int idx){
  vector< pair <string, int> > produccionesEncontradas = buscarProducciones(produccionAProcesar);
   for(auto produccionActual : produccionesEncontradas ){
    	if(tipoRegla(produccionActual, produccionAProcesar) == 1){
        auxiliarFinal.push_back("$");  
      }

     if (tipoRegla(produccionActual, produccionAProcesar) == 2){
        
        auto reglas_derecha = gramatica[produccionActual];
        vector<string> nuevosPrimeros;

        bool siguientePrimero = false;
        for(string posibleProduccion: reglas_derecha){
          if(posibleProduccion == produccionAProcesar){
            siguientePrimero = true; continue;
          }
          if (siguientePrimero){
            nuevosPrimeros.push_back(posibleProduccion);
          }
        } 
      	primero( nuevosPrimeros, auxiliarFinal, idx);
      }else{
       	if(hayCiclo(produccionActual, produccionAProcesar)){
        	return;
        }else{
          siguiente(produccionActual.first, auxiliarFinal, idx);
        }
      }
   
   }
return;
}

void imprimeTablaFinal(void){

  cout << "La tabla final es: \n";

  for(auto x: tablaFinal){
    auto pair = x.first;
    cout << pair.first <<","<<pair.second <<": ";
    for(auto y: x.second){
      cout << y << " ";
    }
    cout <<"\n\n";
  }

return;
}

void iniciaAceptacionDeCadena (string &cadena){

  cout << "Ingresa la cadena a procesar\n";
  cin >> cadena;

  vector<string>cad; 
  string aux = ""; 

  for(int i = 0; i  < cadena.size(); i++){
    aux += cadena[i];
    if(Terminal.count(aux)){
      cad.push_back(aux);
      aux = "";
    }
  }

  (esAceptada(cad)) ? cout <<"cadena valida\n":cout<<"cadena invalida\n";

return;
}

vector< pair <string, int> > produccionesPosibles(string & produccionABuscar, string & str){
  
  vector< pair <string, int> > produccionesEncontradas;
  for(auto it: gramatica){
      if(it.first.first == produccionABuscar){
        if(tablaFinal[it.first].count(str)){
          produccionesEncontradas.push_back(it.first);
        }
      }
  }
  
  return produccionesEncontradas;
}

bool esAceptada(vector<string> &cadena){

  string delimitador = "$";
  cadena.push_back(delimitador);

  list<string>verifica;
  verifica.push_back(delimitador);

  for(auto x: tablaFinal){
      auto pair = x.first;
      if(pair.second == 1){
        verifica.push_front(pair.first); break;
      }
        
  }

  bool tuvoTrans = true;
  string aux = "";
  int i = 0;

  while(!verifica.empty()){

    aux = cadena[i];
    if(verifica.front() == "#"){
      verifica.pop_front();
    }
    
    if(verifica.front() == aux){
      i++; verifica.pop_front();      
    }else{
      //consulta
      int num = 1;
      auto prod_posible = produccionesPosibles(verifica.front(), aux);
      if(prod_posible.size() == 0) {return false;}
      for(auto it: prod_posible){
        //tiene transicion
        if(tablaFinal[it].count(aux)){
          vector <string> conjunto = gramatica[it];
          verifica.pop_front();
          for(int j = conjunto.size()-1; j >= 0; j--){
            verifica.push_front(conjunto[j]);
          }
        }
      }
    }
  }

return true;
}

/*
Ejemplos de entrada para probar el algoritmo

5
E E' T T' F
5
+ * ( ) id
8
E -> T E'
E' -> + T E'
E' -> #
T -> F T'
T' -> * F T'
T' -> #
F -> ( E )
F -> id

Cadena: 
      ( id )
      id + * id 
      (id+id)*id
      ((id+id*id)+id

Salida de la tabla: 
E, 1  = ( id
E', 2 = +
E', 3 = $ )
F, 7  = (
F, 8  = id
T, 4  = ( id
T', 5 = *
T', 6 = $ ) +

Resultado de Cadena: 
      cadena valida
      cadena invalida
      cadena valida
      cadena invalida


*************************
2
A Q'
2
a b
4
Q' -> a A Q'
Q' -> b
A -> a
A -> b Q' A

Salida de la tabla:
A, 3 = a
A, 4 = b
Q', 1 = a
Q', 2 = b

Cadena: 
  aab 
  abbab
  baaba


Resultado de Cadena:
  cadena valida
  cadena valida
  cadena invalida

*/