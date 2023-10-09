
#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <time.h>
using namespace std;


int main(){
	setlocale(LC_ALL, "spanish");

    //MENU OPCIONES
    int menuOpciones, ronda = 1;
    char confirmarSalir, confirmarNombres;
    string jugador1, jugador2;

    cout << "CLUTCH" << endl;
    cout << "---------------------" << endl;
    cout << "1 - JUGAR" << endl;
    cout << "2 - ESTADÍSTICAS" << endl;
    cout << "3 - CRÉDITOS" << endl;
    cout << "---------------------" << endl;
    cout << "0 - SALIR" << endl;
    cout << endl;
    cin >> menuOpciones;
    cout << endl;

    switch(menuOpciones){

        //JUGAR

        case 1:
            cout << "CLUTCH" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            cout << "Antes de comenzar deben registrar sus nombres: " << endl << endl;
            cout << "¿Nombre? ";
            cin >> jugador1;
            cout << endl;
            cout << "¿Nombre? ";
            cin >> jugador2;
            cout << endl;
            cout << "¿Confirmar nombres? (S/N)" << endl;
            cin >> confirmarNombres;
            cout << "------------------------------------------------------------------------" << endl;

                if(confirmarNombres == 'N' || confirmarNombres == 'n'){

            cout << "CLUTCH" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            cout << "Antes de comenzar deben registrar sus nombres: " << endl << endl;
            cout << "¿Nombre? ";
            cin >> jugador1;
            cout << endl;
            cout << "¿Nombre? ";
            cin >> jugador2;
            cout << endl;
            cout << "¿Confirmar nombres? (S/N)" << endl;
            cin >> confirmarNombres;
            cout << "------------------------------------------------------------------------" << endl;

                }

            //COMIENZO DE RONDA
            for(int i = 0; i<2; i++){
            cout << "CLUTCH" << endl;
            cout << "------------------------------------------------------------------------" << endl;
            cout << "RONDA #" << ronda << endl;
            cout << jugador1 << " vs " << jugador2;

            ronda++;
            }
        break;

        //ESTADÍSTICAS

        case 2:

        break;

        //CRÉDITOS

        case 3:
            cout << "Se muestran apellidos, nombres y legajos de intregantes del equipo" ;
        break;

        //SALIR

        case 0:
            cout << "¿Está seguro de que desea salir? (S para sí - N para no)" << endl;
            cin >> confirmarSalir;

            cout << endl;
                if(confirmarSalir == 'S' || confirmarSalir == 's'){
                    cout << "Juego finalizado" << endl;

                }else if(confirmarSalir == 'N' || confirmarSalir == 'n'){
                    return main();
                }
        break;

        default:
            cout << endl << "No se ingresó un número válido en el menu principal, por favor ingrese nuevamente" << endl << endl;
            return main();

        break;


    }


	system("pause>nul");
	return 0;
}

