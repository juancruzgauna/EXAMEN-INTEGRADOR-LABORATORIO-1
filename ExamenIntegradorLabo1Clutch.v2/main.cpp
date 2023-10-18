#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include "declaracionFunciones.h"

using namespace std;


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

    if(menuOpciones == 1)
    {


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

        mezclar(matrizCartas);

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

        int fila1, columna1, fila2, columna2, filaMazo, columnaMazo;

        //DECLARO LAS MANOS DE AMBOS JUGADORES COMO VECTORES DE STRING

        string manoJugador1[5];
        string manoJugador2[5];
        string cartasDelMazo[10];

        //DECLARO EL VECTOR DE MANO GANADORA POR SI TOCA AL REPARTIR HAY QUE MEZCLAR DE NUEVO

        string manoGanadora[5] = {"10", "J", "Q", "K", "A"};


        //REPARTO 5 CARTAS AL JUGADOR 1

        cout<<jugador1<<endl;

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

        //REPARTO 10 CARTAS AL MAZO
        cout << endl;
        cout << "Cartas del mazo" << endl;

        for (int x = 1; x <= 10; x++)
        {
            do
            {
                filaMazo = (rand() % 5);             // Genera un número aleatorio entre 0 y 4
                columnaMazo = (rand() % 4);           //Genera número aleatorio entre 0 y 3
            }
            while (matrizElementos[filaMazo][columnaMazo] != 0);   // Asegura que la carta no se haya tomado antes

            // Muestra la carta que se le asigna al jugador 2
            cout << "Carta nro : " << x << " del mazo es: " << matrizCartas[filaMazo][columnaMazo] << endl;

            matrizElementos[filaMazo][columnaMazo]++; // Registra que esta carta ha sido tomada

            cartasDelMazo[x - 1] = matrizCartas[filaMazo][columnaMazo];
        }

        cout << endl;



        //MANO GANADORA
        bool ganoElJugador1 = true;
        bool ganoElJugador2 = true;
        int tamManoJugador = 5;
        int tamMazo = 10;

        ganoElJugador1 = determinarSiGanoElJugador(manoJugador1, carta, tamManoJugador);
        ganoElJugador2 = determinarSiGanoElJugador(manoJugador2, carta, tamManoJugador);


        if(ganoElJugador1 == true || ganoElJugador2 == true)
        {
            cout << "Alguno de los dos jugadores empezo con la mano ganadora, se deben repartir las cartas nuevamente" << endl;

        }
        else if(ganoElJugador1 == false || ganoElJugador2 == false)
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



        //DEFINO QUIEN COMIENZA LA PARTIDA
        string quienEmpieza, quienNoEmpieza;
        int bandera = 0;
        string manoJugadorQueEmpieza[5];
        string manoJugadorQueNoEmpieza[5];

        //SEGUN QUIEN EMPIECE ES COMO VOY A CARGAR NUEVOS VECTORES

        if(acumulador_jugador1 > acumulador_jugador2)
        {

            quienEmpieza = jugador1;
            quienNoEmpieza = jugador2;
            bandera = 1;

            for(int x = 0; x < 5; x++)
            {
                manoJugadorQueEmpieza[x] = manoJugador1[x];
            }

            for(int x = 0; x < 5; x++)
            {
                manoJugadorQueNoEmpieza[x] = manoJugador2[x];
            }


        }
        else if(acumulador_jugador2 > acumulador_jugador1)
        {
            quienEmpieza = jugador2;
            quienNoEmpieza = jugador1;
            bandera = 2;

            for(int x = 0; x < 5; x++)
            {
                manoJugadorQueEmpieza[x] = manoJugador2[x];
            }

            for(int x = 0; x < 5; x++)
            {
                manoJugadorQueNoEmpieza[x] = manoJugador1[x];
            }

        }
        else if(acumulador_jugador1 = acumulador_jugador2)
        {
            cout << "Hay empate, se deben repartir las cartas nuevamente" << endl;
        }


        //COMIENZO DE RONDA


        //CON UN FOR DE 2 VUELTAS HAGO CADA RONDA (1 TURNO PARA CADA JUGADOR)






        for(int i = 0; i<2; i++)
        {
            cout << endl;
            cout << "CLUTCH" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            cout << "RONDA #" << ronda << endl;
            cout << jugador1 << " vs " << jugador2;
            cout << endl << endl;
            cout << "TURNO DE " << quienEmpieza << endl;

        // Se realiza el lanzamiento de dado
            int dado = 2;

            cout << "LANZAMIENTO DADO #" << dado << endl;

            int cartaCorral;
            string auxiliar;



            //OPCION DADO 1 JUGADOR QUE EMPIEZA

            if(dado == 1)
            {

                cout << "Ingrese carta del corral a intercambiar con el mazo (1-5) :" << endl;
                cin >> cartaCorral;

                auxiliar = manoJugadorQueEmpieza[cartaCorral - 1];
                manoJugadorQueEmpieza[cartaCorral - 1] = cartasDelMazo [0];
                cartasDelMazo[0] = auxiliar;

                cout << "Las nuevas cartas del jugador 1 son : " << endl;

                for(int x = 0; x < 5; x++)
                {
                    cout << manoJugadorQueEmpieza[x] << endl;
                }
            }

            //OPCION DADO 2 JUGADOR QUE EMPIEZA

            if(dado == 2)
            {
                cout << "Ingrese la carta del corral contrario a intercambiar con el mazo" << endl;
                cin >> cartaCorral;

                auxiliar = manoJugadorQueNoEmpieza[cartaCorral - 1];
                manoJugadorQueNoEmpieza[cartaCorral - 1] = cartasDelMazo[0];
                cartasDelMazo[0] = auxiliar;

                cout << "Las nuevas cartas del jugador " << quienNoEmpieza << "son: "<< endl;

                for(int x = 0; x < 5; x++)
                {
                    cout << manoJugadorQueNoEmpieza[x] << endl;
                }
            }



            //OPCION DADO 1 JUGADOR QUE NO EMPIEZA

            if(dado == 1)
            {

                cout << "Ingrese carta del corral a intercambiar con el mazo (1-5) :" << endl;
                cin >> cartaCorral;

                auxiliar = manoJugadorQueNoEmpieza[cartaCorral - 1];
                manoJugadorQueNoEmpieza[cartaCorral - 1] = cartasDelMazo [0];
                cartasDelMazo[0] = auxiliar;

                cout << "Las nuevas cartas del jugador 2 son : " << endl;

                for(int x = 0; x < 5; x++)
                {
                    cout << manoJugadorQueNoEmpieza[x] << endl;
                }
            }

            //OPCION DADO 2 JUGADOR QUE NO EMPIEZA
            if(dado == 2)
            {
                cout << "Ingrese la carta del corral contrario a intercambiar con el mazo" << endl;
                cin >> cartaCorral;

                auxiliar = manoJugadorQueEmpieza[cartaCorral - 1];
                manoJugadorQueEmpieza[cartaCorral - 1] = cartasDelMazo[0];
                cartasDelMazo[0] = auxiliar;

                cout << "Las nuevas cartas del jugador: " << quienEmpieza << " son: " << endl;

                for(int x = 0; x < 5; x++)
                {
                    cout << manoJugadorQueNoEmpieza[x] << endl;
                }
            }





            cout << endl;
            cout << "CLUTCH" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            cout << "RONDA #" << ronda << endl;
            cout << jugador1 << " vs " << jugador2;
            cout << endl << endl;
            cout << "TURNO DE " << quienNoEmpieza << endl;

        }


        ronda++;

        //DESPUES DE CADA RONDA INTENTO DETERMINAR SI ALGUNO DE LOS DOS JUGADORES GANÓ COMPARANDO CON LA MANO GANADORA

        ganoElJugador1 = determinarSiGanoElJugador(manoJugador1, carta, tamManoJugador);
        ganoElJugador2 = determinarSiGanoElJugador(manoJugador2, carta, tamManoJugador);








    }

    //ESTADÍSTICAS

    if(menuOpciones == 2)
    {

        cout << "Aqui se muestran las estadisticas" << endl;
    }

    //CRÉDITOS

    if(menuOpciones == 3)
    {

        cout << "Se muestran apellidos, nombres y legajos de intregantes del equipo";
    }

    //SALIR

    if(menuOpciones == 0)
    {

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

    if(menuOpciones != 1 && menuOpciones != 2 && menuOpciones != 3 && menuOpciones != 0)
    {

        cout << endl << "No se ingresó un número válido en el menu principal, por favor ingrese nuevamente" << endl << endl;
        return main();
    }




    system("pause>nul");
    return 0;
}


