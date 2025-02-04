#include <iostream>
#include <string>
#include <limits> // Para manejar límites de entrada
#include <sstream> // Para convertir cadenas a números
#include <vector> 
#include <map>
#include <random>
#include <utility>
#include <set>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <chrono> // Mamejo del tiempo
#include <ctime>
#include <iomanip>

#define CANTIDAD_BOMBAS_EXPERTO 50
#define CANTIDAD_BOMBAS_INTERMEDIO 17
#define CANTIDAD_BOMBAS_FACIL 8

using namespace std;
using namespace std::chrono;

bool ganador = true; // Global verificador

void imprimirTablero(vector<vector<string>>& tablero, vector<int>& tamanoYCantidadBombas, vector<vector<string>> tableroGame, string& usuario, time_t tiempoInicial);
void puntuaciones(string& usuario, int tiempoJugador = 0);

// Movimiento en x
vector <int> dx = {-1, -1, -1, 0, 0, 1, 1, 1};
// Movimiento en y
vector <int> dy = {-1, 0, 1, -1, 1, -1, 0, 1};

// Configuraciones de DIFICULTAD/BOMBAS/TAMAÑO CUADRICULA
map <int, vector <int>> configuracionJuego = {
    //DIFICULTAD,CANT.BOMBAS,TAMAÑO TABLERO
    {1, {CANTIDAD_BOMBAS_EXPERTO, 26}}, 
    {2, {CANTIDAD_BOMBAS_INTERMEDIO, 14}}, 
    {3, {CANTIDAD_BOMBAS_FACIL, 6}}
};

string lstrip(const string& str){
    // Elimina espacios al inicio (lstrip)
    string result = str;
    result.erase(result.begin(),
                find_if(result.begin(), result.end(),
                              [](unsigned char ch) { return !isspace(ch); }));
    return result;
}

string rstrip(const string& str){
    // Elimina espacios al final (rstrip)
    string result = str;
    result.erase(find_if(result.rbegin(), result.rend(),
                              [](unsigned char ch) { return !isspace(ch); }).base(),
                 result.end());
    return result;
}

string strip(const string& str){
    // Elimina espacios en ambos extremos (strip)
    return lstrip(rstrip(str));
}

int get_int(const string& prompt = "") {
    // Obtiene solo enteros
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

bool isGanador(vector<vector<string>>& tablero, vector<vector<string>>& tableroGame, string& usuario, std::time_t tiempoInicial){
    /*Recorriendo todo el tablero verificamos si todo fue 
    descubierto, lo cual proboca que haya ganado o no */
    int n = tablero.size();

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < n; j++)
        {
            if (tableroGame[i][j] != "B" && tablero[i][j] == "#") 
            {
                return true;
            }
        }
    }

    auto final = std::chrono::system_clock::now();
    std::time_t tiempoFinal = std::chrono::system_clock::to_time_t(final);

    // Calcular duración
    int segundosTotales = static_cast<int>(difftime(tiempoFinal, tiempoInicial));
    int horas = segundosTotales / 3600;
    int minutos = (segundosTotales % 3600) / 60;
    int segundos = segundosTotales % 60;

    cout << "\n¡Felicidades " << usuario << "! Has ganado. Tiempo: " 
         << horas << ":" << minutos << ":" << segundos << endl;
    
    puntuaciones(usuario, segundosTotales);
    return false;
}

void actualizarTablero(vector<vector<string>>& tablero, vector<vector<string>>& tableroGame, int x, int y, vector <int>& tamanoYCantidadBombas, string& usuario, std::time_t tiempoInicial){
    int tamanoTablero = tamanoYCantidadBombas[1]; // Tamaño correcto de la cuadrícula (índice 1)

    // Verificar si la celda está fuera de límites o ya revelada
    if (x < 0 || x >= tamanoTablero || y < 0 || y >= tamanoTablero || tablero[x][y] != "#") {
        return;
    }

    // Revelar la celda actual
    tablero[x][y] = tableroGame[x][y];

    // Si la celda es "0", revelar recursivamente las adyacentes
    if (tableroGame[x][y] == "0") {
        for (int k = 0; k < 8; k++) {
            int nuevoX = x + dx[k];
            int nuevoY = y + dy[k];
            actualizarTablero(tablero, tableroGame, nuevoX, nuevoY, tamanoYCantidadBombas, usuario, tiempoInicial);
        }
    }

    // Verifica si el usuario gano
    ganador = isGanador(tablero, tableroGame, usuario, tiempoInicial);
}

