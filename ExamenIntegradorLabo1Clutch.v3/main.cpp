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

        //Funcion para generar n�meros aleatorios

        srand(time(0));

        //Declaro las matrices

        string matrizCartas[5][4];
        int matrizElementos[5][4] = {};
        string matrizSinMezclar[5][4];

        //Declaro vectores de cartas y palos

        string carta[5] = {"10", "J", "Q", "K", "A"};
        string palo[4] = {" de Picas ", " de Diamantes", " de Corazones ", " de Tr�boles "};

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

        cout << "+-------------------------+" << endl;
        cout << jugador1<< endl;
        for (int x = 1; x <= 5; x++)
        {
            do
            {
                fila1 = (rand() % 5);             // Genera un n�mero aleatorio entre 0 y 4
                columna1 = (rand() % 4);             // Genera un n�mero aleatorio entre 0 y 3
            }
            while (matrizElementos[fila1][columna1] != 0);   // Asegura que la carta no se haya tomado antes

            // Muestra la carta que se le asigna al jugador 1
            cout << matrizCartas[fila1][columna1] << endl;

            matrizElementos[fila1][columna1]++;// Registra que esta carta ha sido tomada

            manoJugador1[x - 1] = matrizCartas[fila1][columna1];
        }

        cout << endl;

        // REPARTO 5 CARTAS AL JUGADOR 2 (SIMILAR A JUGADOR 1)

        cout << jugador2 << endl;


        for (int x = 1; x <= 5; x++)
        {
            do
            {
                fila2 = (rand() % 5);             // Genera un n�mero aleatorio entre 0 y 4
                columna2 = (rand() % 4);           //Genera n�mero aleatorio entre 0 y 3
            }
            while (matrizElementos[fila2][columna2] != 0);   // Asegura que la carta no se haya tomado antes

            // Muestra la carta que se le asigna al jugador 2
            cout << matrizCartas[fila2][columna2] << endl;

            matrizElementos[fila2][columna2]++; // Registra que esta carta ha sido tomada

            manoJugador2[x - 1] = matrizCartas[fila2][columna2];
        }

        cout << "+-------------------------+" << endl;

        //REPARTO 10 CARTAS AL MAZO
        cout << endl;
        //cout << "Cartas del mazo" << endl;

        for (int x = 1; x <= 10; x++)
        {
            do
            {
                filaMazo = (rand() % 5);             // Genera un n�mero aleatorio entre 0 y 4
                columnaMazo = (rand() % 4);           //Genera n�mero aleatorio entre 0 y 3
            }
            while (matrizElementos[filaMazo][columnaMazo] != 0);   // Asegura que la carta no se haya tomado antes

            // Muestra la carta que se le asigna al mazo
            //cout << "Carta nro : " << x << " del mazo es: " << matrizCartas[filaMazo][columnaMazo] << endl;

            matrizElementos[filaMazo][columnaMazo]++; // Registra que esta carta ha sido tomada

            cartasDelMazo[x - 1] = matrizCartas[filaMazo][columnaMazo];
        }

        cout << endl;


        //MANO GANADORA
        bool ganoElJugador1;
        bool ganoElJugador2;
        int tamManoJugador = 5;
        int tamMazo = 10;

        ganoElJugador1 = determinarSiGanoElJugador(manoJugador1, tamManoJugador);
        ganoElJugador2 = determinarSiGanoElJugador(manoJugador2, tamManoJugador);


        if(ganoElJugador1 == true || ganoElJugador2 == true)
        {
            cout << "Alguno de los dos jugadores empezo con la mano ganadora, se deben repartir las cartas nuevamente" << endl;

        }
        //else if(ganoElJugador1 == false || ganoElJugador2 == false)
        //{
        //    cout << "Se puede arrancar tranquilamente" << endl;
        //}


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
        string manoJugadorQueEmpieza[5];
        string manoJugadorQueNoEmpieza[5];

        //SEGUN QUIEN EMPIECE ES COMO VOY A CARGAR NUEVOS VECTORES

        if(acumulador_jugador1 > acumulador_jugador2)
        {

            quienEmpieza = jugador1;
            quienNoEmpieza = jugador2;

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




        do
        {
                cout << endl;
                cout << "CLUTCH" << endl;
                cout << "------------------------------------------------------------------------" << endl;
                cout << "RONDA #" << ronda << endl;
                cout << jugador1 << " vs " << jugador2;
                cout << endl << endl;
                cout << "TURNO DE " << quienEmpieza << endl;

                cout << endl;
                cout << endl;


                cout << quienEmpieza << endl;

                for(int x = 0; x < 5; x++){

                    cout << manoJugadorQueEmpieza[x] << endl;

                }

                    cout << endl;

                    cout << quienNoEmpieza << endl;

                for(int x = 0; x < 5; x++){

                    cout << manoJugadorQueNoEmpieza[x] << endl;

                }



                // Se realiza el lanzamiento de dado

                int dado = 1;

                cout << endl;
                cout << "LANZAMIENTO DADO #" << dado << endl;


                int cartaCorral, cartaCorralPropio, cartaCorralContrario, cartaCorralPropio1, cartaCorralPropio2;
                string auxiliar;



                //OPCION DADO 1 JUGADOR QUE EMPIEZA

                if(dado == 1)
                {
                    accionDado1(manoJugadorQueEmpieza,cartasDelMazo);

                }

                //OPCION DADO 2 JUGADOR QUE EMPIEZA

                if(dado == 2)
                {
                    cout << "Ingrese la carta del corral contrario a intercambiar con el mazo" << endl;
                    cin >> cartaCorral;

                    accionDado2(manoJugadorQueNoEmpieza, cartasDelMazo);
                }

                //OPCION DADO 3 JUGADOR QUE EMPIEZA

                if(dado == 3)
                {
                    accionDado3(manoJugadorQueEmpieza, manoJugadorQueNoEmpieza);
                }

                //OPCION DADO 4 JUGADOR QUE EMPIEZA

                if(dado == 4)
                {
                    accionDado4(manoJugadorQueEmpieza);
                }

                //OPCION DADO 5 JUGADOR QUE EMPIEZA

                if(dado == 5)
                {
                    accionDado5(manoJugadorQueEmpieza);

                    for(int x = 0; x < 5; x++){
                        cout << manoJugadorQueEmpieza[x] << endl;
                    }
                }

                //OPCION DADO 6 JUGADOR QUE EMPIEZA

                if(dado == 6){

                }


                //ACA TERMINA EL TURNO DEL JUGADOR QUE EMPIEZA


                //SE MEZCLA EL MAZO DESPUES DEL TURNO DEL JUGADOR QUE EMPIEZA

                int tam = 10;
                mezclarMazo(cartasDelMazo, tam);




                cout << endl;
                cout << "CLUTCH" << endl;
                cout << "------------------------------------------------------------------------" << endl;
                cout << "RONDA #" << ronda << endl;
                cout << jugador1 << " vs " << jugador2;
                cout << endl << endl;
                cout << "TURNO DE " << quienNoEmpieza << endl;
                cout << endl;
                cout << endl;


                cout << quienEmpieza << endl;

                for(int x = 0; x < 5; x++){

                    cout << manoJugadorQueEmpieza[x] << endl;

                }

                    cout << endl;

                    cout << quienNoEmpieza << endl;

                for(int x = 0; x < 5; x++){

                    cout << manoJugadorQueNoEmpieza[x] << endl;

                }

            ganoElJugador1 = determinarSiGanoElJugador(manoJugadorQueEmpieza, tamManoJugador);
            ganoElJugador2 = determinarSiGanoElJugador(manoJugadorQueNoEmpieza, tamManoJugador);

                // Se realiza el lanzamiento de dado

                dado = 1;

                cout << endl;
                cout << "LANZAMIENTO DADO #" << dado << endl;

                //OPCION DADO 1 JUGADOR QUE NO EMPIEZA

                if(dado == 1)
                {
                    accionDado1(manoJugadorQueNoEmpieza,cartasDelMazo);

                }

                //OPCION DADO 2 JUGADOR QUE NO EMPIEZA


                if(dado == 2)
                {
                    cout << "Ingrese la carta del corral contrario a intercambiar con el mazo" << endl;
                    cin >> cartaCorral;

                    accionDado2(manoJugadorQueEmpieza, cartasDelMazo);
                }

                //OPCION DADO 3 JUGADOR QUE NO EMPIEZA
                if(dado == 3)
                {
                    accionDado3(manoJugadorQueNoEmpieza, manoJugadorQueEmpieza);
                }
                if(dado == 4)
                {
                    accionDado4(manoJugadorQueNoEmpieza);
                }
                if(dado == 5)
                {
                    accionDado5(manoJugadorQueNoEmpieza);
                }

                //ACA TERMINA EL TURNO DEL JUGADOR QUE NO EMPIEZA


                //MUESTRO CARTAS DESPUES DE QUE JUEGUE EL JUGADOR QUE NO EMPIEZA



            ronda++;

            //DESPUES DE CADA RONDA INTENTO DETERMINAR SI ALGUNO DE LOS DOS JUGADORES GAN� COMPARANDO CON LA MANO GANADORA

            ganoElJugador1 = determinarSiGanoElJugador(manoJugadorQueEmpieza, tamManoJugador);
            ganoElJugador2 = determinarSiGanoElJugador(manoJugadorQueNoEmpieza, tamManoJugador);



        }while(ganoElJugador1 == false || ganoElJugador2 == false);
    }

    //ESTAD�STICAS

    if(menuOpciones == 2)
    {

        cout << "Aqui se muestran las estadisticas" << endl;
    }

    //CR�DITOS

    if(menuOpciones == 3)
    {

        cout << "Se muestran apellidos, nombres y legajos de intregantes del equipo";
    }

    //SALIR

    if(menuOpciones == 0)
    {

        cout << "�Est� seguro de que desea salir? (S para s� - N para no)" << endl;
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

        cout << endl << "No se ingres� un n�mero v�lido en el menu principal, por favor ingrese nuevamente" << endl << endl;
        return main();
    }




    system("pause>nul");
    return 0;
}


