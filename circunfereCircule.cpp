/*Autor: Mauricio Castro Leal
Fecha: 14/01/2024
Objetivo: Calcular el perimetro de un circulo */

#include <iostream>

int main(){

    const float Pi = 3.14159;
    float radius = 50;
    float circunference = 2 * Pi* radius;

    std::cout<<circunference<<" Centimeter"<<std::endl;

    return 0;
}