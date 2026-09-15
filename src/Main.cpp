#include "Library.h"
#include "Menu.h"
#include <iostream>
#include <locale>

using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");
    Library library;

    cout << "\n===========================================" << endl;
    cout << " ƒобро пожаловать в университетскую библиотеку!" << endl;
    cout << "===========================================" << endl;

    run_menu(library);

    return 0;
}
