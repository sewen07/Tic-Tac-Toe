#include <iostream>     
#include <vector>
using namespace std;

// Verifica daca mutarea este valida
bool isMoveValid(char ai[3][3], int row, int col) {
    return ai[row][col] == ' ';
}

// Afiseaza tabla de joc
void printBoard(char xo[3][3]) {
    cout << endl;
    cout << xo[0][0] << " | " << xo[0][1] << " | " << xo[0][2] << endl;
    cout << "----------" << endl;
    cout << xo[1][0] << " | " << xo[1][1] << " | " << xo[1][2] << endl;
    cout << "----------" << endl;
    cout << xo[2][0] << " | " << xo[2][1] << " | " << xo[2][2] << endl;
    cout << endl;
}

// Verifica daca mutarea respectiva castiga / a castigat meciul
bool checkWin(char xo[3][3], char player) {
    if ((xo[0][0] == player && xo[0][1] == player && xo[0][2] == player) ||
        (xo[1][0] == player && xo[1][1] == player && xo[1][2] == player) ||
        (xo[2][0] == player && xo[2][1] == player && xo[2][2] == player) ||
        (xo[0][0] == player && xo[1][0] == player && xo[2][0] == player) ||
        (xo[0][1] == player && xo[1][1] == player && xo[2][1] == player) ||
        (xo[0][2] == player && xo[1][2] == player && xo[2][2] == player) ||
        (xo[0][0] == player && xo[1][1] == player && xo[2][2] == player) ||
        (xo[2][0] == player && xo[1][1] == player && xo[0][2] == player)) {
        return true;
    }
    return false;
}

// Verifica daca mutarea respectiva a rezultat intr-o egalitate
bool checkDraw(char xo[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (xo[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

// Verifica daca mutarea respectiva este valida si poate castiga meciul
bool tryMove(char ai[3][3], char player, int row, int col) {
    if (isMoveValid(ai, row, col)) {
        ai[row][col] = player;
        if (checkWin(ai, player)) {
            ai[row][col] = ' '; // reseteaza tabla de joc
            return true;
        }
        ai[row][col] = ' '; // reseteaza tabla de joc
    }
    return false;
}

void AI(char ai[3][3], char player, char bot) {

    // Verifica daca AI-ul poate castiga in urmatoarea mutare
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tryMove(ai, bot, i, j)) {
                ai[i][j] = bot;
                return;
            }
        }
    }

    // Verifica daca player-ul poate castiga in urmatoarea mutare si il blocheaza
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (tryMove(ai, player, i, j)) {
                ai[i][j] = bot;
                return;
            }
        }
    }

    // Restul de mutari (centru, colturi si mijlocuri)

    // Colturi
    int corners[4][2] = { {0, 0}, {0, 2}, {2, 0}, {2, 2} }; // lista pozitiilor colturilor
    for (int i = 0; i < 4; i++) {
        if (isMoveValid(ai, corners[i][0], corners[i][1])) { // verificare pana un colt este mutare valida
            ai[corners[i][0]][corners[i][1]] = bot; // mutarea
            return;
        }
    }

    // Centru
    if (isMoveValid(ai, 1, 1)) {
        ai[1][1] = bot; // daca mutarea este valida, atunci AI-ul face urmatoarea mutare in mijloc
        return;
    }

    // Mijlocuri
    int edges[4][2] = { {0, 1}, {1, 0}, {1, 2}, {2, 1} }; // lista pozitiilor mijlocurilor
    for (int i = 0; i < 4; i++) {
        if (isMoveValid(ai, edges[i][0], edges[i][1])) { // verificare pana un mijloc este o mutare valida
            ai[edges[i][0]][edges[i][1]] = bot; // mutarea
            return;
        }
    }
}

int main() {

    char xo[3][3]; // matrice care reprezinta spatiul de joc

    // Umplerea spatiului de joc cu spatii goale
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            xo[i][j] = ' ';
        }
    }

    char player1, player2;
    string player_choice;
    int win1 = 0, win2 = 0;

    cout << "Vrei sa joci cu X sau cu 0: ";
    cin >> player_choice;

    // Alegerea semnelor de joc
    if (player_choice == "X" || player_choice == "x") {
        player1 = 'X';
        player2 = '0';
    }
    else if (player_choice == "0") {
        player1 = '0';
        player2 = 'X';
    }
    else {
        cout << "Alegere invalida. Incearca din nou." << endl;
        return 0;
    }

    while (true) {

        // Introducere rand, coloana
        int row, col;

        AI(xo, player1, player2);

        // Se verifica daca AI-ul a castigat
        if (checkWin(xo, player2)) {
            printBoard(xo);
            cout << "AI-ul a castigat" << endl;
            break;
        }

        // Se verifica daca este egalitate
        if (checkDraw(xo)) {
            printBoard(xo);
            cout << "Egalitate" << endl;
            break;
        }

        printBoard(xo);

        // Se citeste mutarea jucatorului pana cand aceasta este una valida
        do {
            cout << "Player 1 rand, coloana: ";
            cin >> row >> col;
            row--;
            col--;
            if (!isMoveValid(xo, row, col)) {
                cout << "Optiune invalida." << endl;
            }
        } while (!isMoveValid(xo, row, col));
        xo[row][col] = player1;

        // Se verifica daca jucatorul a castigat
        if (checkWin(xo, player1)) {
            printBoard(xo);
            cout << "Player-ul 1 a castigat" << endl;
            break;
        }

        // Se verifica daca este egalitate
        if (checkDraw(xo)) {
            printBoard(xo);
            cout << "Egalitate" << endl;
            break;
        }

    }

    return 0;
}
