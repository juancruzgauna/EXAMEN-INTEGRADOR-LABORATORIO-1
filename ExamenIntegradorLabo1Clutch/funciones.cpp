#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <time.h>
#include <algorithm>
using namespace std;

//DEFINICION DE FUNCIONES

//Defino funci�n para desplegar el men� principal
void desplegarMenu()
{
    cout << "+--------------------+" << endl;
    cout << "|      \\             |" <<endl;
    cout << "|     (o>            |"<<endl;
    cout << "|   \\_//) CLUTCH     |" << endl;
    cout << "|    \\/_)            |"<<endl;
    cout << "|     _|_            |"<<endl;
    cout << "|--------------------|" << endl;
    cout << "|                    |"<<endl;
    cout << "|  1 - JUGAR         |" << endl;
    cout << "|                    |"<<endl;
    cout << "|  2 - ESTAD�STICAS  |" << endl;
    cout << "|                    |"<<endl;
    cout << "|  3 - CR�DITOS      |" << endl;
    cout << "|                    |"<<endl;
    cout << "|--------------------|" << endl;
    cout << "|                    |"<<endl;
    cout << "|  0 - SALIR         |" << endl;
    cout << "|                    |"<<endl;
    cout << "+--------------------+" << endl;

}
//Defino funci�n para ingresar nombres de los jugadores
string asignarNombres()
{
    string namePlayer;

    cout << "CLUTCH" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Antes de comenzar deben registrar sus nombres: " << endl << endl;
    cout << "�Nombre? ";
    cin >> namePlayer;
    return namePlayer;

}
// Defino funci�n para confirmar nombres de los jugadores

char confirmarNombresJugadores()
{
    char confirmar;

    cout << "�Confirmar nombres? (S/N)" << endl;
    cin >> confirmar;
    cout << "------------------------------------------------------------------------" << endl;
    return confirmar;

}

// Defino funci�n mezclar cartas
void mezclar(string matrizCartas[][4]) {
    srand(time(0));

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 4; j++) {
            int m = rand() % 5;
            int n = rand() % 4;
            swap(matrizCartas[i][j], matrizCartas[m][n]);
        }
        cout << endl;
    }

}