void intToString(int& bombasCercanas, string& bombasAdyacentes){
    bombasAdyacentes = to_string(bombasCercanas);
}

bool nombreUsuario(string& usuario){
    // Ingreso del nombre del usuario 
    do
    {
        cout << "Bienvenido, Ingresa tu nombre para comenzar: ";
        getline(cin, usuario); // Captura del nombre

        if (usuario.empty()) // No se ingresa un nombre
        {
            cout << "\n" << "Debe ingresar un nombre!" << "\n" << endl;
        }else
        {
            return true; // Se ingresa un nombre
        }
    } while (true);
}

void convertirJugadaCoordenadas(string& jugada, vector <char>& myVectorJugada){
    // ACCION/X-COORDENADA/Y-COORDENADA
    for (int i = 0; i < jugada.size(); i++)
    {
        myVectorJugada.push_back(jugada[i]);
    }
}

void checkJugada(string& jugada, vector<vector<string>>& tablero, vector <int>& tamanoYCantidadBombas, vector<vector<string>>& tableroGame, string& usuario, std::time_t tiempoInicial){
    // Vector con las indicaciones de la jugada
    vector <char> myVectorJugada; // ACCION/X-COORDENADA/Y-COORDENADA
    convertirJugadaCoordenadas(jugada, myVectorJugada);
    // Coordenadas
    int x = myVectorJugada[1] - 'A';
    int y = myVectorJugada[2] - 'A';

    if (tablero[x][y] == "F" && myVectorJugada[0] == 'A') // No permite este movimiento 
    {
        cout << "\n" << "Debe quitar primero la bandera intente F()()" << "\n" << endl;
    }
    else if (tablero[x][y] == "#" && myVectorJugada[0] == 'F') // Aplicar Bandera
    {
        tablero[x][y] = "F";
        tamanoYCantidadBombas[0]--;
    }
    else if (tablero[x][y] == "F" && myVectorJugada[0] == 'F') // Quitar bandera
    {
        tablero[x][y] = "#";
        tamanoYCantidadBombas[0]++;
    }
    else if (tableroGame[x][y] == "B" && myVectorJugada[0] == 'A') // Cae en una bomba
    {
        // Obtener el tiempo de finalización
        auto final = std::chrono::system_clock::now();
        std::time_t tiempoFinal = std::chrono::system_clock::to_time_t(final);
        
        // Calcular duración
        int segundosTotales = static_cast<int>(difftime(tiempoFinal, tiempoInicial));
        int horas = segundosTotales / 3600;
        int minutos = (segundosTotales % 3600) / 60;
        int segundos = segundosTotales % 60;

        cout << "BOOM! Caiste en una bomba. Tiempo jugado: " 
            << horas << ":" << minutos << ":" << segundos << endl;
        ganador = false;
    }
    else
    {
        actualizarTablero(tablero, tableroGame, x, y, tamanoYCantidadBombas, usuario, tiempoInicial);
    }
}
vector <int> tamanoCuadriculaYCantidadBombas(int& nivelDificultad){
    // Determina nxn de la cuadricula y la cantidad de bombas
    return configuracionJuego[nivelDificultad]; // Retorno vector BOMBAS/Ncondition
}

int seleccionDificultad(){
    int nivelDificultad;
    do
    {
        // Selección de la dificultad
        cout << "\n" << "Seleccione una dificultad de juego" << endl;
        cout << "1. Experto" << endl;
        cout << "2. Intermedio" << endl;
        cout << "3. Cobarde" << endl;

        // Captura del nivel de dificultad
        nivelDificultad = get_int("\nIngrese su nivel de dificultad: ");
        cout << "\n";
    } while (nivelDificultad > 3 || nivelDificultad < 1);
    
    return nivelDificultad;
}

