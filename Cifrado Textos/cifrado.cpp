#include <iostream>
#include <string>
#include <limits> // Para manejar límites de entrada
#include <sstream> // Para convertir cadenas a números

using namespace std;

// Minusculas
#define BASE_MINUSCULAS 97
#define MAX_RANGO_MINUSCULAS 122
#define MIN_RANGO_MINUSCULAS 97

// Mayusculas
#define BASE_MAYUSCULAS 65
#define MAX_RANGO_MAYUSCULAS 90
#define MIN_RANGO_MAYUSCULAS 65

// Constantes
const int modulo = 26;

// Capturador de enteros 
int get_int(const string& prompt = "") {
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

void obtenerInputUsuario(int& desplazamiento, string& fraseACifrar){
    // Ingreso de la frase
    cout << "\n" << "Ingrese la frase: ";
    getline(cin, fraseACifrar);

    // Ingreso el desplazamiento 
    desplazamiento = get_int("Ingrese el desplazamiento: ");
}

int caracterModificado(const char& caracter, int& desplazamiento){
    // Vuelve la modificación de los caracteres rotativa
    if (int(caracter) >= MIN_RANGO_MAYUSCULAS && int(caracter) <= MAX_RANGO_MAYUSCULAS) // Si es un caracter mayusq.
    {
        return ((int(caracter) - BASE_MAYUSCULAS + desplazamiento + modulo) % modulo) + BASE_MAYUSCULAS;
    }
    
    return ((int(caracter) - BASE_MINUSCULAS + desplazamiento + modulo) % modulo) + BASE_MINUSCULAS;
    
}

void operacion(string& frace, string& fraceOperada, int desplazamiento){
    // Declaración de variables
    int temporal;

    // Convierto cada caracter a su equivalente ASCII
    for (const char& caracter : frace)
    {
        // Caracteres especiales
        if ((int(caracter) < 65 ) || (int(caracter) > 122 ) || (int(caracter) > 90 && int(caracter) < 97))
        {
            fraceOperada += caracter;
        }
        else
        {
            temporal = caracterModificado(caracter, desplazamiento);
            fraceOperada += char(temporal);
        }
    }
    
    cout << "Su frase es: " << fraceOperada << "\n" << endl;
}

void cifrado(){
    // Declaración de variables
    int desplazamiento;
    string fraseACifrar;
    string fraseCifrada = "";

    // Obtengo la entrada Dezplazamiento/Frase
    obtenerInputUsuario(desplazamiento, fraseACifrar);

    // Realizo las operaciones de cifrado
    operacion(fraseACifrar, fraseCifrada, desplazamiento);
}

void descifrar(){
    // Declaración de variables
    int desplazamiento;
    string fraseADescifrar;
    string fraseDescifrada = "";

    // Obtengo la entrada Desplazamiento/Frase
    obtenerInputUsuario(desplazamiento, fraseADescifrar);

    // Realizo las operaciones de descifrado
    operacion(fraseADescifrar, fraseDescifrada, desplazamiento);
}

void funciones(int opcion){
    // Ingreso a las funciones de usuario
    switch (opcion)
    {
    case 1:
        cifrado();
        break;
    
    case 2:
        descifrar();
        break;

    case 3:
        cout << "\n" << "Que tengas un buen día" << endl;
        break;

    default:
        // Validación de opcion de usuario
        cout << "Opción invalida, por favor ingrese un número entre 1-3" << "\n" << endl;
        break;
    }
}

void menuOpciones(){
    // Declaración de variables
    int opcion;

    do
    {
        // Intrefaz de menú de usuario
        cout << "Ingresa la opción que necesitas" << endl;

        // Opciones de Cifrado/Descifrado
        cout << "1. Cifrado César" << endl;
        cout << "2. Descifrado (Método César)" << endl;
        cout << "3. Salir" << endl;

        // Captura opción del usuario
        opcion = get_int("\nIngrese su opción: ");
        funciones(opcion);

    } while (opcion != 3);
    
}

int main(){
    // Ingreso al menú
    cout << "Bienvenido al cifrador de frases" << endl;
    menuOpciones();

    return 0;
}