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
    int menuOpciones, ronda = 1, partida = 1;
    //VARIABLES PARA DETERMINAR SI PASARON LOS JUGADORES (ACCION DADO 6)
    bool pasoElJugadorQueEmpieza = false, pasoElJugadorQueNoEmpieza = false;
    bool sufrioRoboQuienEmpieza = false, sufrioRoboQuienNoEmpieza = false;
    char confirmarSalir, confirmarNombres;
    string jugador1, jugador2;
    int puntosPorCartasMalUbicadasDelJugador1 = 0, puntosPorCartasMalUbicadasDelJugador2 = 0;

    //ACUMULADOR PUNTOS DE VICTORIA TOTALES
    int puntosDeVictoriajugador1, puntosDeVictoriajugador2;

    if(partida == 1)
    {
        puntosDeVictoriajugador1 = 0;
        puntosDeVictoriajugador2 = 0;
    }



    desplegarMenu();
    cin >> menuOpciones;
    cin.ignore();
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

        cout << "+-------------------------+" << endl;
        cout << jugador1 << endl;
        for (int x = 1; x <= 5; x++)
        {
            do
            {
                fila1 = (rand() % 5);             // Genera un número aleatorio entre 0 y 4
                columna1 = (rand() % 4);             // Genera un número aleatorio entre 0 y 3
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
                fila2 = (rand() % 5);             // Genera un número aleatorio entre 0 y 4
                columna2 = (rand() % 4);           //Genera número aleatorio entre 0 y 3
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
                filaMazo = (rand() % 5);             // Genera un número aleatorio entre 0 y 4
                columnaMazo = (rand() % 4);           //Genera número aleatorio entre 0 y 3
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

        ganoElJugador1 = determinarSiGanoElJugador(manoJugador1, matrizSinMezclar, tamManoJugador);
        ganoElJugador2 = determinarSiGanoElJugador(manoJugador2, matrizSinMezclar, tamManoJugador);


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
        bool manoJugador1SinCartasBloqueadas[5] = {false};
        bool manoJugador2SinCartasBloqueadas[5] = {false};

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

            for(int x = 0; x < 5; x++)
            {

                cout << manoJugadorQueEmpieza[x] << endl;

            }

            cout << endl;

            cout << quienNoEmpieza << endl;

            for(int x = 0; x < 5; x++)
            {

                cout << manoJugadorQueNoEmpieza[x] << endl;

            }



            // Se realiza el lanzamiento de dado

            int dado = tirardado();

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

                while(manoJugador2SinCartasBloqueadas[cartaCorral - 1] == true)
                {

                    cout << "No puedes elegir la carta porque está bloqueada por el contrario" << endl;
                    cout << "Elije otra carta por favor: " << endl;
                    cin >> cartaCorral;
                }
                accionDado2(manoJugadorQueNoEmpieza, cartasDelMazo, cartaCorral);
            }

            //OPCION DADO 3 JUGADOR QUE EMPIEZA

            if(dado == 3)
            {
                cout << "Ingrese la carta del corral propio (1-5) para intercambiar por la del corral del contrario (1-5)" << endl;
                cout << "Carta del corral propio: " << endl;
                cin >> cartaCorralPropio;
                cout << endl;
                cout << "Carta del corral contrario: " << endl;
                cin >> cartaCorralContrario;

                while (manoJugador2SinCartasBloqueadas[cartaCorralContrario - 1] == true)
                {

                    cout << "No puedes elegir la carta porque está bloqueada por el contrario" << endl;

                    cout << "Elije otra carta por favor: " << endl;

                    cin >> cartaCorralContrario;
                }
                accionDado3(manoJugadorQueEmpieza, manoJugadorQueNoEmpieza, cartaCorralPropio, cartaCorralContrario);

                sufrioRoboQuienNoEmpieza = true;

            }

            //OPCION DADO 4 JUGADOR QUE EMPIEZA

            if(dado == 4)
            {
                accionDado4(manoJugadorQueEmpieza, manoJugador1SinCartasBloqueadas);
            }

            //OPCION DADO 5 JUGADOR QUE EMPIEZA

            if(dado == 5)
            {
                accionDado5(manoJugador1SinCartasBloqueadas);

            }

            //OPCION DADO 6 JUGADOR QUE EMPIEZA

            if(dado == 6)
            {

                int opcionDevuelta = accionDado6();

                switch(opcionDevuelta)
                {

                case 1:
                    accionDado1(manoJugadorQueEmpieza,cartasDelMazo);
                    break;
                case 2:
                    cout << "Ingrese la carta del corral contrario a intercambiar con el mazo" << endl;
                    cin >> cartaCorral;

                    while(manoJugador2SinCartasBloqueadas[cartaCorral - 1] == true)
                    {

                        cout << "No puedes elegir la carta porque está bloqueada por el contrario" << endl;
                        cout << "Elije otra carta por favor: " << endl;
                        cin >> cartaCorral;
                    }

                    accionDado2(manoJugadorQueNoEmpieza, cartasDelMazo, cartaCorral);
                    break;
                case 3:

                    cout << "Ingrese la carta del corral propio (1-5) para intercambiar por la del corral del contrario (1-5)" << endl;
                    cout << "Carta del corral propio: " << endl;
                    cin >> cartaCorralPropio;
                    cout << endl;
                    cout << "Carta del corral contrario: " << endl;
                    cin >> cartaCorralContrario;

                    while (manoJugador2SinCartasBloqueadas[cartaCorralContrario - 1] == true)
                    {

                        cout << "No puedes elegir la carta porque está bloqueada por el contrario" << endl;

                        cout << "Elije otra carta por favor: " << endl;

                        cin >> cartaCorralContrario;

                    }

                    accionDado3(manoJugadorQueEmpieza, manoJugadorQueNoEmpieza, cartaCorralPropio, cartaCorralContrario);
                    break;
                case 4:
                    accionDado4(manoJugadorQueEmpieza, manoJugador1SinCartasBloqueadas);
                    break;
                case 5:
                    accionDado5(manoJugador1SinCartasBloqueadas);

                    break;
                case 6:
                    cout << "El jugador pasó de turno" << endl;
                    pasoElJugadorQueEmpieza = true;
                    break;
                default:
                    cout << "No se ingreso un número válido" << endl;
                    break;
                }
            }


            //ACA TERMINA EL TURNO DEL JUGADOR QUE EMPIEZA


            //SE MEZCLA EL MAZO DESPUES DEL TURNO DEL JUGADOR QUE EMPIEZA

            ganoElJugador1 = determinarSiGanoElJugador(manoJugadorQueEmpieza, matrizSinMezclar, tamManoJugador);
            ganoElJugador2 = determinarSiGanoElJugador(manoJugadorQueNoEmpieza, matrizSinMezclar, tamManoJugador);

            if(ganoElJugador1 == true)
            {
                break;
            }

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

            for(int x = 0; x < 5; x++)
            {

                cout << manoJugadorQueEmpieza[x] << endl;

            }

            cout << endl;

            cout << quienNoEmpieza << endl;

            for(int x = 0; x < 5; x++)
            {

                cout << manoJugadorQueNoEmpieza[x] << endl;

            }





            // Se realiza el lanzamiento de dado

            dado = tirardado();

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

                while(manoJugador1SinCartasBloqueadas[cartaCorral - 1] == true)
                {

                    cout << "No puedes elegir la carta porque está bloqueada por el contrario" << endl;
                    cout << "Elije otra carta por favor: " << endl;
                    cin >> cartaCorral;
                }
                accionDado2(manoJugadorQueEmpieza, cartasDelMazo, cartaCorral);
            }

            //OPCION DADO 3 JUGADOR QUE NO EMPIEZA
            if(dado == 3)
            {
                cout << "Ingrese la carta del corral propio (1-5) para intercambiar por la del corral del contrario (1-5)" << endl;
                cout << "Carta del corral propio: " << endl;
                cin >> cartaCorralPropio;
                cout << endl;
                cout << "Carta del corral contrario: " << endl;
                cin >> cartaCorralContrario;

                while (manoJugador1SinCartasBloqueadas[cartaCorralContrario - 1] == true)
                {

                    cout << "No puedes elegir la carta porque está bloqueada por el contrario" << endl;

                    cout << "Elije otra carta por favor: " << endl;

                    cin >> cartaCorralContrario;
                }
                accionDado3(manoJugadorQueNoEmpieza, manoJugadorQueEmpieza, cartaCorralPropio, cartaCorralContrario);

                sufrioRoboQuienEmpieza = true;

            }
            if(dado == 4)
            {
                accionDado4(manoJugadorQueNoEmpieza, manoJugador2SinCartasBloqueadas);
            }
            if(dado == 5)
            {
                accionDado5(manoJugador2SinCartasBloqueadas);
            }

            if(dado == 6)
            {

                int opcionDevuelta = accionDado6();

                switch(opcionDevuelta)
                {

                case 1:
                    accionDado1(manoJugadorQueNoEmpieza,cartasDelMazo);
                    break;
                case 2:
                    cout << "Ingrese la carta del corral contrario a intercambiar con el mazo" << endl;
                    cin >> cartaCorral;

                    while(manoJugador1SinCartasBloqueadas[cartaCorral - 1] == true)
                    {

                        cout << "No puedes elegir la carta porque está bloqueada por el contrario" << endl;
                        cout << "Elije otra carta por favor: " << endl;
                        cin >> cartaCorral;
                    }

                    accionDado2(manoJugadorQueEmpieza, cartasDelMazo, cartaCorral);
                    break;
                case 3:

                    cout << "Ingrese la carta del corral propio (1-5) para intercambiar por la del corral del contrario (1-5)" << endl;
                    cout << "Carta del corral propio: " << endl;
                    cin >> cartaCorralPropio;
                    cout << endl;
                    cout << "Carta del corral contrario: " << endl;
                    cin >> cartaCorralContrario;

                    while (manoJugador1SinCartasBloqueadas[cartaCorralContrario - 1] == true)
                    {

                        cout << "No puedes elegir la carta porque está bloqueada por el contrario" << endl;

                        cout << "Elije otra carta por favor: " << endl;

                        cin >> cartaCorralContrario;

                    }

                    accionDado3(manoJugadorQueNoEmpieza, manoJugadorQueEmpieza, cartaCorralPropio, cartaCorralContrario);
                    break;
                case 4:
                    accionDado4(manoJugadorQueNoEmpieza, manoJugador2SinCartasBloqueadas);
                    break;
                case 5:
                    accionDado5(manoJugador2SinCartasBloqueadas);

                    break;
                case 6:
                    cout << "El jugador pasó de turno" << endl;
                    pasoElJugadorQueNoEmpieza = true;
                    break;
                default:
                    cout << "No se ingreso un número válido" << endl;
                    break;
                }
            }


            //ACA TERMINA EL TURNO DEL JUGADOR QUE NO EMPIEZA


            //MUESTRO CARTAS DESPUES DE QUE JUEGUE EL JUGADOR QUE NO EMPIEZA



            ronda++;


            //DESPUES DE CADA RONDA INTENTO DETERMINAR SI ALGUNO DE LOS DOS JUGADORES GANÓ COMPARANDO CON LA MANO GANADORA

            ganoElJugador1 = determinarSiGanoElJugador(manoJugadorQueEmpieza, matrizSinMezclar, tamManoJugador);
            ganoElJugador2 = determinarSiGanoElJugador(manoJugadorQueNoEmpieza, matrizSinMezclar, tamManoJugador);




        }while(ganoElJugador1 == false && ganoElJugador2 == false);

        //MUESTRO COMO QUEDARON LAS MANOS FINALES

        cout << quienEmpieza << endl;

        for(int x = 0; x < 5; x++)
        {

            cout << manoJugadorQueEmpieza[x] << endl;

        }

        cout << endl;

        cout << quienNoEmpieza << endl;

        for(int x = 0; x < 5; x++)
        {

            cout << manoJugadorQueNoEmpieza[x] << endl;

        }


        cout << "Se termino la partida: " << endl;

        string ganadorDeLaPartida;

        //DECLARO VARIABLES DE LOS PUNTOS DE VICTORIA

        int puntosDeVictoriaQuienEmpieza = 0, puntosDeVictoriaQuienNoEmpieza = 0;

        //PUNTOS DE VICTORIAS SEGUN QUIEN GANA

        //QUIEN EMPIEZA

        if(ganoElJugador1 == true)
        {
            //PUNTOS DE VICTORIA POR HABER GANADO LA PARTIDA

            puntosDeVictoriaQuienEmpieza += 15;

            //PUNTOS DE VICTORIA POR NO HABER PASADO DE TURNO

            if(pasoElJugadorQueEmpieza == false)
            {
                puntosDeVictoriaQuienEmpieza += 10;
            }

            //PUNTOS DE VICTORIA POR NO HABER SUFRIDO ROBO DEL CONTRARIO (ACCION DADO 3)

            if(sufrioRoboQuienEmpieza == false)
            {
                puntosDeVictoriaQuienEmpieza += 5;
            }

            //PUNTOS POR CARTAS MAL UBICADAS DEL CONTRARIO

            puntosPorCartasMalUbicadasDelJugador2 = cuantasCartasMalUbicadas(manoJugadorQueNoEmpieza, matrizSinMezclar, tamManoJugador);

            puntosDeVictoriaQuienEmpieza += puntosPorCartasMalUbicadasDelJugador2;

            //PUNTOS POR GANAR LA PARTIDA ROBANDOLE LA ÚLTIMA CARTA AL RIVAL (ACCION DADO 3)

            int dado;

            if(dado == 3)
            {
                puntosDeVictoriaQuienEmpieza += 10;
            }

            ganadorDeLaPartida = quienEmpieza;
            cout << "El ganador de la partida es: " << ganadorDeLaPartida << endl;
        }
        //QUIEN NO EMPIEZA
        else
        {
            //PUNTOS DE VICTORIA POR HABER GANADO LA PARTIDA

            puntosDeVictoriaQuienNoEmpieza += 15;

            //PUNTOS DE VICTORIA POR NO HABER PASADO DE TURNO

            if(pasoElJugadorQueNoEmpieza == false)
            {
                puntosDeVictoriaQuienNoEmpieza += 10;
            }

            //PUNTOS DE VICTORIA POR NO HABER SUFRIDO ROBO DEL CONTRARIO (ACCION DADO 3)

            if(sufrioRoboQuienNoEmpieza == false)
            {
                puntosDeVictoriaQuienNoEmpieza += 5;
            }

            //PUNTOS POR CARTAS MAL UBICADAS DEL CONTRARIO

            puntosPorCartasMalUbicadasDelJugador1 = cuantasCartasMalUbicadas(manoJugadorQueEmpieza, matrizSinMezclar, tamManoJugador);

            puntosDeVictoriaQuienNoEmpieza += puntosPorCartasMalUbicadasDelJugador1;

            //PUNTOS POR GANAR LA PARTIDA ROBANDOLE LA ÚLTIMA CARTA AL RIVAL (ACCION DADO 3)

            int dado;

            if(dado == 3)
            {
                puntosDeVictoriaQuienNoEmpieza += 10;
            }


            ganadorDeLaPartida = quienNoEmpieza;
            cout << "El ganador de la partida es: " << ganadorDeLaPartida << endl;
        }

        //PUNTOS DE VICTORIA JUGADOR 1

        int puntosDeVictoriajugador1 = 0;

        if(quienEmpieza == jugador1)
        {
            puntosDeVictoriajugador1 = puntosDeVictoriaQuienEmpieza;

        }
        else if(quienNoEmpieza == jugador1)
        {
            puntosDeVictoriajugador1 = puntosDeVictoriaQuienNoEmpieza;
        }

        if(quienEmpieza == jugador2)
        {
            puntosDeVictoriajugador2 = puntosDeVictoriaQuienEmpieza;

        }
        else if(quienNoEmpieza == jugador1)
        {
            puntosDeVictoriajugador2 = puntosDeVictoriaQuienNoEmpieza;
        }





        //PUNTOS DE VICTORIA

        cout << "CLUTCH" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << ganadorDeLaPartida << endl << endl;
        cout << "HITO" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << "Ganar la partida: " << endl;
        cout << "Robo última carta al jugador rival: " << endl;
        cout << "Cartas mal ubicadas del rival x 4: " << endl;
        cout << "Sin pasar de turno: " << endl;
        cout << "Sin haber sufrido un robo del rival: " << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << "TOTAL" << endl;
        cout << "GANADOR: " << ganadorDeLaPartida << endl;

        if(ganadorDeLaPartida == jugador1)
        {
            cout << "El jugador obtuvo: " << puntosDeVictoriajugador1 << " puntos de victoria" << endl;
        }
        else if(ganadorDeLaPartida == jugador2)
        {
            cout << "El jugador obtuvo: " << puntosDeVictoriajugador2 << " puntos de victoria" << endl;
        }



        partida++;
        char jugarOtra;


        cout << "¿Desea jugar otra partida (S/N)?" << endl;
        cin >> jugarOtra;

        if(jugarOtra == 'S' || jugarOtra == 's')
        {
            return main();
        }
    }
    //ACA TERMINA LA OPCION JUGAR


    //ESTADÍSTICAS

    if(menuOpciones == 2)
    {

        cout << "Aqui se muestran las estadisticas" << endl;
    }

    //ACA TERMINA LA OPCION ESTADÍSTICAS

    //CRÉDITOS

    if(menuOpciones == 3)
    {

        cout << "Se muestran apellidos, nombres y legajos de intregantes del equipo";
    }

    //ACA TERMINA LA OPCION CRÉDITOS

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


