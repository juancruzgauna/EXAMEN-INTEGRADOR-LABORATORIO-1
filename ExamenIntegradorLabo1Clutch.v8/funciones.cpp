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
    string nombreJugador;

    cout << "CLUTCH" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "Antes de comenzar deben registrar sus nombres: " << endl << endl;
    cout << "¿Nombre? ";
    getline(cin, nombreJugador);
    return nombreJugador;

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
//Defino función para crear la matriz cartas y la matriz sin mezclar
void crearMatricesCartasYSinMezclar(string matrizCartas[][4], string matrizSinMezclar[][4], string carta[], string palo[]){

    for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matrizCartas[i][j] = carta[i] + palo[j];
                matrizSinMezclar[i][j] = carta[i] + palo[j];
            }
        }
}

void repartirCartasAJugadores(int matrizElementos[][4], string matrizCartas[][4], string manoJugador[], int fila, int columna){

    srand(time(0));

    for (int x = 1; x <= 5; x++)
        {
            do
            {
                fila = (rand() % 5);             // Genera un número aleatorio entre 0 y 4
                columna = (rand() % 4);             // Genera un número aleatorio entre 0 y 3
            }
            while (matrizElementos[fila][columna] != 0);   // Asegura que la carta no se haya tomado antes

            matrizElementos[fila][columna]++;// Registra que esta carta ha sido tomada

            manoJugador[x - 1] = matrizCartas[fila][columna];
        }
}

void repartirCartasAlMazo(int matrizElementos[][4], string matrizCartas[][4], string cartasDelMazo[], int filaMazo, int columnaMazo){

    for (int x = 1; x <= 10; x++)
        {
            do
            {
                filaMazo = (rand() % 5);             // Genera un número aleatorio entre 0 y 4
                columnaMazo = (rand() % 4);           //Genera número aleatorio entre 0 y 3
            }
            while (matrizElementos[filaMazo][columnaMazo] != 0);   // Asegura que la carta no se haya tomado antes

            matrizElementos[filaMazo][columnaMazo]++; // Registra que esta carta ha sido asignada al mazo

            cartasDelMazo[x - 1] = matrizCartas[filaMazo][columnaMazo];
        }
}

// Defino función mezclar cartas tipo matriz
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

void mezclarMazo(string cartasDelMazo[], int tam)
{

    srand(time(0));
    int m;
    for(int x = 0; x < tam; x++)
    {
        m = rand() % 10;
        swap(cartasDelMazo[x], cartasDelMazo[m]);
    }
}

