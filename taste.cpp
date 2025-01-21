#include <iostream>
#include <string>

using namespace std;

class Estudiante
{
    public:
        string name;
        int id;

        Estudiante(string name, int id)
        {
            this->name = name;
            this->id = id;
        }

        void mostrar(){
            cout << name << " " << id << endl;
        }

};


int main() {

    Estudiante lol("Enrique", 123);

    lol.mostrar();

    return 0;
}

