#ifndef DECLARACIONFUNCIONES_H_INCLUDED
#define DECLARACIONFUNCIONES_H_INCLUDED

using namespace std;

void desplegarMenu();
string asignarNombres();
char confirmarNombresJugadores();
void mezclar(string matrizCartas[][4]);
int tirardado();
bool determinarSiGanoElJugador(string manoJugador[], string carta[], int tam);

#endif // DECLARACIONFUNCIONES_H_INCLUDED
