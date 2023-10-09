//ETAPA INICIAL

#include <iostream>
#include <locale.h>
#include <cstdlib>
#include <time.h>

using namespace std;



int main(){
	setlocale(LC_ALL, "spanish");


    string palos[] = {"Picas", "Corazones", "Diamantes", "Tréboles"};
    string valores[] = {"10", "J", "Q", "K", "A"};


    string mazo[4][5];

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            mazo[i][j] = valores[j] + " " + palos[i];
        }
    }

    cout << "Primera carta: " << mazo[0][0] << endl;

}


