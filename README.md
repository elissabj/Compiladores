# Compiladores2021B
Ramos_Gomez_Elisa_2015021066 


Aplicación de los conocimientos adquiridos durante el curso de compiladores 2021.

# Proyecto Final 

Es un compilador de señales de audio. 
   A través de este compilador se podrá someter una señal de audio a alguna operación básica disponible. Se realiza por un lenguaje de programación 
   que decidí llamar "sgn" que contiene las siguientes características: 
   ## Tipos de dato.
   Al momento de hacer el diseño me gustó hacer un lenguaje tipado, por el momento solo acepta dos tipos.
   - "sgn" : es el tipo de dato que se le asigna a la señal de audio.
   - "float": es un flotante que viene siendo el factor por el cual se desea realizar cierta operación.
        
   ## Operaciones.
   Las operaciones disponibles son:
   - "decimate": operación que elimina submuestras de la señal de audio por un factor indicado, este factor tiene que ser ≥ 0. 
   - "interpoalte": operación que agrega submuestras a la señal de audio (utilizando el método interpolación a escalón) por una factor indicado, este factor tiene que ser ≥ 0.
   - "amplitude": operación que hace una cierta extensión de la señal, existen la amplificación (factor entero) y la atenuación (factor puede ser decimal) por lo que la operación definida en este lenguaje cumple ambas sin ningún problema. 
   - "shift": operación de desplazamiento de la señal hacia la izquierda o derecha, el factor puede ir de -∞ a ∞.
   - "reflect": operación que invierte la señal de audio.
   
        
     
     
    