bool entradaValida(string& jugadaMayusc, int tamanoTablero){
    // Rango de coordenadas validas
    int rangoValido = 'A' + tamanoTablero;

    // Condiciones de verificación
    if (jugadaMayusc.length() != 3) // Verifica longitud
    { 
        cout << "\nLa entrada debe ser: A o F (Abrir o Bandera) / A-Z (Fila) / A-Z (Columna), todo junto (AFF o FAA)" << endl;
        return false;
    }
    
    if (jugadaMayusc[0] != 'F' && jugadaMayusc[0] != 'A') // Verifica rango Acción
    {
        cout << "\nAcción inválida. Debe ser 'F' o 'A'" << endl;
        return false;
    }

    if (jugadaMayusc[1] < 'A' || jugadaMayusc[1] >= rangoValido) // Verifica rango de filas
    {
        cout << "\nRango de fila inválido. Debe estar entre A y " << char(rangoValido - 1) << "." << endl;
        return false;
    }

    if (jugadaMayusc[2] < 'A' || jugadaMayusc[2] >= rangoValido) // Verifica rango de columnas
    {
        cout << "\nRango de columna inválido. Debe estar entre A y " << char(rangoValido - 1) << "." << endl;
        return false;
    }

    return true;
}

void jugadaUsuario(vector<vector<string>>& tablero, vector <int>& tamanoYCantidadBombas, vector<vector<string>>& tableroGame, string& usuario, std::time_t tiempoInicial){
    // Almacena la jugada
    string jugada;
    string jugadaMayusc = "";
    int tamanoTablero = tamanoYCantidadBombas[1];
    // Se ingresa la jugada del usuario
    do
    {
        cout << "\n" << "Ingrese su jugada: ";
        getline(cin, jugada);

        if (jugada.empty()) // No se ingreso nada
        {
            cout << "\n" << "Debe ingresar una jugada" << endl;
            cin.clear();
        }
        else
        {
            // Elimino los espcios en blanco en caso de existir
            jugada = strip(jugada);

            for (auto &&i : jugada) // Todo a Mayuscula
            {
                // Convertida a Mayuscula
                char c = toupper(i);
                jugadaMayusc += c;
            }
        }
        
        if (entradaValida(jugadaMayusc, tamanoTablero)) // Verfica si es valida la entrada
        {
            checkJugada(jugadaMayusc, tablero, tamanoYCantidadBombas, tableroGame, usuario, tiempoInicial); // Corrobora la jugada
        }
        
    } while (jugada.empty() && !entradaValida(jugadaMayusc, tamanoTablero)); // Deberia ajustarse a si esta vacia o es invalida
}

string colocarNumero(vector<vector<string>>& tableroGame, const int& i, const int& j, vector<int>& tamanoYCantidadBombas){
    // Contador de las bombas adyacentes
    int bombasCercanas = 0;

    // Busca bombas adyecentes dentro del rango del tablero
    for (size_t k = 0; k < dx.size(); k++)
    {
        if ((i + dx[k] >= 0 && tamanoYCantidadBombas[1] > i + dx[k]) &&
        (j + dy[k] >= 0 && tamanoYCantidadBombas[1] > j + dy[k])) // Dentro del rango
        {
            if (tableroGame[i + dx[k]][j + dy[k]] == "B") // Encuentra una bomba adyacente
            {
                bombasCercanas++;
            }
        }
    }

    string bombasAdyacentes;
    // Converson de string a entero las bombas cercanas
    intToString(bombasCercanas, bombasAdyacentes);

    return bombasAdyacentes;
}

void insertarIndicadoresBombas(vector<vector<string>>& tableroGame, vector<int>& tamanoYCantidadBombas){
    // Determina si son bombas o debe ir un numbero
    for (size_t i = 0; i < tamanoYCantidadBombas[1]; i++) {
        for (size_t j = 0; j < tamanoYCantidadBombas[1]; j++) {
            if (tableroGame[i][j] != "B") {
                tableroGame[i][j] = colocarNumero(tableroGame, i, j, tamanoYCantidadBombas);
            }
        }
    }
}

