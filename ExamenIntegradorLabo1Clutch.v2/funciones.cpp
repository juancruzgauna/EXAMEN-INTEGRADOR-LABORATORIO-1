#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <time.h>
#include <algorithm>
using namespace std;

//DEFINICION DE FUNCIONES

//Defino función para desplegar el menú principal
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
    cout << "|  2 - ESTADÍSTICAS  |" << endl;
    cout << "|                    |"<<endl;
    cout << "|  3 - CRÉDITOS      |" << endl;
    cout << "|                    |"<<endl;
    cout << "|--------------------|" << endl;
    cout << "|                    |"<<endl;
    cout << "|  0 - SALIR         |" << endl;
    cout << "|                    |"<<endl;
    cout << "+--------------------+" << endl;

}
//Defino función para ingresar nombres de los jugadores
string asignarNombres()
{
    string namePlayer;

    cout << "CLUTCH" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Antes de comenzar deben registrar sus nombres: " << endl << endl;
    cout << "¿Nombre? ";
    cin >> namePlayer;
    return namePlayer;

}
// Defino función para confirmar nombres de los jugadores

char confirmarNombresJugadores()
{
    char confirmar;

    cout << "¿Confirmar nombres? (S/N)" << endl;
    cin >> confirmar;
    cout << "------------------------------------------------------------------------" << endl;
    return confirmar;

}

// Defino función mezclar cartas
void mezclar(string matrizCartas[][4])
{
    srand(time(0));

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int m = rand() % 5;
            int n = rand() % 4;
            swap(matrizCartas[i][j], matrizCartas[m][n]);
        }
        cout << endl;
    }

}

int tirardado()
{
    int dado;
    srand(time(0));
    dado = rand() % 6 + 1;
    switch (dado)
    {
    case 1:
        cout << "LANZAMIENTO DADO #1" << endl;
        cout << "-------------------" << endl;

        cout << "Elegir una carta de su propio corral (1-5) y robar una carta del mazo. Se intercambian las dos. La carta robada pasa a formar parte del corral y la carta seleccionada se incorpora al mazo." <<endl;
        cout << endl;
        break;
    case 2:
        cout << "LANZAMIENTO DADO #2" << endl;
        cout << "-------------------" << endl;

        cout << "Elegir una carta del corral del contrario (1-5) y robar una carta del mazo. Se intercambian las dos. La carta robada pasa a formar parte del corral del contrario y la carta seleccionada se incorpora al mazo."<<endl;
        break;
    case 3:
        cout << "LANZAMIENTO DADO #3" << endl;
        cout << "-------------------" << endl;

        cout << "Elegir una carta del corral propio (1-5) e intercambiarla por una carta del corral del contrario (1-5). Las cartas seleccionadas se intercambian."<<endl;
        break;
    case 4:
        cout << "LANZAMIENTO DADO #4" << endl;
        cout << "-------------------" << endl;

        cout << "Intercambiar dos cartas del propio corral. Se eligen dos cartas del propio corral (1-5) y se intercambian entre sí"<<endl;
        break;
    case 5:
        cout << "LANZAMIENTO DADO #5" << endl;
        cout << "-------------------" << endl;

        cout << "Bloquear una carta del corral. La carta bloqueada no puede ser elegida por el contrario para intercambio (acciones 2 y 3) pero sí puede ser elegida por uno mismo."<<endl;
        break;
    case 6:
        cout << "LANZAMIENTO DADO #6" << endl;
        cout << "-------------------" << endl;

        cout << "Elegir cualquiera de las acciones anteriores o bien pasar el turno."<< endl;
        break;
    default:
        cout << "Opción no válida. Arroje nuevamente el dado." << endl;
        break;
    }
    return dado;
}

bool determinarSiGanoElJugador(string manoJugador[], string carta[], int tam)
{

    bool ganoElJugador = true;

    for(int x = 0; x < tam; x++)
    {
        if(manoJugador[x] != carta[x])
        {
            return false;
        }
    }
    return true;
}
