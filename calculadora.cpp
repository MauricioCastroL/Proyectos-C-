/*Autor: Mauricio Castro Leal
Fecha: 14/01/2024
Objetivo: Crear una calculadora simple */

#include <iostream>

int main(){
    float result;
    int option;
    float x;
    float y; 

    std::cout<<"         OPERACIONES MATEMÁTICAS       "<<std::endl;
    std::cout<<"========================================"<<std::endl;

    std::cout<<"1.Suma"<<std::endl;
    std::cout<<"2.Resta"<<std::endl;
    std::cout<<"3.Multiplicación"<<std::endl;
    std::cout<<"4.División"<<std::endl;
    std::cout<<"Ingrese su opcion: ";

    std::cin>>option;
    std::cout<<"========================================"<<std::endl;

    switch(option){
        case 1:

            std::cout<<"Ingrese un número: ";
            std::cin>>x;

            std::cout<<"Ingrese un número: ";
            std::cin>>y;

            result = x + y;

            std::cout<<"El resultado es: "<<result<<std::endl;

            break;

        case 2:

            std::cout<<"Ingrese un número: ";
            std::cin>>x;

            std::cout<<"Ingrese un número: ";
            std::cin>>y;

            result = x - y;

            std::cout<<"El resultado es: "<<result<<std::endl;

            break;

        case 3:

            std::cout<<"Ingrese un número: ";
            std::cin>>x;

            std::cout<<"Ingrese un número: ";
            std::cin>>y;

            result = x * y;

            std::cout<<"El resultado es: "<<result<<std::endl;

            break;

        case 4:

            std::cout<<"Ingrese un número: ";
            std::cin>>x;

            std::cout<<"Ingrese un número: ";
            std::cin>>y;
            
            if (y != 0){
                result = x / y;
    
                std::cout<<"El resultado es: "<<result<<std::endl;
                break;
            }
            else{
                std::cout<<"El divisor no puede ser 0!";
                break;
            }

        default:
            std::cout<<"Las opciones son del (1-4)!"<<std::endl;
            break;
    }

    return 0;
}