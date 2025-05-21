#include "game_of_life.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

game_of_life::game_of_life() {
    srand(static_cast<unsigned int>(time(nullptr)));
    for (unsigned int i = 0; i < REDAKA; i++) {
        for (unsigned int j = 0; j < STUPACA; j++) {
            _generacija[i][j] = slucajna_vrijednost();
            _sljedeca_generacija[i][j] = false;
        }
    }
}


bool game_of_life::slucajna_vrijednost() {
    return (rand() % 4 == 0);
}

//Ako je izvan granica onda umire
bool game_of_life::celija_zauzeta(int i, int j) {
    if (i < 0 || i >= static_cast<int>(REDAKA) || j < 0 || j >= static_cast<int>(STUPACA))
        return false;
    return _generacija[i][j];
}

//Raèunanje novih generacija
void game_of_life::sljedeca_generacija() {
    for (unsigned int i = 0; i < REDAKA; i++) {
        for (unsigned int j = 0; j < STUPACA; j++) {
            int susjedi = 0;
            //Gleda žive æelije (i, j)
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    if (di == 0 && dj == 0) continue;
                    if (celija_zauzeta(i + di, j + dj)) susjedi++;
                }
            }

            if (_generacija[i][j]) {
                //Živa æelija preživljava ako ima 2 ili 3 susjeda
                _sljedeca_generacija[i][j] = (susjedi == 2 || susjedi == 3);
            }
            else {
                //Mrtva æelija se može oživiti ako ima toèno 3 susjeda
                _sljedeca_generacija[i][j] = (susjedi == 3);
            }
        }
    }

    //Zamijeni generacije
    for (unsigned int i = 0; i < REDAKA; i++) {
        for (unsigned int j = 0; j < STUPACA; j++) {
            _generacija[i][j] = _sljedeca_generacija[i][j];
        }
    }
}
//Iscrtavanje trenutne generacije
void game_of_life::iscrtaj() {
    system("cls");
    for (unsigned int i = 0; i < REDAKA; i++) {
        for (unsigned int j = 0; j < STUPACA; j++) {
            cout << (_generacija[i][j] ? 'O' : '.');
        }
        cout << endl;
    }
}
