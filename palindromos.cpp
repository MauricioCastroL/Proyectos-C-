#include <iostream>
#include <string>
#include <cctype> 

using namespace std;

void verificacion(string palindromo){

    string compare = ""; // String a comparar

    for (int i = palindromo.size() - 1; i >= 0; i--) // Da vuelta el string
    {
        compare += palindromo[i];
    }
    
    if (compare == palindromo)
    {
        cout << "Es un palindromo" << endl;
        return;
    }

    cout << "No es un palindromo" << endl;

}

string convertirMinusculas(string palindromo){
    // Declaración de variables
    string entrada = "";

    // COnvierto cada caracter a minusculas
    for (int i = 0; i < palindromo.size(); i++)
    {
        entrada += tolower(palindromo[i]);
    }

    return entrada;
}

int main(){
    // Declaracion de variables
    string fraseEntrada;
    string palindromo = "";

    cout << "Ingrese la frase: ";
    getline(cin, fraseEntrada);

    if (fraseEntrada.empty())
    {
        cout << "Debe ingresar una frase" << endl;
        return 1;
    }

    // Quitamos los espacios en blanco
    for(int i = 0; i < fraseEntrada.size(); i++) 
    {
        if(fraseEntrada[i] != ' ')
        {
            palindromo += fraseEntrada[i];
        }
    }

    // Convertimos todo a minusculas
    palindromo = convertirMinusculas(palindromo); 

    // Función que verfique si es un palindromo
    verificacion(palindromo); 

    return 0;
}