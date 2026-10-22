#include "TemplateMenu.h"
#include "Collection.h"
#include "Utils.h"
#include <iostream>

using namespace std;

template <typename T>
void run_single_template_menu(const string& title, Collection<T>& col, function<T()> selector, bool isReader) {
    int choice;
    do {
        cout << "\n===========================================" << endl;
        cout << "   УПРАВЛЕНИЕ КОЛЛЕКЦИЕЙ: " << title << endl;
        cout << "===========================================" << endl;
        cout << "1. Добавить объект" << endl;
        cout << "2. Удалить объект по индексу" << endl;
        cout << "3. Получить объект по индексу" << endl;
        cout << "4. Поиск объекта" << endl;
        cout << "5. Получить количество элементов" << endl;
        cout << "6. Вывод содержимого коллекции" << endl;
        cout << "7. Поиск по критерию" << endl;
        cout << "0. Назад" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Выберите действие: ";

        cin >> choice;
        if (cin.fail()) { clear_input(); continue; }

        try {
            switch (choice) {
            case 1: {
                T item = selector();
                if (item != nullptr) {
                    if (col.find(item) != -1) cout << "[ОШИБКА] Объект уже есть в коллекции!" << endl;
                    else {
                        col.add(item);
                        cout << "[OK] Объект добавлен." << endl;
                    }
                }
                break;
            }
            case 2: {
                if (col.size() == 0) { cout << "Коллекция пуста." << endl; break; }
                if (isReader) col.print_readers(); else col.print_publications();

                size_t idx;
                cout << "Введите индекс для удаления: ";
                cin >> idx; clear_input();
                col.remove_by_index(idx);
                cout << "[OK] Элемент удален." << endl;
                break;
            }
            case 3: {
                if (col.size() == 0) { cout << "Коллекция пуста." << endl; break; }
                size_t idx;
                cout << "Введите индекс: ";
                cin >> idx; clear_input();
                T item = col.get_by_index(idx);
                cout << "Найден объект: ";
                if (isReader) cout << ((Reader*)item)->get_name();
                else cout << ((Publication*)item)->get_title();
                cout << endl;
                break;
            }
            case 4: {
                if (col.size() == 0) { cout << "Коллекция пуста." << endl; break; }
                T target = selector();
                if (target != nullptr) {
                    int idx = col.find(target);
                    if (idx != -1) cout << "[OK] Объект найден. Индекс: " << idx << endl;
                    else cout << "Объект не найден." << endl;
                }
                break;
            }
            case 5:
                cout << "Размер коллекции: " << col.size() << endl;
                break;
            case 6:
                if (isReader) col.print_readers(); else col.print_publications();
                break;
            case 7: {
                if (col.size() == 0) { cout << "Коллекция пуста." << endl; break; }
                cout << "Введите строку для поиска: ";
                string query;
                clear_input();
                getline(cin, query);

                auto res = find_by_criteria(col, [query](T item) {
                    if (item == nullptr) return false;
                    return true;
                    });
                cout << "Найдено элементов: " << res.size() << endl;
                break;
            }
            case 0: break;
            default: cout << "[ОШИБКА] Неверный выбор." << endl;
            }
        }
        catch (const exception& e) {
            cout << "[ОШИБКА] " << e.what() << endl; clear_input();
        }
    } while (choice != 0);
}

template void run_single_template_menu<Publication*>(const string&, Collection<Publication*>&, function<Publication* ()>, bool);
template void run_single_template_menu<Reader*>(const string&, Collection<Reader*>&, function<Reader* ()>, bool);

void run_templates_menu(Library& library) {
    Collection<Publication*> pubCol;
    Collection<Reader*> readerCol;

    int choice;
    do {
        cout << "\n===========================================" << endl;
        cout << "   МЕНЮ ШАБЛОНОВ COLLECTION<T> (ЛР №5)" << endl;
        cout << "===========================================" << endl;
        cout << "1. Работа с коллекцией ИЗДАНИЙ" << endl;
        cout << "2. Работа с коллекцией ЧИТАТЕЛЕЙ " << endl;
        cout << "0. Назад в главное меню" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Выберите действие: ";

        cin >> choice;
        if (cin.fail()) { clear_input(); continue; }

        if (choice == 1) {
            std::function<Publication* ()> pubSelector = [&library]() -> Publication* {
                return select_any_publication(library, "Выберите издание:");
            };
            run_single_template_menu<Publication*>("ИЗДАНИЯ", pubCol, pubSelector, false);
        }
        else if (choice == 2) {
            std::function<Reader* ()> readerSelector = [&library]() -> Reader* {
                return select_reader(library, "Выберите читателя:");
            };
            run_single_template_menu<Reader*>("ЧИТАТЕЛИ", readerCol, readerSelector, true);
        }

    } while (choice != 0);
}