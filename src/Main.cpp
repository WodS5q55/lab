#include "Library.h"
#include "Menu.h"
#include <iostream>
#include <locale>

using namespace std;

int main() {
#ifdef _WIN32
    setlocale(LC_ALL, "Russian");
#else
    setlocale(LC_ALL, "");
#endif

    Library library;

    cout << "\n===========================================" << endl;
    cout << "   днапн онфюкнбюрэ б смхбепяхреряйсч ахакхнрейс!" << endl;
    cout << "===========================================" << endl;

    run_menu(library);

    return 0;
}