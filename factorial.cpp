#include <iostream>

using namespace std;

long double calculateFactorial(int numero){

    long double factorial = 1;

    for (long double i = 1; i <= numero; i++){ // Calculo del factorial
        factorial *= i;        
    }

    return factorial;
}


int main(){
    // Declaracion de variables de tipo entero para el resultado
    int numero; 
    long double factorial;

    cout << "Programa que calcule el factorial de un número\n";

    // Ingreso de la entrada del usuario
    do{
        cout << "Ingrese el valor del factorial: ";
        cin >> numero;
    }
    while(numero < 0);

    // Determino de caso base y calculo del factorial
    if ( numero == 0){ // Si el numero es 0
        factorial = 1;
    }
    else{
        factorial = calculateFactorial(numero);
    }

    cout << "El factorial de " << numero << "! es: " << factorial; // Muestro el resultado

    return 0;
}