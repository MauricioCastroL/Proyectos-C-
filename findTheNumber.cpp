#include <iostream>
#include <ctime>

using namespace std;

int main(){
    // Declaracion de variables
    int number;
    int trys = 0;
    int inputNumber;

    srand(time(NULL)); // Semilla de números aleatorios 

    number = rand() % 100 + 1; // Número aleatorio desde el (1-100)

    do {
        cout << "Ingrese un número: ";
        cin >> inputNumber;

        if (inputNumber < number){
            cout << "Frio\n";
            trys ++;
        }
        else if (inputNumber > number){
            cout << "Caliente\n";
            trys ++;
        }
    }
    while (inputNumber != number);
    
    trys++;
    cout << "Felicidades encontraste el número! \n";
    cout << "Número de intentos: " << trys;

    return 0;
}
