#include <iostream>
#include <vector>
#include <string>
#include <limits> 
#include <sstream> 
#include <random>
#include <chrono>
#include <thread>

using namespace std;

// Declaración de variables globales
int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1}; // Desplazamiento en x
int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1}; // Desplazamiento en y

int get_int(const string& prompt = "") // Captura de enteros 
{
    string input;
    int number;

    while (true) {
        cout << prompt;
        getline(cin, input); // Leer entrada como cadena

        stringstream ss(input); 
        if (ss >> number && ss.eof()) { 
            return number; // Entrada válida, regresar el número
        }

        cout << "Entrada inválida. Por favor, ingrese un número entero válido." << endl;

        cin.clear();
    }
}

int saludo_inicial(){
    int tamano_tablero; // Tamaño del tablero nxn
    do // Saludo y captura del tamaño del tablero 
    {
        cout << "Bienvenido al juego de la vida\n"; // Bienvenida
        tamano_tablero = get_int("Ingrese el tamaño del tablero, mayor a 15: "); // Captura de datos 

        // Validación de entrada
        if (tamano_tablero < 15)
        {
            cout << "Ingrese un número mayor o igual a 15!" << endl;
        }
        
    } while (tamano_tablero < 15);
    
    return tamano_tablero; // Retorno del tamaño del tablero
}

void mostrar_tablero(vector <vector <string>>& tablero){
    // Imprimir el tablero para ver el resultado
    cout << endl;
    for (const auto& fila : tablero) {
        for (const auto& celda : fila) {
            cout << celda << " ";
        }
        cout << endl;
    }
}

void generador_tablero_inicial(int tamano_tablero, vector <vector <string>>& tablero){
    vector <string> simbolos = {"#", "."}; // Simbolos del tablero vida/muerte

    random_device rd;  // Generador de hardware (aleatoriedad real)
    mt19937 gen(rd()); // Motor de números pseudoaleatorios (Mersenne Twister)
    uniform_int_distribution<int> dist(0, 1); // Rango [0, 1]

    // Ciclos iterativos que generen aleatoriamente el tablero 
    for (int i = 0; i < tamano_tablero; i++)
    {
        for (int j = 0; j < tamano_tablero; j++)
        {
            tablero[i][j] = simbolos[dist(gen)]; // Rellena con los simbolos
        }
    }
}

void actualizar_tablero(vector <vector <string>>& tablero, int tamano_tablero){
    vector <vector <string>> temporal = tablero; // tablero temporal

    for (int x = 0; x < tamano_tablero; x++)
    {
        for (int y = 0; y < tamano_tablero; y++)
        {
            // Contador
            int vivos = 0;

            for (int k = 0; k < 8; k++) // Recorre los desplazamientos 
            {
                int nx = x + dx[k]; // Desplazamientos por x
                int ny = y + dy[k]; // Desplazamiento por y

                if ((nx >= 0 && nx < tamano_tablero) && (ny >= 0 && ny < tamano_tablero)) // Dentro del rango 
                {

                    if (tablero[nx][ny] == "#")
                    {
                        vivos++;
                    }
                }
            }
            // Condicionales 
            if ((tablero[x][y] == "#" && (vivos < 2 || vivos > 3))) // Muere por sobrepoblación o por aislamiento
            {
                temporal[x][y] = ".";
            }
            if (tablero[x][y] == "." && vivos == 3) // Nacimiento
            {
                temporal[x][y] = "#";
            }
        }    
    }
    tablero = temporal; // actualizo el tablero original 
}

void inicio_juego(int tamano_tablero){
    vector <vector <string>> tablero(tamano_tablero, vector<string>(tamano_tablero)); // Iniciador del tablero
    generador_tablero_inicial(tamano_tablero, tablero);

    while (true)
    {
        mostrar_tablero(tablero);
        actualizar_tablero(tablero, tamano_tablero); // Actualizo el tablero
        this_thread::sleep_for(std::chrono::seconds(2)); // Espera dos segs.
    }
}

int main(){
    int tamano_tablero = saludo_inicial();
    inicio_juego(tamano_tablero);
    return 0;
}