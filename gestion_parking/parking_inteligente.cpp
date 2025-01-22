/* Autor: Mauricio Castro Leal
Fecha: 21/01/2025
Objetivo: Crear un sistema automatizado de estacionamiento */

#include <iostream>
#include <string>
#include <chrono>

using namespace std;

// Declaración de variables globales
const int MAX_SPACE = 30;
int clientes_totales = 0;
int clientes_en_uso = 0;
double dinero_recolectado = 0;
const int TARIFA_MINUTO = 22;

// Reciclaje de codigo
const bool ERROR = false;
const bool EXITO = true;

struct parking_inteligente
{
    bool estacionamiento; // Array de booleanos
    string registro_matriculas; // Array de matriculas 
    chrono::time_point<chrono::high_resolution_clock> tiempo_entrada; // Array de tiempo por vehiiculo
};

// Declaro la estructura 
parking_inteligente Parking[MAX_SPACE];

// Scope funciones
bool ingresoMatricula();
bool checkEstacionamiento();
void ingresoVehiculos();
void salidaVehiculos();
bool retiroMatricula();
void dailyReport();

int main(){

    // Declaracion de variables
    int option; 

    // Se inicia con todos los puestos desocupados 
    for (size_t i = 0; i < MAX_SPACE; i++)
    {
        Parking[i].estacionamiento = true;
    }
    
    do
    {
        // Menú para los trabajadores
        cout << "======================" << endl;
        cout << " Parking Inteligente " << endl;
        cout << "======================" << endl;

        // Opciones

        cout << "1. Ingreso de vehiculos" << endl;
        cout << "2. Salida de vehiculos" << endl;
        cout << "3. Reporte" << endl;
        cout << "4. Salir" << endl;

        cout << "Su opción: ";
        cin >> option;

        switch (option)
        {
            case 1:
                ingresoVehiculos(); // Registra entrada de vehiculos
                break;
            
            case 2:
                salidaVehiculos(); // Regista salida de vehiculos
                break;

            case 3:
                dailyReport(); // Reporte 
                break;
                
            case 4:  // Detiene el programa
                break;

            default:
                cout << "Opción invalida!" << endl;
                break;
        }

    } while (option != 4);
  
    return 0;
}

bool checkEstacionamiento(){
    // Verifica si hay espacio en el parking
    if (clientes_en_uso < MAX_SPACE)
    {
        return EXITO;
    }
    
    return ERROR;
}

bool ingresoMatricula(){
    // Declaro variable para almacenar la matricula
    string matricula;

    for (size_t i = 0; i < MAX_SPACE; i++)
    {
        if(Parking[i].estacionamiento == true)
        {
            Parking[i].estacionamiento = false; // El espacio del nuevo cliente se reserva
            // Se obtiene la matricula
            cin.ignore();
            cout << "Ingrese la matricula del vehiculo a ingresar: ";
            getline(cin, matricula);

            if (matricula.empty()){
                Parking[i].estacionamiento = true;
                cout << "Ingreso una matricula vacia" << endl;
                return ERROR;
            }
            else{
                Parking[i].registro_matriculas = matricula;
                Parking[i].tiempo_entrada = chrono::high_resolution_clock::now();
                cout << "Regitado con exito!" << endl;
                return EXITO; // Ingreso exitoso
            }
        }
    }
    
    return ERROR; // Ingreso fallido
}

void ingresoVehiculos(){
    // Verifico si hay lugar de estacionamiento
    if (checkEstacionamiento()){
        if (ingresoMatricula()){ // Registra la matricula
            clientes_en_uso ++;
            clientes_totales ++;
        }else
        {
            cout << "Ingreso fallido" << endl;
        }   
    }  
    else{
        cout << "No hay espacio en el estacionamiento!" << endl;
    }
    
}

bool retiroMatricula(){
    // Matricula a retirar 
    string matricula; // Guarda la matricula a quitas

    // Se obtiene la matricula
    cin.ignore();
    cout << "Ingrese la matricula del vehiculo a retirar: ";
    getline(cin, matricula);

    if (matricula.empty()){
        cout << "Se ingreso una matriculla vacia" << endl; 
        return ERROR;
    }
    
    for (size_t i = 0; i < MAX_SPACE; i++)
    {
        if (Parking[i].registro_matriculas == matricula) // Si la matricula esta registrada
        {
            // Cálculo del tiempo en el estacionamiento
            auto tiempo_salida = chrono::high_resolution_clock::now();
            auto duracion = chrono::duration_cast<chrono::minutes>(tiempo_salida - Parking[i].tiempo_entrada);
            int minutos = duracion.count();

            // Cálculo del costo
            double costo = minutos * TARIFA_MINUTO;
            dinero_recolectado += costo;
            
            cout << "El tiempo en el parking fue de: " << minutos << " minutos" << endl;
            cout << "El costo es de: " << costo << endl;

            Parking[i].registro_matriculas = ""; // Se borra la matricula
            Parking[i].estacionamiento = true; // Espacio disponible

            return EXITO;
        }
        
    }

    return ERROR; // Si no se encuentra la amtricula
    
}

void salidaVehiculos(){
    if (clientes_en_uso == 0) // Verificación del estacionamiento 
    {
        cout << "El estacionamiento ya esta vacio!" << endl;
    }
    else{
        if (retiroMatricula()){
            cout << "Retiro exitoso" << endl;
            clientes_en_uso --; // Se reduce el estacionamiento 
        }else{
            cout << "No se pudo retirar, matricula incorrecta" << endl;
        }
    }
}

void dailyReport(){
    // Genera un reporte de ganancias y clientes 
    cout << "==========================" << endl;
    cout << "Reporte diario de ingresos" << endl;
    cout << "==========================" << endl;

    cout << "Clientes atendidos: " << clientes_totales << endl;
    cout << "Dinero recolectado: $" << dinero_recolectado << endl;

}