void insertarBombasTablero(vector<vector<string>>& tableroGame, set<pair<int, int>>& setCoordenadas, vector<int>& tamanoYCantidadBombas){
    // Inserta las bombas en las coordenadas aleatoriaas
    for (const auto& bomba : setCoordenadas) {
        int x = bomba.first, y = bomba.second;
        tableroGame[x][y] = "B";
    }
    // Inserta los numeros con bombas adyacentes
    insertarIndicadoresBombas(tableroGame, tamanoYCantidadBombas);
}

void obtenerCoordenadasBombas(vector<vector<string>>& tableroGame, vector <int>& tamanoYCantidadBombas){
    // Genero aleatoriamente las bombas
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, tamanoYCantidadBombas[1] - 1);

    // Set donde iran las coordenadas de las bombas
    set <pair <int, int>> setCoordenadas;

    while (setCoordenadas.size() != tamanoYCantidadBombas[0]){
        // Se declara el par de indices donde se generan las bombas
        pair <int, int> coordenadas;
        coordenadas.first = distrib(gen);
        coordenadas.second = distrib(gen);

        setCoordenadas.insert(coordenadas);
    }

    insertarBombasTablero(tableroGame, setCoordenadas, tamanoYCantidadBombas);
}

void imprimirTablero(vector<vector<string>>& tablero, vector <int>& tamanoYCantidadBombas, vector<vector<string>> tableroGame, string& usuario, std::time_t tiempoInicial){
    // Muestra la cantidad de bombas que quedan en el tablero
    cout << "Cantidad de bombas: " << tamanoYCantidadBombas[0] << "\n" << endl;

    int n = tablero.size(); // Número de filas y columnas

    // Imprimir encabezado de las columnas con letras
    cout << "  |";
    for (int col = 0; col < n; col++) {
        cout << char('A' + col) << " "; // Convertir el índice en letra
    }
    cout << endl;

    // Imprimir cada fila con el índice correspondiente
    for (int fila = 0; fila < n; fila++) {
        cout << char('A' + fila) << " |"; // Índice de la fila
        for (int col = 0; col < n; col++) {
            cout << tablero[fila][col] << "|";
        }
        cout << endl;
    }

    jugadaUsuario(tablero, tamanoYCantidadBombas, tableroGame, usuario, tiempoInicial);
}

void mostrarPuntuaciones(map <int, string, greater<int>> puntuacionesUsuarios){
    // Muestro las puntuaciones de mayor a menor
    cout << "\nPuntuaciones" << endl;
    
    for (const auto& [key, value] : puntuacionesUsuarios)
    {
        cout << "\n" << "Usuario: " << value << " Puntuación: " << key << endl;
    }
}

void puntuaciones(string& usuario, int tiempoJugador){
    if (tiempoJugador > 0) 
    {
        ofstream archivoEscritura("buscaminas_puntuaciones.txt", ios::app);
        if (archivoEscritura.is_open()) 
        {
            archivoEscritura << usuario << " " << tiempoJugador << endl;
            archivoEscritura.close();
        } else 
        {
            cout << "Error al guardar la puntuación." << endl;
        }
    }

    // Leer y mostrar puntuaciones
    ifstream archivoLectura("buscaminas_puntuaciones.txt");
    map<int, string> puntuacionesMap;

    if (archivoLectura.is_open()) 
    {
        string nombre;
        int segundos;
        while (archivoLectura >> nombre >> segundos) 
        {
            puntuacionesMap.insert({segundos, nombre});
        }
        archivoLectura.close();
    } 
    else
    {
        // Crear el archivo si no existe
        ofstream archivoCrear("buscaminas_puntuaciones.txt");
        archivoCrear.close();
        cout << "No hay puntuaciones registradas aún." << endl;
        return;
    }

    // Mostrar puntuaciones ordenadas de mejor a peor
    cout << "\n--- Tabla de Puntuaciones ---" << endl;
    for (const auto& par : puntuacionesMap) 
    {
        int h = par.first / 3600;
        int m = (par.first % 3600) / 60;
        int s = par.first % 60;
        cout << par.second << " - " 
             << setfill('0') << setw(2) << h << ":" 
             << setw(2) << m << ":" << setw(2) << s << endl;
    }
}

