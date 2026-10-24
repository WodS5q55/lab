#include "TemplateMenu.h"
#include "Collection.h"
#include "Utils.h"
#include "Book.h"
#include "Magazine.h"
#include "Newspaper.h"
#include <iostream>

using namespace std;

template <typename T>
void run_single_template_menu(const string& title, Collection<T>& col, function<T()> selector, bool isReader, Library& library) {
    int choice;
    do {
        cout << "\n===========================================" << endl;
        cout << "   УПРАВЛЕНИЕ КОЛЛЕКЦИЕЙ: " << title << endl;
        cout << "===========================================" << endl;
        cout << "1. Добавить объект" << endl;
        cout << "2. Удалить объект по индексу" << endl;
        cout << "3. Найти объект по типу " << endl;
        cout << "4. Получить количество элементов" << endl;
        cout << "5. Вывод содержимого коллекции" << endl;
        cout << "6. Поиск по критерию " << endl;
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

                if constexpr (is_same_v<T, Publication*>) {
                    library -= col.get_by_index(idx);
                }
                else {
                    library -= col.get_by_index(idx);
                }
                cout << "[OK] Элемент удален." << endl;
                break;
            }
            case 3: {
                if (col.size() == 0) { cout << "Коллекция пуста." << endl; break; }

                if constexpr (is_same_v<T, Publication*>) {
                    cout << "Выберите тип для поиска:" << endl;
                    cout << "  1. Книга" << endl;
                    cout << "  2. Журнал" << endl;
                    cout << "  3. Газета" << endl;
                    int type_choice;
                    cout << "Ваш выбор: ";
                    cin >> type_choice; clear_input();

                    string target_type = "";
                    if (type_choice == 1) target_type = "Книга";
                    else if (type_choice == 2) target_type = "Журнал";
                    else if (type_choice == 3) target_type = "Газета";
                    else { cout << "Неверный тип." << endl; break; }

                    auto res = find_by_criteria(col, [target_type](Publication* item) {
                        return item->get_type() == target_type;
                        });

                    cout << "\nНайдено элементов (" << target_type << "): " << res.size() << endl;
                    for (size_t i = 0; i < res.size(); ++i) {
                        cout << "[" << i << "] " << res[i]->get_title() << endl;
                    }
                }
                else {
                    int target_id;
                    cout << "Введите ID читателя: ";
                    cin >> target_id; clear_input();

                    auto res = find_by_criteria(col, [target_id](Reader* item) {
                        return item->get_id() == target_id;
                        });

                    cout << "\nНайдено элементов: " << res.size() << endl;
                    for (size_t i = 0; i < res.size(); ++i) {
                        cout << "[" << i << "] " << res[i]->get_name() << " (ID: " << res[i]->get_id() << ")" << endl;
                    }
                }
                break;
            }
            case 4:
                cout << "Размер коллекции: " << col.size() << endl;
                break;
            case 5:
                if (isReader) col.print_readers(); else col.print_publications();
                break;
            case 6: {
                if (col.size() == 0) { cout << "Коллекция пуста." << endl; break; }

                cout << "Выберите критерий поиска:" << endl;
                if constexpr (is_same_v<T, Publication*>) {
                    cout << "  1. Только доступные издания" << endl;
                    cout << "  2. Только выданные издания" << endl;
                    cout << "  3. Дешевые (цена < 50 руб.)" << endl;
                    cout << "  4. Дорогие (цена >= 50 руб.)" << endl;
                    cout << "  5. Маленькие (страниц < 100)" << endl;
                    cout << "  6. Большие (страниц >= 100)" << endl;
                }
                else {
                    cout << "  1. Читатели с четным ID" << endl;
                    cout << "  2. Читатели с нечетным ID" << endl;
                }

                int criteria_choice;
                cout << "Ваш выбор: ";
                cin >> criteria_choice; clear_input();

                auto res = find_by_criteria(col, [criteria_choice](T item) -> bool {
                    if (item == nullptr) return false;

                    if constexpr (is_same_v<T, Publication*>) {
                        if (criteria_choice == 1) return item->is_available();
                        if (criteria_choice == 2) return item->is_borrowed();
                        if (criteria_choice == 3) return item->calculate_price() < 50.0;
                        if (criteria_choice == 4) return item->calculate_price() >= 50.0;
                        if (criteria_choice == 5) return item->get_pages() < 100;
                        if (criteria_choice == 6) return item->get_pages() >= 100;
                    }
                    else if constexpr (is_same_v<T, Reader*>) {
                        if (criteria_choice == 1) return item->get_id() % 2 == 0;
                        if (criteria_choice == 2) return item->get_id() % 2 != 0;
                    }
                    return false;
                    });

                cout << "\nНайдено элементов: " << res.size() << endl;
                for (size_t i = 0; i < res.size(); ++i) {
                    cout << "[" << i << "] ";
                    if constexpr (is_same_v<T, Publication*>) {
                        cout << res[i]->get_title()
                            << " | Цена: " << res[i]->calculate_price() << " руб."
                            << " | Страниц: " << res[i]->get_pages()
                            << " | (" << (res[i]->is_available() ? "Доступно" : "Выдано") << ")" << endl;
                    }
                    else {
                        cout << res[i]->get_name() << " (ID: " << res[i]->get_id() << ")" << endl;
                    }
                }
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

template void run_single_template_menu<Publication*>(const string&, Collection<Publication*>&, function<Publication* ()>, bool, Library&);
template void run_single_template_menu<Reader*>(const string&, Collection<Reader*>&, function<Reader* ()>, bool, Library&);

void run_templates_menu(Library& library) {
    int choice;
    do {
        cout << "\n===========================================" << endl;
        cout << "   МЕНЮ ШАБЛОНОВ " << endl;
        cout << "===========================================" << endl;
        cout << "1. Работа с коллекцией ИЗДАНИЙ " << endl;
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
            run_single_template_menu<Publication*>("ИЗДАНИЯ", library.get_publications_mutable(), pubSelector, false, library);
        }
        else if (choice == 2) {
            std::function<Reader* ()> readerSelector = [&library]() -> Reader* {
                return select_reader(library, "Выберите читателя:");
            };
            run_single_template_menu<Reader*>("ЧИТАТЕЛИ", library.get_readers_mutable_collection(), readerSelector, true, library);
        }

    } while (choice != 0);
}