#include <iostream>
#include <cmath>

using namespace std;

void isPrime();
void generatePrimes();
void mostarPrimes(bool* arr, int len);
void nthTerm();

int main () {
    // Declaración de variables
    int option;

    do
    {
        // Menú de usuario
        cout << "=============================" << endl;
        cout << "Calculadora de Números primos" << endl;
        cout << "=============================" << endl;

        cout << "1. Comprobar si un número es primo" << endl;
        cout << "2. Generar todos los números primos hasta un límite" << endl;
        cout << "3. Calcular el N-ésimo número primo" << endl;
        cout << "4. Salir" << endl;

        // Opción de usuario
        cout << "Ingrese su opción: ";
        cin >> option;

        // Ingreso a las funciones
        switch (option)
        {
            case 1:
                isPrime(); // Comprueba si n es primo 
                break;

            case 2:
                generatePrimes(); // Genera n primos
                break;

            case 3:
                nthTerm(); // Muestra el n-ésimo primo
                break;

            case 4:
                break;

            default:
                cout << "Opción invalida" << endl;
                break;
        }

    } while (option != 4);
    
    return 0;
}


void isPrime()
{
    // Declaración de variables
    int number;
    bool flag = true;

    cout << "Ingrese un número: ";
    cin >> number;

    // Iterador de divisores
    for (size_t i = 2; i < number; i++)
    {
        if (number % i == 0) // Verfica si es primo
        {
            flag = false;
        }
    }
    
    // Muestro los resultados  

    if (flag = true)
    {
        cout << number << " es primo." << endl;
    }
    else {
        cout << number << " no es primo." << endl;
    }

}

void generatePrimes(){
    // Declaración de variables
    int limite;

    cout << "Ingresa el limite: ";
    cin >> limite;

    // Lista repleta de true    
    bool arr[limite + 1];
    fill(arr, arr + limite + 1, true);

    // 0 y 1 no cuentan en el array
    arr[0] = false;
    arr[1] = false;

    // Generador de primos
    for (size_t i = 2; i <= sqrt(limite); i++)
    {
        if (arr[i])
        {
            for (size_t p = i*i; p <= limite; p += i)
            {
                arr[p] = false;
            }
        }
    }

    mostarPrimes(arr, limite); // Muestro los primos
}

void mostarPrimes(bool* arr, int len){
    for (int i = 2; i < len; i++)
    {
        if (arr[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;
}

void nthTerm(){
    // Declaración de variables
    int n_term;

    cout << "Ingresa el valor de N: ";
    cin >> n_term;

    // Validación de entrada
    if (n_term <= 0) {
        cout << "El valor de N debe ser mayor a 0." << endl;
        return;
    }

    // Calcula el límite superior aproximado para el enésimo número primo
    int limite = n_term > 5 ? n_term * log(n_term) + n_term * log(log(n_term)) : 15;

    // Reserva memoria dinámica para el arreglo
    bool* arr = new bool[limite + 1];

    // Inicializa el arreglo en `true`
    fill(arr, arr + limite + 1, true);

    // 0 y 1 no son primos
    arr[0] = false;
    arr[1] = false;

    // Generador de números primos usando el método de la criba de Eratóstenes
    for (int i = 2; i <= sqrt(limite); i++) {
        if (arr[i]) {
            for (int p = i * i; p <= limite; p += i) {
                arr[p] = false;
            }
        }
    }

    // Encuentra el enésimo número primo
    int contador = 0;
    for (int i = 2; i <= limite; i++) {
        if (arr[i]) {
            contador++;
            if (contador == n_term) {
                cout << "El " << n_term << "° número primo es: " << i << endl;
                delete[] arr; // Libera la memoria dinámica
                return;
            }
        }
    }

    // Si no se encuentra el primo (caso improbable)
    cout << "No se pudo encontrar el " << n_term << "° número primo." << endl;

    // Libera la memoria dinámica
    delete[] arr;
}