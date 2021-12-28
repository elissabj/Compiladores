# Compiladores
Ramos_Gomez_Elisa_2015021066 


Aplicación de los conocimientos adquiridos durante el curso de compiladores 2021.

# Proyecto Final 

Es un compilador de señales de audio. 
   A través de este compilador se podrá someter una señal de audio a alguna operación básica disponible. La entrada es el código en formato .txt y una señal de entrada con formato .wav, como salida obtendremos un ploteo (de ambas señales Entrada-Salida) y el archivo de la señal alterada. Se realiza por un lenguaje de programación 
   que decidí llamar "SGN" que contiene las siguientes características: 
   ## Tipos de dato.
   Al momento de hacer el diseño me gustó hacer un lenguaje tipado, por el momento solo acepta dos tipos.
   - "sgn" : es el tipo de dato que se le asigna a la señal de audio.
   - "float": es un flotante que viene siendo el factor por el cual se desea realizar cierta operación.
        
   ## Operaciones.
   Las operaciones disponibles son:
   - "decimate": operación que elimina submuestras de la señal de audio por un factor indicado, este factor tiene que ser ≥ 0. 
   - "interpolate": operación que agrega submuestras a la señal de audio (utilizando el método interpolación a escalón) por una factor indicado, este factor tiene que ser ≥ 0.
   - "amplitude": operación que hace una cierta extensión de la señal, existen la amplificación (factor entero) y la atenuación (factor decimal) por lo que la operación definida en este lenguaje cumple ambas sin ningún problema, el factor tiene que ser ≥ 0.
   - "shift": operación de desplazamiento de la señal hacia la izquierda o derecha, el factor pertenece al conjunto ℝ.
   - "reflect": operación que invierte la señal de audio.

   ## Syntaxis
   Para la declaración de un tipo de dato. 
   
   ```sng [nombreDeVariable] = nombreDelArchivo.wav;```
   
   ```float [nombreDeVariable] = 3.5;```
   
   Para las operaciones.
   
   ```interpolate(nombreDeVariableDeLaSeñal, nombreDeVariableDelFactor);```
   
   ```amplitude(nombreDeVariableDeLaSeñal, nombreDeVariableDelFactor);```
   
   ```decimate(nombreDeVariableDeLaSeñal, nombreDeVariableDelFactor);```
   
   ```shift(nombreDeVariableDeLaSeñal, nombreDeVariableDelFactor);```
   
   ```reflect(nombreDeVariableDeLaSeñal);```
   
  
   
   ## Ejemplo de código 
   Ejemplo de compilación válida.
      
      float          [ fact ]= 4;
      signal [ prueba  ]   =    recordEli.wav   ;
      reflect ( prueba )  ; 
      
      
   Ejemplo de compilación inválida.
      
      
      float          [ fact ]= 4;
      signal [ prueba  ]   =    recordEli.wav   ;
      interpolate ( prueba, factorFloat )  ; 
      
   Algunas recomendaciones para poder apreciar mejor las operaciones son:
   - Para "decimate", factor podría ser de valor 4.
   - Para "amplitude", factor = 110000.
   - Para "interpolate", factor = 3.
   - Para "shift", factor = -40000.
      
   ## Dependencias
   Se desarolló en Python 3 usando las siguientes bibliotecas auxiliares.
   - ply 
   - scipy
   - wavio
   - numpy
   - matplotlib
   - sounddevice

   ## Ejecución del Compilador
   En consola
   
   - <img src="https://raw.githubusercontent.com/FortAwesome/Font-Awesome/master/svgs/brands/windows.svg" alt="windows" width="16" height="16"/>Windows</a> 
         
         python sgn.py
         
   - <img src="https://raw.githubusercontent.com/FortAwesome/Font-Awesome/master/svgs/brands/linux.svg" alt="linux" width="16" height="16"/>Linux</a>
         
         python3 sgn.py

   ## Alcance
   - [ ] Solo acepta señales de audio en formato ".wav".
   - [ ] El código se tiene que sobreescribir en el archivo "codigo.txt".
   - [ ] Para mejor rendimiento se recomienda aplicarlo en señales de audio con duración no mayor a 10 s.
   - [ ] Para algún nombre de las variables solo se aceptan nombres que contengan minúsculas y mayúsculas.
   - [ ] En el código no puede existir más de una operación definida, solo acepta una operación por compilación.
   - [ ] Al momento de usar la operación "reflect" es necesario hacer la declaración de los dos tipos de dato disponibles.

# Practicas 
Se desarrollaron todas las prácticas en C++. 
- Se realizaron dos ejemplos de un analizador sintáctico por descenso recursivo, con las gramáticas vistas en clase.
- Algoritmo LL(1), para su uso se necesitan indicar 
   a) El número de No Terminales y definir cuales son separados por espacio.
   b) El número de Terminales y definir cuales son separados por espacio.
   c) El número de Producciones y definir cuales son separados por enter.
   d) Para el uso de épsilon utilizamos el caracter #.
   
   Ejemplo
   Entrada:
   
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
         ((id+id*id)+id
         
    La salida será la Tabla Final del algoritmo y si la cadena es correcta o incorrecta.
    Salida: 
    
         La tabla final es:
         E,1: ( id
         E',2: +
         E',3: $ )
         F,7: (
         F,8: id
         T,4: ( id
         T',5: *
         T',6: $ ) +
         
         cadena invalida
         
 - Algoritmo LR(0), para su uso se necesitan indicar, aun falta validar la cadena, se piensa desarrollar en los proximos meses
   a) Las producciones de la gramática.    
   Ejemplo
   Entrada:
    
         E->TE'
         E'->+TE'
         E'->#
         T->FT'
         T'->*FT'
         T'->#
         F->(E)
         F->id
         
         
     
    
