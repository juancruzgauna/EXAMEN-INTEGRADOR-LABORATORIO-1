#ifndef DECLARACIONFUNCIONES_H_INCLUDED
#define DECLARACIONFUNCIONES_H_INCLUDED

using namespace std;

//DECLARACIONES DE FUNCIONES

void desplegarMenu();
string asignarNombres();
char confirmarNombresJugadores();
void crearMatricesCartasYSinMezclar(string matrizCartas[][4], string matrizSinMezclar[][4], string carta[], string palo[]);
void repartirCartasAJugadores(int matrizElementos[][4], string matrizCartas[][4], string manoJugador[], int fila, int columna);
void repartirCartasAlMazo(int matrizElementos[][4], string matrizCartas[][4], string cartasDelMazo[], int filaMazo, int columnaMazo);
void mezclar(string matrizCartas[][4]);
void mezclarMazo(string cartasDelMazo[], int tam);
int determinarQuienEmpieza(string manoJugador[], string matrizSinMezclar[][4]);
int tirardado();
bool determinarSiGanoElJugador(string manoJugador[], string matrizSinMezclar[][4], int tam);


//FUNCIONES DADO

void accionDado1(string manoJugador[], string cartasDelMazo[]);
void accionDado2(string manoJugador[],string cartasDelMazo[], int cartaCorral);
void accionDado3(string manoJugadorQueNoEmpieza[], string manoJugadorQueEmpieza[], int cartaCorralPropio, int cartaCorralContrario, bool manoJugadorContrarioSinCartasBloqueadas[]);
void accionDado4(string manoJugadorQueEmpieza[], bool manoJugadorSinCartasBloqueadas[]);
void accionDado5(bool manoJugadorSinCartasBloqueadas[]);
int accionDado6();

//FUNCION CARTAS MAL UBICADAS EN LA MANO DEL JUGADOR

int cuantasCartasMalUbicadas(string manoJugador[], string matrizSinMezclar[][4], int tam);


#endif // DECLARACIONFUNCIONES_H_INCLUDED
