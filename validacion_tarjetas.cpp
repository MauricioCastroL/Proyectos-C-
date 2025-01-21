#include <iostream>
#include <string>

using namespace std;

string procesar_numeros(string numeros_tarjeta);
int duplicar_numeros(string numeros_tarjeta);

int main() {

    string numeros_tarjeta; 

    cout << "Ingrese los números de la tarjeta: ";
    getline(cin, numeros_tarjeta);

    numeros_tarjeta = procesar_numeros(numeros_tarjeta);
    int number = duplicar_numeros(numeros_tarjeta);

    if (number % 10 == 0){
        cout << "La tarjeta es valida";
    }else{
        cout << "La tarjeta es invalida";
    }

    return 0;
}

string procesar_numeros(string numeros_tarjeta){
    string number = "";

    for (int i = size(numeros_tarjeta) - 1; i >= 0; i--){
        if (numeros_tarjeta[i] != ' '){
            number += numeros_tarjeta[i];
        }
    }

    return number;
}

int duplicar_numeros(string numeros_tarjeta){
    string number = "";
    int num = 0;

    for (int i = 0; i < size(numeros_tarjeta); i++){
        if (i == 0){
            number += numeros_tarjeta[i];
        }
        else if (i > 0 && i % 2 != 0){
            int int_number = numeros_tarjeta[i] - '0';
            int_number *= 2;
            if (int_number > 9){
                int_number -= 9;
                char str_number = int_number + '0';
                number += str_number;
            }
            else {
                char str_number = int_number + '0';
                number += str_number;
            }
        }
        else if (i > 0 && i % 2 == 0){
            number += numeros_tarjeta[i];
        }
    }

    for (int i = 0; i < number.length(); i++){
        int n = number[i] - '0';
        num += n;
    }

    return num;
}
