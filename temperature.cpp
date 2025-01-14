#include <iostream>

int main(){
    // Variables de entrada (Temperaturas)
    float temperatureCelcius;
    float temperatureFarenheith;
    float resutlConvertion;

    // Opción de cambio
    int option;

    // Menu
    std::cout<<"      Conversor de Temperaturas      "<<std::endl;
    std::cout<<"====================================="<<std::endl;

    std::cout<<"1.Celcius(°C) a Farenheith(°F)"<<std::endl;
    std::cout<<"2.Farenheith(°F) a Celcius(°C)"<<std::endl;

    // Ingreso de la opción
    std::cout<<"Ingrese su opción: ";
    std::cin>>option;

    std::cout<<"====================================="<<std::endl;

    // Calculos y conversión
    switch(option){

        // Celcius a Farenheith
        case 1:
            std::cout<<"Ingrese los grados Celcius: ";
            std::cin>>temperatureCelcius;

            resutlConvertion = ((temperatureCelcius * (9.0 / 5.0)) + 32);

            std::cout<<temperatureCelcius<<"°C"<<" Equivalen a: "<<resutlConvertion<<"F"<<std::endl;
            break;

        // Farenheith a Celcius
        case 2:
            std::cout<<"Ingrese los grados Farenheith: ";
            std::cin>>temperatureFarenheith;

            resutlConvertion = (temperatureFarenheith - 32) * (5.0 / 9.0);

            std::cout<<temperatureFarenheith<<"°F"<<" Equivalen a: "<<resutlConvertion<<"°C"<<std::endl;
            break;
        
        // Caso default
        default:
            std::cout<<"La opción va de (1-2), vuelve a intentarlo";
            break;
    }

    return 0;
}