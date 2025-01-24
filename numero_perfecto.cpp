#include <iostream>

using namespace std;

bool check_numero(int numero){
    // Suma de los divisores
    int suma_divisores = 0;

    // Calcula los divisores de número
    for (size_t i = 1; i < numero - 1; i++) 
    {
        if (numero % i == 0){
            suma_divisores += i;
        }
    }
    
    if (suma_divisores == numero)
    {
        return true;
    }

    return false;
}

int main() {
    // Declaración de variables
    int numero;

    cout << "Ingrese el número: ";
    cin >> numero;

    if (check_numero(numero))
    {
        cout << "true";
        return 0;
    }

    cout << "false";
    return 1;
}
