#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <time.h>
#include <algorithm>

using namespace std;

//DECLARACION DE FUNCIONES

void desplegarMenu();
string asignarNombres();
char confirmarNombresJugadores();
void mezclar(string[], int);


int main()
{
    setlocale(LC_ALL, "spanish");

    //VARIABLES MENU OPCIONES
    int menuOpciones, ronda = 1;
    char confirmarSalir, confirmarNombres;
    string jugador1, jugador2;

    desplegarMenu();
    cin >> menuOpciones;
    cout << endl;

    if(menuOpciones == 1){


    //JUGAR

        jugador1 = asignarNombres();
        jugador2 = asignarNombres();

        confirmarNombres = confirmarNombresJugadores();

        if(confirmarNombres == 'N' || confirmarNombres == 'n')
        {

            jugador1 = asignarNombres();
            jugador2 = asignarNombres();

            confirmarNombres = confirmarNombresJugadores();

        }

        //Funcion para generar números aleatorios

        srand(time(0));

        //Declaro las matrices

        string matrizCartas[5][4];
        int matrizElementos[5][4] = {};
        string matrizSinMezclar[5][4];

        //Declaro vectores de cartas y palos

        string carta[5] = {"10", "J", "Q", "K", "A"};
        string palo[4] = {" de Picas ", " de Diamantes", " de Corazones ", " de Tréboles "};

        // Armo las cartas en la matriz combinando las cartas y los palos

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matrizCartas[i][j] = carta[i] + palo[j];
            }
        }


        // Creo una matriz sin mezclar para comparar posteriormente los valores de las manos con las cartas

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matrizSinMezclar[i][j] = carta[i] + palo[j];
            }
        }

        // Mezclar cartas

        int tamanio = 20;
        mezclar(matrizCartas[0], tamanio);

        // Muestro las cartas ya mezcladas

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                cout << matrizCartas[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl << endl;

        int fila1, columna1, fila2, columna2;

        //DECLARO LAS MANOS DE AMBOS JUGADORES COMO VECTORES DE STRING

        string manoJugador1[5];
        string manoJugador2[5];

        //DECLARO EL VECTOR DE MANO GANADORA POR SI TOCA AL REPARTIR HAY QUE MEZCLAR DE NUEVO

        string manoGanadora[5] = {"10", "J", "Q", "K", "A"};


        //REPARTO 5 CARTAS AL JUGADOR 1

        for (int x = 1; x <= 5; x++)
        {
            do
            {
                fila1 = (rand() % 5);             // Genera un número aleatorio entre 0 y 4
                columna1 = (rand() % 4);             // Genera un número aleatorio entre 0 y 3
            }
            while (matrizElementos[fila1][columna1] != 0);   // Asegura que la carta no se haya tomado antes

            // Muestra la carta que se le asigna al jugador 1
            cout << "Carta nro : " << x << " del jugador 1 es: " << matrizCartas[fila1][columna1] << endl;

            matrizElementos[fila1][columna1]++;// Registra que esta carta ha sido tomada

            manoJugador1[x - 1] = matrizCartas[fila1][columna1];
        }

        cout << endl;

        // REPARTO 5 CARTAS AL JUGADOR 2 (SIMILAR A JUGADOR 1)

        cout<<jugador2<<endl;
        cout<<"--------"<<endl;

        for (int x = 1; x <= 5; x++)
        {
            do
            {
                fila2 = (rand() % 5);             // Genera un número aleatorio entre 0 y 4
                columna2 = (rand() % 4);           //Genera número aleatorio entre 0 y 3
            }
            while (matrizElementos[fila2][columna2] != 0);   // Asegura que la carta no se haya tomado antes

            // Muestra la carta que se le asigna al jugador 2
            cout << "Carta nro : " << x << " del jugador 2 es: " << matrizCartas[fila2][columna2] << endl;

            matrizElementos[fila2][columna2]++; // Registra que esta carta ha sido tomada

            manoJugador2[x - 1] = matrizCartas[fila2][columna2];
        }
        cout << endl;



        //MANO GANADORA
        bool ganoElChabon = true;

        for(int x = 0; x < 5; x++)
        {
            if(manoJugador1[x] != carta[x])
            {
                ganoElChabon = false;
            }
        }

        if(ganoElChabon == true)
        {
            cout << "Se empezo con la mano ganadora" << endl;

        }
        else if(ganoElChabon == false)
        {
            cout << "Se puede arrancar tranquilamente" << endl;
        }


        int acumulador_jugador1 = 0;

        for (int x = 0; x < 5; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                if (manoJugador1[x] == matrizSinMezclar[4][y])
                {
                    acumulador_jugador1 += 625;
                }
                else if (manoJugador1[x] == matrizSinMezclar[3][y])
                {
                    acumulador_jugador1 += 125;
                }
                else if (manoJugador1[x] == matrizSinMezclar[2][y])
                {
                    acumulador_jugador1 += 25;
                }
                else if(manoJugador1[x] == matrizSinMezclar[1][y])
                {
                    acumulador_jugador1 += 5;
                }
                else if(manoJugador1[x] == matrizSinMezclar[0][y])
                {
                    acumulador_jugador1 += 1;
                }
            }
        }

        cout << acumulador_jugador1 << endl;

        int acumulador_jugador2 = 0;

        for (int x = 0; x < 5; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                if (manoJugador2[x] == matrizSinMezclar[4][y])
                {
                    acumulador_jugador2 += 625;
                }
                else if (manoJugador2[x] == matrizSinMezclar[3][y])
                {
                    acumulador_jugador2 += 125;
                }
                else if (manoJugador2[x] == matrizSinMezclar[2][y])
                {
                    acumulador_jugador2 += 25;
                }
                else if(manoJugador2[x] == matrizSinMezclar[1][y])
                {
                    acumulador_jugador2 += 5;
                }
                else if(manoJugador2[x] == matrizSinMezclar[0][y])
                {
                    acumulador_jugador2 += 1;
                }
            }
        }


        cout << acumulador_jugador2 << endl;


        //DEFINO QUIEN COMIENZA LA PARTIDA
        string quienEmpieza;

        if(acumulador_jugador1 > acumulador_jugador2)
        {

            quienEmpieza = jugador1;

        }
        else if(acumulador_jugador2 > acumulador_jugador1)
        {
            quienEmpieza = jugador2;

        }
        else if(acumulador_jugador1 == acumulador_jugador2)
        {
            cout << "Hay empate, se deben repartir las cartas nuevamente" << endl;
        }


        //COMIENZO DE RONDA
        for(int i = 0; i<2; i++)
        {
            cout << endl;
            cout << "CLUTCH" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            cout << "RONDA #" << ronda << endl;
            cout << jugador1 << " vs " << jugador2;
            cout << endl << endl;
            cout << "TURNO DE " << quienEmpieza << endl;

        }

        ronda++;


    }

    //ESTADÍSTICAS

    if(menuOpciones == 2){

        cout << "Aqui se muestran las estadisticas" << endl;
    }

    //CRÉDITOS

    if(menuOpciones == 3){

        cout << "Se muestran apellidos, nombres y legajos de intregantes del equipo";
    }

    //SALIR

    if(menuOpciones == 0){

        cout << "¿Está seguro de que desea salir? (S para sí - N para no)" << endl;
        cin >> confirmarSalir;

        cout << endl;
        if(confirmarSalir == 'S' || confirmarSalir == 's')
        {
            cout << "Juego finalizado" << endl;

        }
        else if(confirmarSalir == 'N' || confirmarSalir == 'n')
        {
            return main();
        }
    }

    if(menuOpciones != 1 && menuOpciones != 2 && menuOpciones != 3 && menuOpciones != 0){

        cout << endl << "No se ingresó un número válido en el menu principal, por favor ingrese nuevamente" << endl << endl;
        return main();
    }




    system("pause>nul");
    return 0;
    }





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
void mezclar(string cartas[], int tamanio)
{
    srand(time(0));
    for (int n = 0; n < tamanio; n++)
    {
        int m = rand() % tamanio;
        swap(cartas[n], cartas[m]); //implemento SWAP que recibe dos parámetros e intercambia el valor del uno por el otro.
    }
}
