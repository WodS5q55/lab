#include "Library.h"
#include "Menu.h"
#include <iostream>
#include <locale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    Library library;

    cout << "\n===========================================" << endl;
    cout << "   Welcome to the Library!" << endl;
    cout << "===========================================" << endl;

    run_menu(library);

    return 0;
}
