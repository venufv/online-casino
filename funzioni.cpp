#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;




int pescarandom() {
    return (rand() % 10) + 2; 
}


int determinaColore(int n) {
    if (n == 0) return 0;
    if (n % 2 == 0) return 2;
    return 1;
}