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

    //VARIABLES QUE NO NECESITO QUE SE REINICIEN DESPUES DE CADA PARTIDA

    //PUNTAJE VICTORIA MAXIMO INICIALIZADO EN CERO

    int puntajeVictoriaMaximo = 0;
    string ganadorMaximo = "Aún no hay ganador máximo";


    //VARIABLES ETAPA INICIAL
    int menuOpciones;

    char confirmarSalir, confirmarNombres;
    string jugador1, jugador2;
    int fila1, columna1, fila2, columna2, filaMazo, columnaMazo;
    int dado;

    //DECLARACION DE MATRICES Y VECTORES

    string matrizCartas[5][4];
    string matrizSinMezclar[5][4];
    int matrizElementos[5][4] = {};
    string carta[5] = {"10", "J", "Q", "K", "A"};
    string palo[4] = {" de Picas ", " de Diamantes", " de Corazones ", " de Tréboles "};

    //DECLARO LAS MANOS DE AMBOS JUGADORES COMO VECTORES DE STRING

    string manoJugador1[5];
    string manoJugador2[5];
    string cartasDelMazo[10];

    //VARIABLES PARA DETERMINAR SI ALGUN JUGADOR COMENZÓ CON LA MANO GANADORA

    int tamManoJugador = 5, tamMazo = 10;

    //VARIABLES FINAL DE PARTIDA
    int puntosDeVictoriajugador1, puntosDeVictoriajugador2;
    char jugarOtra;

    menuOpciones = 5;

    while(menuOpciones == 5){


    desplegarMenu();
    cin >> menuOpciones;
    cin.ignore();
    cout << endl;

    while(menuOpciones == 1)
    {

    int ronda = 1;
    int acumulador_jugador1 = 0, acumulador_jugador2 = 0;
    bool ganoElJugador1, ganoElJugador2;
    bool jugador1ComenzoConManoGanadora = false, jugador2ComenzoConManoGanadora = false;

    //VARIABLES QUE SE USAN DURANTE LA PARTIDA
    bool pasoElJugadorQueEmpieza = false, pasoElJugadorQueNoEmpieza = false;
    bool sufrioRoboQuienEmpieza = false, sufrioRoboQuienNoEmpieza = false;
    int puntosPorCartasMalUbicadasDelJugador = 0;

    //VARIABLES PARA DEFINIR QUIEN COMIENZA LA PARTIDA
    string quienEmpieza, quienNoEmpieza;
    string manoJugadorQueEmpieza[5];
    string manoJugadorQueNoEmpieza[5];

    //VECTOR PARA UTILIZAR EL DADO 5 INICIALIZADO EN FALSE
    bool manoJugador1SinCartasBloqueadas[5] = {false};
    bool manoJugador2SinCartasBloqueadas[5] = {false};

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

        //Utilizo la función que me crea las matrices cartas y sin mezclar combinando los vectores carta y palo

        crearMatricesCartasYSinMezclar(matrizCartas, matrizSinMezclar, carta, palo);

        // Mezclar cartas

        mezclar(matrizCartas);

        cout << endl << endl;


        //REPARTO 5 CARTAS AL JUGADOR 1

        cout << "+-------------------------+" << endl;
        cout << jugador1 << endl;

        repartirCartasAJugadores(matrizElementos, matrizCartas, manoJugador1, fila1, columna1);

        //CARTAS INICIALES JUGADOR 1

        for(int x = 0; x < 5; x++)
        {
            cout << manoJugador1[x] << endl;
        }


        //REPARTO 5 CARTAS AL JUGADOR 2

        cout << "+-------------------------+" << endl;
        cout << jugador2 << endl;

        repartirCartasAJugadores(matrizElementos, matrizCartas, manoJugador2, fila2, columna2);

        cout << "+-------------------------+" << endl;

        //CARTAS INICIALES JUGADOR 2

        for(int x = 0; x < 5; x++)
        {
            cout << manoJugador2[x] << endl;
        }

        //REPARTO 10 CARTAS AL MAZO

        cout << endl;

        repartirCartasAlMazo(matrizElementos, matrizCartas, cartasDelMazo, filaMazo, columnaMazo);

        cout << endl;

        do{

        //ANALIZO SI ALGUNO DE LOS DOS EMPEZÓ CON LA MANO GANADORA (10, J, Q, K, A)

        jugador1ComenzoConManoGanadora = determinarSiGanoElJugador(manoJugador1, matrizSinMezclar, tamManoJugador);
        jugador2ComenzoConManoGanadora = determinarSiGanoElJugador(manoJugador2, matrizSinMezclar, tamManoJugador);

            if(jugador1ComenzoConManoGanadora == true || jugador2ComenzoConManoGanadora == true)
            {
                cout << "Alguno de los dos jugadores empezo con la mano ganadora, se deben repartir las cartas nuevamente" << endl;

            repartirCartasAJugadores(matrizElementos, matrizCartas, manoJugador1, fila1, columna1); //reparto nuevamente cartas a jugador 1
            repartirCartasAJugadores(matrizElementos, matrizCartas, manoJugador2, fila2, columna2); //reparto nuevamente cartas a jugador 2
            }

        }while(jugador1ComenzoConManoGanadora == true || jugador2ComenzoConManoGanadora == true);

        //DETERMINO QUIEN EMPIEZA LA PARTIDA USANDO ACUMULADORES (EL QUE DE UN VALOR MAS ALTO ES EL QUE COMIENZA LA PARTIDA)

        acumulador_jugador1 = determinarQuienEmpieza(manoJugador1, matrizSinMezclar);
        acumulador_jugador2 = determinarQuienEmpieza(manoJugador2, matrizSinMezclar);


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
            repartirCartasAJugadores(matrizElementos, matrizCartas, manoJugador1, fila1, columna1);
            repartirCartasAJugadores(matrizElementos, matrizCartas, manoJugador2, fila2, columna2);
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

            dado = 6;

            cout << endl;
            cout << endl;
            cout << "LANZAMIENTO DADO #" << dado << endl;


            int cartaCorral, cartaCorralPropio, cartaCorralContrario;
            string auxiliar;



            //OPCION DADO 1 JUGADOR QUE EMPIEZA

            if(dado == 1)
            {
                accionDado1(manoJugadorQueEmpieza,cartasDelMazo);

            }

            //OPCION DADO 2 JUGADOR QUE EMPIEZA

            if(dado == 2)
            {
                cout << "Ingrese la carta del corral contrario a intercambiar con el mazo (1-5)" << endl;
                cin >> cartaCorral;


                while(cartaCorral < 1 || cartaCorral > 5){
                    cout << "No se ingresó un valor correcto de carta corral, recuerde que es un valor de 1 a 5" << endl;
                    cout << "Ingrese carta del corral a intercambiar con el mazo (1-5) :" << endl;
                    cin >> cartaCorral;
                }

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
                    cout << "Ingrese la carta del corral contrario a intercambiar con el mazo (1-5)" << endl;
                    cin >> cartaCorral;

                    while(cartaCorral < 1 || cartaCorral > 5){
                        cout << "No se ingresó un valor correcto de carta corral, recuerde que es un valor de 1 a 5" << endl;
                        cout << "Ingrese carta del corral a intercambiar con el mazo (1-5) :" << endl;
                        cin >> cartaCorral;
                    }

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
                    sufrioRoboQuienNoEmpieza = true;
                    dado = 3; // se cambia el valor para los puntos de victoria
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

            if(ganoElJugador1 == true || ganoElJugador2 == true)
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

            dado = 6;

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
                cout << "Ingrese la carta del corral contrario a intercambiar con el mazo (1-5)" << endl;
                cin >> cartaCorral;

                while(cartaCorral < 1 || cartaCorral > 5){
                    cout << "No se ingresó un valor correcto de carta corral, recuerde que es un valor de 1 a 5" << endl;
                    cout << "Ingrese carta del corral a intercambiar con el mazo (1-5) :" << endl;
                    cin >> cartaCorral;
                }

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
                    cout << "Ingrese la carta del corral contrario a intercambiar con el mazo (1-5)" << endl;
                    cin >> cartaCorral;

                    while(cartaCorral < 1 || cartaCorral > 5){
                    cout << "No se ingresó un valor correcto de carta corral, recuerde que es un valor de 1 a 5" << endl;
                    cout << "Ingrese carta del corral a intercambiar con el mazo (1-5) :" << endl;
                    cin >> cartaCorral;
                    }

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
                    sufrioRoboQuienEmpieza = true;
                    dado = 3; // se cambia el valor para los puntos de victoria
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


            ronda++;


            //DESPUES DE CADA RONDA CONSULTO SI ALGUNO DE LOS DOS JUGADORES GANÓ

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
        int pdv_ganarPartida = 0, pdv_robandoUltimaCarta = 0, pdv_turno = 0, pdv_sinSufrirRobo = 0;

        //PUNTOS DE VICTORIAS SEGUN QUIEN GANA

        //QUIEN EMPIEZA

        if(ganoElJugador1 == true)
        {
            //PUNTOS DE VICTORIA POR HABER GANADO LA PARTIDA

            puntosDeVictoriaQuienEmpieza += 15;
            pdv_ganarPartida = 15;

            //PUNTOS DE VICTORIA POR NO HABER PASADO DE TURNO

            if(pasoElJugadorQueEmpieza == false)
            {
                puntosDeVictoriaQuienEmpieza += 10;
                pdv_turno = 10;
            }

            //PUNTOS DE VICTORIA POR NO HABER SUFRIDO ROBO DEL CONTRARIO (ACCION DADO 3)

            if(sufrioRoboQuienEmpieza == false)
            {
                puntosDeVictoriaQuienEmpieza += 5;
                pdv_sinSufrirRobo = 5;
            }

            //PUNTOS POR CARTAS MAL UBICADAS DEL CONTRARIO

            puntosPorCartasMalUbicadasDelJugador = cuantasCartasMalUbicadas(manoJugadorQueNoEmpieza, matrizSinMezclar, tamManoJugador);

            puntosDeVictoriaQuienEmpieza += puntosPorCartasMalUbicadasDelJugador;

            //PUNTOS POR GANAR LA PARTIDA ROBANDOLE LA ÚLTIMA CARTA AL RIVAL (ACCION DADO 3)

            if(dado == 3)
            {
                puntosDeVictoriaQuienEmpieza += 10;
                pdv_robandoUltimaCarta = 10;
            }

            ganadorDeLaPartida = quienEmpieza;
            cout << "El ganador de la partida es: " << ganadorDeLaPartida << endl;
        }
        //QUIEN NO EMPIEZA
        else
        {
            //PUNTOS DE VICTORIA POR HABER GANADO LA PARTIDA

            puntosDeVictoriaQuienNoEmpieza += 15;
            pdv_ganarPartida = 15;

            //PUNTOS DE VICTORIA POR NO HABER PASADO DE TURNO

            if(pasoElJugadorQueNoEmpieza == false)
            {
                puntosDeVictoriaQuienNoEmpieza += 10;
                pdv_turno = 10;
            }

            //PUNTOS DE VICTORIA POR NO HABER SUFRIDO ROBO DEL CONTRARIO (ACCION DADO 3)

            if(sufrioRoboQuienNoEmpieza == false)
            {
                puntosDeVictoriaQuienNoEmpieza += 5;
                pdv_sinSufrirRobo = 5;
            }

            //PUNTOS POR CARTAS MAL UBICADAS DEL CONTRARIO

            puntosPorCartasMalUbicadasDelJugador = cuantasCartasMalUbicadas(manoJugadorQueEmpieza, matrizSinMezclar, tamManoJugador);

            puntosDeVictoriaQuienNoEmpieza += puntosPorCartasMalUbicadasDelJugador;

            //PUNTOS POR GANAR LA PARTIDA ROBANDOLE LA ÚLTIMA CARTA AL RIVAL (ACCION DADO 3)


            if(dado == 3)
            {
                puntosDeVictoriaQuienNoEmpieza += 10;
                pdv_robandoUltimaCarta = 10;
            }


            ganadorDeLaPartida = quienNoEmpieza;
            cout << "El ganador de la partida es: " << ganadorDeLaPartida << endl;
        }


        int puntosDeVictoriajugadorGanador = 0;


        if(quienEmpieza == jugador1)
        {
            puntosDeVictoriajugadorGanador = puntosDeVictoriaQuienEmpieza;

        }
        else if(quienNoEmpieza == jugador1)
        {
            puntosDeVictoriajugadorGanador = puntosDeVictoriaQuienNoEmpieza;
        }

        if(quienEmpieza == jugador2)
        {
            puntosDeVictoriajugadorGanador = puntosDeVictoriaQuienEmpieza;

        }
        else if(quienNoEmpieza == jugador1)
        {
            puntosDeVictoriajugadorGanador = puntosDeVictoriaQuienNoEmpieza;
        }

        //PUNTOS DE VICTORIA

        cout << "CLUTCH" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << ganadorDeLaPartida << endl << endl;
        cout << "HITO" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << "Ganar la partida: " << pdv_ganarPartida << " PDV"<< endl;
        cout << "Robo última carta al jugador rival: " << pdv_robandoUltimaCarta <<" PDV" << endl;
        cout << "Cartas mal ubicadas del rival x" << puntosPorCartasMalUbicadasDelJugador / 5 << ": "<< puntosPorCartasMalUbicadasDelJugador << " PDV"<< endl;
        cout << "Sin pasar de turno: " << pdv_turno << " PDV" << endl;
        cout << "Sin haber sufrido un robo del rival: " << pdv_sinSufrirRobo << " PDV" << endl;
        cout << "------------------------------------------------------------------------" << endl;
        cout << "TOTAL" << endl;
        cout << "GANADOR: " << ganadorDeLaPartida << " con: " << puntosDeVictoriajugadorGanador << " puntos de victoria" << endl;

        //ACA GUARDAMOS TODAS LAS ESTADÍSTICAS
        if(puntajeVictoriaMaximo < puntosDeVictoriajugadorGanador){
            puntajeVictoriaMaximo = puntosDeVictoriajugadorGanador;
            ganadorMaximo = ganadorDeLaPartida;
        }

        //ACA TERMINA LA CAJA DE PROCESO DE ESTADÍSTICAS

        cout << "Presione 5 para volver al menú principal..." << endl << endl;
        cout << "Presione 1 para jugar otra partida..." << endl << endl;
        cout << "Presione 2 para ver estadísticas..." << endl << endl;
        cout << "Presione 3 para ver los créditos..." << endl << endl;
        cout << "Presione 0 para salir..." << endl << endl;

        cin >> menuOpciones;

        }




    //ACA TERMINA LA OPCION JUGAR



    //ESTADÍSTICAS

    if(menuOpciones == 2)
    {

        cout << "Aqui se muestran las estadisticas" << endl;
        cout << "Mejor jugador es: " << ganadorMaximo << " con " << puntajeVictoriaMaximo << endl;

        cout << "Presione 5 para volver al menú principal..." << endl;
        cin >> menuOpciones;

    }

    //ACA TERMINA LA OPCION ESTADÍSTICAS

    //CRÉDITOS

    if(menuOpciones == 3)
    {

        cout << "JUEGO DESARROLLADO POR: " << endl;
        cout << "MARTÍN NAHUEL LOZANO - LEGAJO 27971" << endl;
        cout << "MARÍA ITATÍ ROMERO - LEGAJO 29888" << endl;
        cout << "JUAN CRUZ GAUNA - LEGAJO 28815" << endl << endl;
        cout << "EN EL MARCO DE LA MATERIA LABORATORIO 1 " << endl;
        cout << "UTN FACULTAD REGIONAL GENERAL PACHECO" << endl;

        cout << "Presione 5 para volver al menú principal..." << endl;
        cin >> menuOpciones;

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
            menuOpciones = 5;
        }
    }

    if(menuOpciones != 1 && menuOpciones != 2 && menuOpciones != 3 && menuOpciones != 0 && menuOpciones != 5)
    {

        cout << endl << "No se ingresó un número válido en el menu principal, por favor ingrese nuevamente" << endl << endl;

        menuOpciones = 5;
    }



    }


    system("pause>nul");
    return 0;


}


