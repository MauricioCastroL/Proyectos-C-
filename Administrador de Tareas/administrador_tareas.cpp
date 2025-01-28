#include <iostream>
#include <string>
#include <limits> // Para manejar límites de entrada
#include <sstream> // Para convertir cadenas a números
#include <map>
#include <vector>

using namespace std;

void agregarTarea();
void listarTarea();
void marcarTareaCompletada();
void eliminarTarea();

// Map donde guardaremos las tareas
map <string, vector <string>> tareasPendientes;
map <string, vector <string>> tareasCompletas;

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

bool inicioSesion(string& user){
    // Ingreso del nombre del usuario
    while (user.empty())
    {
        cout << "Bienvenido al administrador de tareas\n" << "Por favor, ingresa tu nombre: "; 
        getline(cin, user);

        if (user.empty()){ // Validación del nombre
            cout << "Debe ingresar un nombre" << endl;
            cin.clear();
        }
    }
    
    // Bienvenida
    cout << "\nBienvenido al gestor de tareas " << user << endl;
    return true;
}

void funciones(int opcion, string user){
    switch (opcion)
    {
    case 1:
        agregarTarea();
        break;
    
    case 2: 
        listarTarea();
        break;
    
    case 3:
        marcarTareaCompletada();
        break;

    case 4:
        eliminarTarea();
        break;

    case 5:
        cout << "Adios " << user << endl;
        break;

    default:
        cout << "Ingrese una opción entre 1-5" << endl;
        break;
    }
}

void menuAdministrador(string user){
    // Opción del usuario
    int opcion;

    // Interfaz del menú
    do
    {
        cout << "1. Agregar Tareas" << endl;
        cout << "2. Listar Tareas" << endl;
        cout << "3. Marcar tarea como completada" << endl;
        cout << "4. Eliminar Tareas" << endl;
        cout << "5. Salir" << endl;

        opcion = get_int("Ingrese su opción: ");
        funciones(opcion, user);
        
    } while (opcion != 5);    
}

void obtenerTarea(string& titulo, string& descripcion, string& fecha){
    // Obtener el titulo
    while (titulo.empty())
    {
        cout << "Título: ";
        getline(cin, titulo);

        if (titulo.empty()) // Validaciones de entrada 
        {
            cin.clear();
        }
    }
    
    // Obtener la descripción
    while (descripcion.empty())
    {
        cout << "Descripción: ";
        getline(cin, descripcion);

        if (descripcion.empty()) // Validaciones de entrada 
        {
            cin.clear();
        }
    }

    // Obtener la fecha
    while (fecha.empty())
    {
        cout << "Fecha límite (YYYY-MM-DD): ";
        getline(cin, fecha);

        if (fecha.empty()) // Validaciones de entrada 
        {
            cin.clear();
        }
    }

}

void agregarTarea(){
    /*Agregar una tarea Key-Value con ciclo
    iterativo por input del usuario */

    // Variables a ingresar
    string titulo, descripcion, fecha;

    obtenerTarea(titulo, descripcion, fecha); // Input usuario

    // Ingreso de las tareas
    tareasPendientes[titulo].push_back(descripcion);
    tareasPendientes[titulo].push_back(fecha);

    cout << "¡Tarea ingresada con éxito!" << endl;

}

void listarTarea(){
    // Listado de tareas pendientes y completas

    cout << "--Tareas pendientes--" << endl;

    // Ordenado por fechas
    for (const auto& [key, values] : tareasPendientes) {
        cout << "[" << key << "]"<<" - " << tareasPendientes[key][0] << ". - Fecha limite: " << tareasPendientes[key][1];
        cout << endl;
    }

    cout << "--Tareas completas--" << endl;

    // Ordenado por clave
    for (const auto& [key, values] : tareasCompletas) {
        cout << "[" << key << "]"<<" - " << tareasCompletas[key][0] << ". - Fecha limite: " << tareasCompletas[key][1];
        cout << endl;
    }
}

bool checkTareaExist(string& tarea){
    // Validación si existe la tarea
    if (tareasPendientes.count(tarea)){
        return true; // Existe la tarea
    }

    return false; // No existe la tarea
}

bool obtenerTareaCompletada(string& tareaCompletada){
    // Obtener la tarea
    while (tareaCompletada.empty())
    {
        cout << "Ingrese el nombre de la tarea completada: ";
        getline(cin, tareaCompletada);

        if (tareaCompletada.empty())
        {
            cin.clear();
        }
        else if (checkTareaExist(tareaCompletada)){
            return true ; // Existe la tarea
        } 
    }
    
    cout << "La tarea no existe" << endl;
    return false;
}


void marcarTareaCompletada(){
    // Variable de la tarea que quiere eliminar
    string tareaCompletada;

    if (obtenerTareaCompletada(tareaCompletada))
    {
        // Agregar al map de las tareas hechas
        tareasCompletas.insert({tareaCompletada, tareasPendientes[tareaCompletada]});

        // Elimino la tarea de pendientes
        tareasPendientes.erase(tareaCompletada);

        cout << "Tarea marcada como completa" << endl;
    }

}

bool obtenerTareaEliminar(string& tareaPorEliminar){
    // Obtener la tarea
    while (tareaPorEliminar.empty())
    {
        cout << "Ingrese la tarea que desea eliminar: ";
        getline(cin, tareaPorEliminar);

        if (tareaPorEliminar.empty())
        {
            cin.clear();
        }
        else if (checkTareaExist(tareaPorEliminar)){
            return true ; // Existe la tarea
        } 
    }
    
    cout << "La tarea no existe" << endl;
    return false;
}

void eliminarTarea(){
    // Eliminar por título
    string tareaPorEliminar;

    if (obtenerTareaEliminar(tareaPorEliminar))
    {
        tareasPendientes.erase(tareaPorEliminar);
        cout << "¡Tarea eliminada con exito!" << endl;
    }

}

int main(){
    // Captura el nombre del usuario
    string user;

    if (inicioSesion(user)){
        menuAdministrador(user);
    }

    return 0;
}
