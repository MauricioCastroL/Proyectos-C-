#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <set>

using namespace std;

// Divide cadenas (split)
vector<string> split(const string& str, char delimiter) {
    
    vector<string> tokens;
    string token;
    stringstream ss(str);

    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

// Elimina espacios al inicio (lstrip)
string lstrip(const string& str) {
    string result = str;
    result.erase(result.begin(),
                find_if(result.begin(), result.end(),
                              [](unsigned char ch) { return !isspace(ch); }));
    return result;
}

// Elimina espacios al final (rstrip)
string rstrip(const string& str) {
    string result = str;
    result.erase(find_if(result.rbegin(), result.rend(),
                              [](unsigned char ch) { return !isspace(ch); }).base(),
                 result.end());
    return result;
}

// Elimina espacios en ambos extremos (strip)
string strip(const string& str) {
    return lstrip(rstrip(str));
}

void lectura(set <string> &lista){
    // Apertura del archivo
    ifstream archivo("archivo.txt");

    if (!archivo.is_open()) // Validación de apertura
    {
        cout << "Archivo no abierto" << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) // Lectura linea por Linea
    {
        vector <string> token = split(linea, ','); // Separado por (,)

        for (string elemento : token) 
        {
            lista.insert(strip(elemento)); // Agrega a la lista cada elemento
        }
    }
    
    archivo.close(); // Cierre del archivo

}

int main(){
    // Declaración de variables
    set <string> lista;

    lectura(lista);

    cout << "Palabras únicas encontradas:" << endl;

    for (string element : lista) // Salida 
    {
        cout << element << endl;
    }

    cout << "Total palabras únicas: " << lista.size() << endl;

    return 0;
}