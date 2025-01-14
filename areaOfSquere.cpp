#include <iostream>
#include <cmath>

using namespace std;

int calculoArea(int lado);

int main(){
    // Declaración de variables
    int lado;
    int area;

    cout << "Ingrese un lado del cuadrado: ";
    cin >> lado; // Largo de entrada del cuadrado

    area = calculoArea(lado); 

    cout << "El area de un cuadrado es de: " << area; // Muestra del área

    return 0;
}

// Función que calcule el área del cuadrado
int calculoArea(int lado){ 

    int area;

    area = pow(lado, 2); // Calculo del area

    return area;
}