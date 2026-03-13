#include <iostream>
#include <cstdlib>
#include <ctime>
#include "FUNZIONI.h"
using namespace std;

int main() {
    srand(time(0));
    
    int saldo = 0;
    int ricarica = 0;
    int x;       
    int azione;  
    int z;       

    cout << "***************************************************" << endl;
    cout << "*********** BENVENUTO AL CASINO *******************" << endl;
    cout << "***************************************************" << endl;

    cout << "\nQuanti soldi vuoi cambiare in saldo gioco? ";
    cin >> ricarica;
    saldo = ricarica;

    while (true) {
        if (saldo <= 0) {
            cout << "\n[ATTENZIONE] Saldo esaurito. Vuoi ricaricare? 1)Si 0)Esci: ";
            cin >> azione;
            if (azione == 1) {
                cout << "Importo ricarica: "; cin >> ricarica;
                saldo += ricarica;
            } else break;
        }

        cout << "\n--- MENU PRINCIPALE (Saldo: " << saldo << "$) ---" << endl;
        cout << "1)Blackjack 2)Roulette 3)Baccarat 4)Dadi 5)Cassa 0)Esci: ";
        cin >> x;

        if (x == 0) break;
        if (x == 5) {
            cout << "Ricarica: "; cin >> ricarica;
            saldo += ricarica;
            continue;
        }

        if (x >= 1 && x <= 4) {
            while (true) {
                cout << "\nSaldo attuale: " << saldo << "$ - Inserisci puntata: ";
                cin >> z;

                if (z > saldo || z <= 0) {
                    cout << "!!! ERRORE: Puntata non valida o superiore al saldo !!!" << endl;
                    break; 
                }

                // --- 1. BLACKJACK (Con visualizzazione carte) ---
                if (x == 1) {
                    int c1 = pescarandom(), c2 = pescarandom();
                    int d1 = pescarandom(), d2 = pescarandom();
                    int p = c1 + c2;
                    int d = d1 + d2;
                    
                    cout << "Tu: [" << c1 << "][" << c2 << "] - Totale: " << p << endl;
                    cout << "Dealer mostra: [" << d1 << "]" << endl;

                    cout << "1)Carta 2)Stai: "; cin >> azione;
                    while (azione == 1 && p < 21) {
                        int nuova = pescarandom();
                        p += nuova;
                        cout << "Hai pescato: [" << nuova << "] - Nuovo totale: " << p << endl;
                        if (p < 21) { cout << "1)Carta 2)Stai: "; cin >> azione; }
                    }

                    if (p > 21) {
                        cout << "SBALLATO! Hai perso " << z << "$" << endl;
                        saldo -= z;
                    } else {
                        cout << "Dealer rivela la seconda carta: [" << d2 << "]" << endl;
                        while (d < 17) {
                            int nuovaD = pescarandom();
                            d += nuovaD;
                            cout << "Dealer pesca: [" << nuovaD << "] - Totale Dealer: " << d << endl;
                        }
                        
                        if (d > 21 || p > d) { cout << "VINCI! +" << z << "$" << endl; saldo += z; }
                        else if (p == d) cout << "PAREGGIO!" << endl;
                        else { cout << "PERSO! -" << z << "$" << endl; saldo -= z; }
                    }
                }

                // --- 2. ROULETTE ---
                else if (x == 2) {
                    cout << "1)Numero 2)Colore: "; cin >> azione;
                    int uscito = rand() % 37;
                    if (azione == 1) {
                        int n; cout << "Scegli 0-36: "; cin >> n;
                        cout << "Pallina su: " << uscito << endl;
                        if (n == uscito) { cout << "COLPITO! +35x" << endl; saldo += z * 35; }
                        else { cout << "PERSO!" << endl; saldo -= z; }
                    } else {
                        int col; cout << "1)Rosso 2)Nero: "; cin >> col;
                        int res = determinaColore(uscito);
                        cout << "Uscito: " << uscito << (res==1?" ROSSO":" NERO") << endl;
                        if (col == res) { cout << "VINTO!" << endl; saldo += z; }
                        else { cout << "PERSO!" << endl; saldo -= z; }
                    }
                }

                // --- 3. BACCARAT ---
                else if (x == 3) {
                    int scommessa; cout << "1)Player 2)Banker 3)Tie: "; cin >> scommessa;
                    int pMano = (pescarandom() + pescarandom()) % 10;
                    int bMano = (pescarandom() + pescarandom()) % 10;
                    cout << "Player: " << pMano << " | Banker: " << bMano << endl;
                    int v = (pMano > bMano) ? 1 : (bMano > pMano ? 2 : 3);
                    if (scommessa == v) {
                        if (v == 3) saldo += z * 8; else saldo += z;
                        cout << "VINTO!" << endl;
                    } else { cout << "PERSO!" << endl; saldo -= z; }
                }

                // --- 4. DADI (Nuova logica puntate) ---
                else if (x == 4) {
                    int tipoScommessa;
                    cout << "Punta su: 1)Numero preciso (x6) 2)Pari (x2) 3)Dispari (x2): ";
                    cin >> tipoScommessa;
                    
                    int d1 = (rand() % 6) + 1;
                    int d2 = (rand() % 6) + 1;
                    int somma = d1 + d2;
                    
                    cout << "Lancio: [" << d1 << "] + [" << d2 << "] = " << somma << endl;
                    
                    bool vinto = false;
                    if (tipoScommessa == 1) {
                        int numScelto; cout << "Quale numero? (2-12): "; cin >> numScelto;
                        if (somma == numScelto) { saldo += z * 5; vinto = true; } 
                    } else if (tipoScommessa == 2) {
                        if (somma % 2 == 0) { saldo += z; vinto = true; }
                    } else if (tipoScommessa == 3) {
                        if (somma % 2 != 0) { saldo += z; vinto = true; }
                    }
                    
                    if (vinto) cout << "VITTORIA!" << endl;
                    else { cout << "PERSO!" << endl; saldo -= z; }
                }

                if (saldo <= 0) break;
                cout << "\nSaldo attuale: " << saldo << "$ - 1)Rigioca 2)Menu: "; 
                cin >> azione;
                if (azione == 2) break;
            }
        }
    }

    cout << "\nGrazie per aver giocato! Esci con: " << saldo << "$" << endl;
    return 0;
}