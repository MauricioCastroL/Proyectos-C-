/*Autor: Mauricio Castro Leal
Fecha: 14/01/2024
Objetivo: Calcular el area de un circulo */

#include <iostream>
#include <cmath>

int main(){
    float catetoOpuesto;
    float catetoAdyacente;
    float hipotenuza;

    std::cout<<"Ingrese el valor del cateto adyacente: ";
    std::cin>>catetoAdyacente;

    std::cout <<"Ingrese el valor del cateto opuesto: ";
    std::cin>>catetoOpuesto;

    hipotenuza = sqrt(pow(catetoAdyacente, 2) + pow(catetoOpuesto, 2));

    std::cout<<"El valor de la hipotenuza es: "<<hipotenuza<<std::endl;

    return 0;
}