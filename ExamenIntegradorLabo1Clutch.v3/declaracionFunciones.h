#ifndef DECLARACIONFUNCIONES_H_INCLUDED
#define DECLARACIONFUNCIONES_H_INCLUDED

using namespace std;

//DECLARACIONES DE FUNCIONES

void desplegarMenu();
string asignarNombres();
char confirmarNombresJugadores();
void mezclar(string matrizCartas[][4]);
int tirardado();
bool determinarSiGanoElJugador(string manoJugador[], int tam);
void mezclarMazo(string cartasDelMazo[], int tam);

//FUNCIONES DADO

void accionDado1(string manoJugador[], string cartasDelMazo[]);
void accionDado2(string manoJugador[],string cartasDelMazo[]);
void accionDado3(string manoJugadorQueNoEmpieza[], string manoJugadorQueEmpieza[]);
void accionDado4(string manoJugadorQueEmpieza[]);
void accionDado5(string manoJugador[]);
int accionDado6();


#endif // DECLARACIONFUNCIONES_H_INCLUDED