int determinarQuienEmpieza(string manoJugador[], string matrizSinMezclar[][4]){

    int acumulador_jugador = 0;

    for (int x = 0; x < 5; x++)
        {
            for (int y = 0; y < 4; y++)
            {
                if (manoJugador[x] == matrizSinMezclar[4][y])
                {
                    acumulador_jugador += 625;
                }
                else if (manoJugador[x] == matrizSinMezclar[3][y])
                {
                    acumulador_jugador += 125;
                }
                else if (manoJugador[x] == matrizSinMezclar[2][y])
                {
                    acumulador_jugador += 25;
                }
                else if(manoJugador[x] == matrizSinMezclar[1][y])
                {
                    acumulador_jugador += 5;
                }
                else if(manoJugador[x] == matrizSinMezclar[0][y])
                {
                    acumulador_jugador += 1;
                }
            }
        }

    return acumulador_jugador;
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

bool determinarSiGanoElJugador(string manoJugador[], string matrizSinMezclar[][4], int tam)
{
    int contador = 0;

    for (int y = 0; y < 4; y++)
    {
        //ACA PREGUNTO POR LOS DIEZ
        if (manoJugador[0] == matrizSinMezclar[0][y])
        {
            contador++;
        }
        //ACA PREGUNTO POR LAS JOTAS
        if (manoJugador[1] == matrizSinMezclar[1][y])

        {
            contador++;
        }
        //ACA PREGUNTO POR LAS QUS
        if (manoJugador[2] == matrizSinMezclar[2][y])
        {
            contador++;
        }
        //ACA PREGUNTO POR LAS KAS
        if(manoJugador[3] == matrizSinMezclar[3][y])
        {
            contador++;
        }
        //ACA PREGUNTO POR LAS ASES
        if(manoJugador[4] == matrizSinMezclar[4][y])
        {
            contador++;
        }
    }


    if(contador == 5)
    {
        return true;
    }
    return false;
}

//FUNCIONES PARA LOS DADOS

//FUNCION DADO 1

void accionDado1(string manoJugador[], string cartasDelMazo[])
{
    int cartaCorral;
    string auxiliar;

    cout << "Ingrese carta del corral a intercambiar con el mazo (1-5) :" << endl;
    cin >> cartaCorral;

    while(cartaCorral < 1 || cartaCorral > 5){
            cout << "No se ingresó un valor correcto de carta corral, recuerde que es un valor de 1 a 5" << endl;
            cout << "Ingrese carta del corral a intercambiar con el mazo (1-5) :" << endl;
            cin >> cartaCorral;
          }

    auxiliar = manoJugador[cartaCorral - 1];
    manoJugador[cartaCorral - 1] = cartasDelMazo [0];
    cartasDelMazo[0] = auxiliar;
}

//FUNCION DADO 2

void accionDado2(string manoJugador[],string cartasDelMazo[], int cartaCorral)
{
    string auxiliar;

    auxiliar = manoJugador[cartaCorral - 1];
    manoJugador[cartaCorral - 1] = cartasDelMazo[0];
    cartasDelMazo[0] = auxiliar;
}
//FUNCION DADO 3
void accionDado3(string manoJugadorQueNoEmpieza[], string manoJugadorQueEmpieza[], int cartaCorralPropio, int cartaCorralContrario)
{

    string auxiliar;

    auxiliar = manoJugadorQueNoEmpieza[cartaCorralPropio - 1];
    manoJugadorQueNoEmpieza[cartaCorralPropio - 1] = manoJugadorQueEmpieza[cartaCorralContrario - 1];
    manoJugadorQueEmpieza[cartaCorralContrario - 1] = auxiliar;
}
// FUNCION DADO 4
void accionDado4(string manoJugadorQueEmpieza[], bool manoJugadorSinCartasBloqueadas[])
{
    int cartaCorralPropio1, cartaCorralPropio2;
    string auxiliar;
    bool auxiliar2;
    cout << "Ingrese primer carta del corral a intercambiar" << endl;
    cin >> cartaCorralPropio1;

    while(cartaCorralPropio1 < 1 || cartaCorralPropio1 > 5){
        cout << "No se ingresó un valor correcto de carta, recuerde que es un número del 1 al 5" << endl;
        cout << "Ingrese primer carta del corral a intercambiar" << endl;
        cin >> cartaCorralPropio1;
    }
    cout << "Ingrese segunda carta del corral a intercambiar" << endl;
    cin >> cartaCorralPropio2;

    while(cartaCorralPropio2 < 1 || cartaCorralPropio2 > 5){
        cout << "No se ingresó un valor correcto de carta, recuerde que es un número del 1 al 5" << endl;
        cout << "Ingrese segunda carta del corral a intercambiar" << endl;
        cin >> cartaCorralPropio2;
    }

    while(cartaCorralPropio1 == cartaCorralPropio2){
        cout << "Esa carta ya fue seleccionada, elija una diferente para intercambiar" << endl;
        cout << "Ingrese segunda carta del corral a intercambiar" << endl;
        cin >> cartaCorralPropio2;
    }

    auxiliar2 = manoJugadorSinCartasBloqueadas[cartaCorralPropio1 - 1];
    manoJugadorSinCartasBloqueadas[cartaCorralPropio1 - 1] = manoJugadorSinCartasBloqueadas[cartaCorralPropio2 - 1];
    manoJugadorSinCartasBloqueadas[cartaCorralPropio2 - 1] = auxiliar2;


    auxiliar = manoJugadorQueEmpieza[cartaCorralPropio1 - 1];
    manoJugadorQueEmpieza[cartaCorralPropio1 - 1] = manoJugadorQueEmpieza[cartaCorralPropio2 - 1];
    manoJugadorQueEmpieza[cartaCorralPropio2 - 1] = auxiliar;
}
//FUNCION DADO 5
void accionDado5(bool manoJugadorSinCartasBloqueadas[])
{
    int cartaCorral;
    cout << "Ingrese la carta del corral a bloquear (1-5): " << endl;
    cin >> cartaCorral;

    manoJugadorSinCartasBloqueadas[cartaCorral - 1] = true;
}

//FUNCION DADO 6

int accionDado6()
{

    int dado;

    cout << "Elija la opcion que quiere realizar(1-5) o bien pasar de turno (6): " << endl;

    //MOSTRAR EN PANTALLA TODAS LAS OPCIONES
    cin >> dado;

    return dado;
}

int cuantasCartasMalUbicadas(string manoJugador[], string matrizSinMezclar[][4], int tam)
{
    int contador = 5;
    int resultado;

    for (int y = 0; y < 4; y++)
    {
        //ACA PREGUNTO POR LOS DIEZ
        if (manoJugador[0] == matrizSinMezclar[0][y])
        {
            contador--;
        }
        //ACA PREGUNTO POR LAS JOTAS
        if (manoJugador[1] == matrizSinMezclar[1][y])

        {
            contador--;
        }
        //ACA PREGUNTO POR LAS QUS
        if (manoJugador[2] == matrizSinMezclar[2][y])
        {
            contador--;
        }
        //ACA PREGUNTO POR LAS KAS
        if(manoJugador[3] == matrizSinMezclar[3][y])
        {
            contador--;
        }
        //ACA PREGUNTO POR LAS ASES
        if(manoJugador[4] == matrizSinMezclar[4][y])
        {
            contador--;
        }
    }
    resultado = contador * 5;

    return resultado;
}