void manual(){
    cout << "\n";
    std::cout << "==============================\n";
    std::cout << "         REGLAS DEL BUSCAMINAS\n";
    std::cout << "==============================\n";
    std::cout << "1. El objetivo del juego es descubrir todas las casillas libres del tablero\n";
    std::cout << "   sin hacer clic en ninguna mina.\n\n";

    std::cout << "2. El tablero es una cuadrícula con celdas ocultas que pueden contener minas.\n";
    std::cout << "   - Al hacer clic en una celda:\n";
    std::cout << "     * Si es una mina: pierdes el juego.\n";
    std::cout << "     * Si no es una mina: aparece un número.\n\n";

    std::cout << "3. Los números indican cuántas minas están en las celdas adyacentes.\n";
    std::cout << "   - El número puede variar entre 1 y 8.\n";
    std::cout << "   - Si no hay minas cercanas, se descubre un área vacía conectada.\n\n";

    std::cout << "4. Usa banderas para marcar las celdas que creas que contienen minas.\n";
    std::cout << "   - Presiona clic derecho (o usa una opción del menú) para colocar una bandera.\n\n";

    std::cout << "5. Ganas si:\n";
    std::cout << "   - Descubres todas las celdas sin minas.\n";
    std::cout << "   - Todas las minas están marcadas correctamente con banderas.\n\n";

    std::cout << "6. Pierdes si haces clic en una mina.\n\n";

    std::cout << "==============================\n";
    std::cout << "           ¡Diviértete jugando!\n";
    std::cout << "==============================\n";
}

void game(string& usuario){
    // Dificultad de JUEGO/TAMAÑO CUADRICULA
    int nivelDificultad = seleccionDificultad();
    vector <int> tamanoYCantidadBombas = tamanoCuadriculaYCantidadBombas(nivelDificultad);

    // Creación del tablero oculto 
    vector<vector<string>> tablero(tamanoYCantidadBombas[1], vector<string>(tamanoYCantidadBombas[1], "#"));
    // Creación del tablero con bombas
    vector<vector<string>> tableroGame(tamanoYCantidadBombas[1], vector<string>(tamanoYCantidadBombas[1]));
    obtenerCoordenadasBombas(tableroGame, tamanoYCantidadBombas);

    // Capturar el tiempo inicial al inicio del juego
    auto tiempoInicial_tp = std::chrono::system_clock::now();
    std::time_t tiempoInicial = std::chrono::system_clock::to_time_t(tiempoInicial_tp);

    // Inicia el ciclo del juego
    do
    {
        imprimirTablero(tablero, tamanoYCantidadBombas, tableroGame, usuario, tiempoInicial); 
    } while (ganador);

    ganador = true; // Actualizacióon de la variable
}

void opcionesMenu(int& opcionJugador, string& usuario){
    // Ingreso a las funciones del juego 
    switch (opcionJugador)
    {
    case 1:
        game(usuario); // Inicio del juego
        break;

    case 2:
        puntuaciones(usuario); // Muestra todas las puntuaciones
        break;

    case 3: 
        manual(); // Muestra como jugar
        break;

    case 4:
        cout << "Gracias por jugar " << usuario << " Espero te hayas divertido" << endl;
        break;
    
    default:
        cout << "\n" << "Debe ingresar una opción entre (1-4)" << endl;
        break;
    }
}

void menuBuscaminas(string& usuario){
    // Opción del jugador
    int opcionJugador;
    // Interfaz del menú
    do
    {
        cout << "\n";
        cout << "==============" << endl;
        cout << "  Buscaminas  " << endl;
        cout << "==============" << endl;

        cout << "1. Jugar" << endl;
        cout << "2. Puntuaciones" << endl;
        cout << "3. ¿Cómo Jugar?" << endl;
        cout << "4. Salir";

        opcionJugador = get_int("\nIngrese su opción: ");
        opcionesMenu(opcionJugador, usuario);

    } while (opcionJugador != 4);
}

int main(){
    // Nombre del usuario
    string usuario;

    if (nombreUsuario(usuario))
    {
        menuBuscaminas(usuario); // Ingreso al menu del juego 
    }

    return 0;
}