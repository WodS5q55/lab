#include "TemplateMenu.h"
#include "Utils.h"
#include "Book.h"
#include "Magazine.h"
#include "Newspaper.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

void run_publications_stl_menu(Library& library) {
    int choice;
    do {
        cout << "\n===========================================" << endl;
        cout << "   ИЗДАНИЯ  " << endl;
        cout << "===========================================" << endl;
        cout << "1. Добавить издание" << endl;
        cout << "2. Удалить издание" << endl;
        cout << "3. Поиск по критерию" << endl;
        cout << "4. Сортировка по году(мин -> макс)" << endl;
        cout << "5. Сортировка по цене(мин -> макс)" << endl;
        cout << "6. Минимальное количество страниц" << endl;
        cout << "7. Максимальное количество страниц" << endl;
        cout << "8. Подсчёт выданных" << endl;
        cout << "9. Показать все" << endl;
        cout << "10. Сортировка по году(макс -> мин)" << endl;
        cout << "11. Сортировка по цене(макс -> мин)" << endl;
        cout << "0. Назад" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Выберите действие: ";

        cin >> choice;
        if (cin.fail()) { clear_input(); continue; }

        auto& pubs = library.get_publications();

        try {
            switch (choice) {
            case 1: {
                cout << "\n1. Книга\n2. Журнал\n3. Газета\nВыбор: ";
                int type; cin >> type; clear_input();
                string title = input_non_empty_string("Название: ");
                string author = input_non_empty_string("Автор: ");

                if (type == 1) {
                    int year = input_int_in_range("Год: ", 1452, 2026);
                    int pages = input_int_in_range("Страниц: ", 1, 10000);
                    int tc;
                    cout << "Тип (1-Учебник, 2-Метод, 3-Монография): "; cin >> tc; clear_input();
                    string t = (tc == 1) ? "учебник" : (tc == 2) ? "методическое пособие" : "монография";
                    library += new Book(library.get_publication_count() + 1, title, author, year, pages, t);
                }
                else if (type == 2) {
                    int year = input_int_in_range("Год: ", 1452, 2026);
                    int pages = input_int_in_range("Страниц: ", 1, 500);
                    int issue = input_int_in_range("Выпуск: ", 1, 10000);
                    library += new Magazine(library.get_publication_count() + 1, title, author, year, pages, issue);
                }
                else {
                    int pages = input_int_in_range("Страниц: ", 1, 96);
                    string date = input_non_empty_string("Дата (дд.мм.гггг): ");
                    library += new Newspaper(library.get_publication_count() + 1, title, author, pages, date);
                }
                break;
            }
            case 2: {
                if (pubs.empty()) { cout << "Каталог пуст." << endl; break; }
                vector<string> lines;
                for (auto* p : pubs) lines.push_back(p->short_line());
                int idx = select_from_list(lines, "Выберите издание для удаления:");
                if (idx >= 0) {
                    library -= pubs[idx];
                }
                break;
            }
            case 3: {
                cout << "\n1. Только доступные\n2. Только выданные\n3. Дешевые (<50)\n4. Дорогие (>=50)\n5. Маленькие (<100 стр)\n6. Большие (>=100 стр)\n7. По названию\nВаш выбор: ";
                int crit; cin >> crit; clear_input();

                vector<Publication*> res;
                if (crit == 7) {
                    string q = input_non_empty_string("Введите часть названия: ");
                    copy_if(pubs.begin(), pubs.end(), back_inserter(res), [&q](Publication* p) {
                        return p->get_title().find(q) != string::npos;
                        });
                }
                else {
                    copy_if(pubs.begin(), pubs.end(), back_inserter(res), [crit](Publication* p) {
                        if (crit == 1) return p->is_available();
                        if (crit == 2) return p->is_borrowed();
                        if (crit == 3) return p->calculate_price() < 50.0;
                        if (crit == 4) return p->calculate_price() >= 50.0;
                        if (crit == 5) return p->get_pages() < 100;
                        if (crit == 6) return p->get_pages() >= 100;
                        return false;
                        });
                }
                cout << "\nНайдено: " << res.size() << endl;
                for (auto* p : res) cout << p->short_line() << endl;
                break;
            }
            case 4: {
                vector<Publication*> sorted_pubs = pubs;
                sort(sorted_pubs.begin(), sorted_pubs.end(), [](Publication* a, Publication* b) {
                    return a->get_year() < b->get_year();
                    });
                cout << "--- ПО ГОДУ ---" << endl;
                for (auto* p : sorted_pubs) {
                    cout << p->short_line() << " | Год: " << p->get_year() << endl;
                }
                break;
            }
            case 5: {
                vector<Publication*> sorted_pubs = pubs;
                sort(sorted_pubs.begin(), sorted_pubs.end(), [](Publication* a, Publication* b) {
                    return a->calculate_price() < b->calculate_price();
                    });
                cout << "--- ПО ЦЕНЕ ---" << endl;
                for (auto* p : sorted_pubs) {
                    cout << p->short_line() << " | Цена: " << p->calculate_price() << " руб." << endl;
                }
                break;
            }
            case 6: {
                if (pubs.empty()) { cout << "Нет изданий." << endl; break; }
                auto min_it = min_element(pubs.begin(), pubs.end(), [](Publication* a, Publication* b) {
                    return a->get_pages() < b->get_pages();
                    });
                cout << "Мин. страниц: " << (*min_it)->get_pages() << " стр. (\"" << (*min_it)->get_title() << "\")" << endl;
                break;
            }
            case 7: {
                if (pubs.empty()) { cout << "Нет изданий." << endl; break; }
                auto max_it = max_element(pubs.begin(), pubs.end(), [](Publication* a, Publication* b) {
                    return a->get_pages() < b->get_pages();
                    });
                cout << "Макс. страниц: " << (*max_it)->get_pages() << " стр. (\"" << (*max_it)->get_title() << "\")" << endl;
                break;
            }
            case 8: {
                int count = count_if(pubs.begin(), pubs.end(), [](Publication* p) {
                    return p->is_borrowed();
                    });
                cout << "Выдано изданий: " << count << endl;
                break;
            }
            case 9: {
                for (auto* p : pubs) cout << p->short_line() << endl;
                break;
            }
            case 10: {
                vector<Publication*> sorted_pubs = pubs;
                sort(sorted_pubs.begin(), sorted_pubs.end(), [](Publication* a, Publication* b) {
                    return a->get_year() > b->get_year();
                    });
                cout << "--- ПО ГОДУ ---" << endl;
                for (auto* p : sorted_pubs) {
                    cout << p->short_line() << " | Год: " << p->get_year() << endl;
                }
                break;
            }
            case 11: {
                vector<Publication*> sorted_pubs = pubs;
                sort(sorted_pubs.begin(), sorted_pubs.end(), [](Publication* a, Publication* b) {
                    return a->calculate_price() > b->calculate_price();
                    });
                cout << "--- ПО ЦЕНЕ ---" << endl;
                for (auto* p : sorted_pubs) {
                    cout << p->short_line() << " | Цена: " << p->calculate_price() << " руб." << endl;
                }
                break;
            }
            case 0: break;
            default: cout << "Неверный выбор." << endl;
            }
        }
        catch (const exception& e) {
            cout << "[Ошибка] " << e.what() << endl;
            clear_input();
        }
    } while (choice != 0);
}

void run_readers_stl_menu(Library& library) {
    int choice;
    do {
        cout << "\n===========================================" << endl;
        cout << "   ЧИТАТЕЛИ   " << endl;
        cout << "===========================================" << endl;
        cout << "1. Добавить читателя" << endl;
        cout << "2. Удалить читателя" << endl;
        cout << "3. Поиск по критерию" << endl;
        cout << "4. Подсчёт с книгами " << endl;
        cout << "5. Показать всех" << endl;
        cout << "0. Назад" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Выберите действие: ";

        cin >> choice;
        if (cin.fail()) { clear_input(); continue; }

        auto& readers = library.get_readers();

        try {
            switch (choice) {
            case 1: {
                clear_input();
                string name = input_non_empty_string("ФИО: ");
                string phone = input_non_empty_string("Телефон: ");
                library += new Reader(name, phone);
                break;
            }
            case 2: {
                if (readers.empty()) { cout << "Список пуст." << endl; break; }
                vector<Reader*> rlist;
                vector<string> lines;
                for (auto* r : readers) {
                    rlist.push_back(r);
                    lines.push_back(r->get_name() + " (ID: " + to_string(r->get_id()) + ")");
                }
                int idx = select_from_list(lines, "Выберите читателя для удаления:");
                if (idx >= 0) {
                    library -= rlist[idx];
                }
                break;
            }
            case 3: {
                cout << "\n1. Четные ID\n2. Нечетные ID\n3. По имени\nВаш выбор: ";
                int crit; cin >> crit; clear_input();

                vector<Reader*> res;
                if (crit == 3) {
                    string q = input_non_empty_string("Введите часть ФИО: ");
                    for (auto* r : readers) {
                        if (r->get_name().find(q) != string::npos) res.push_back(r);
                    }
                }
                else {
                    for (auto* r : readers) {
                        if (crit == 1 && r->get_id() % 2 == 0) res.push_back(r);
                        if (crit == 2 && r->get_id() % 2 != 0) res.push_back(r);
                    }
                }
                cout << "\nНайдено: " << res.size() << endl;
                for (auto* r : res) cout << *r << endl;
                break;
            }
            case 4: {
                auto& pubs = library.get_publications();
                int count = count_if(readers.begin(), readers.end(), [&pubs](Reader* p) {
                    return any_of(pubs.begin(), pubs.end(), [&p](Publication* pub) {
                        return pub->get_borrowed_by() == p;
                        });
                    });
                cout << "Читателей с книгами: " << count << endl;
                break;
            }
            case 5: library.display_all_readers(); break;
            case 0: break;
            default: cout << "Неверный выбор." << endl;
            }
        }
        catch (const exception& e) {
            cout << "[Ошибка] " << e.what() << endl;
            clear_input();
        }
    } while (choice != 0);
}

void run_templates_menu(Library& library) {
    int choice;
    do {
        cout << "\n===========================================" << endl;
        cout << "   МЕНЮ STL   " << endl;
        cout << "===========================================" << endl;
        cout << "1. Работа с изданиями " << endl;
        cout << "2. Работа с читателями " << endl;
        cout << "0. Назад в главное меню" << endl;
        cout << "-------------------------------------------" << endl;
        cout << "Выберите действие: ";

        cin >> choice;
        if (cin.fail()) { clear_input(); continue; }

        if (choice == 1) run_publications_stl_menu(library);
        else if (choice == 2) run_readers_stl_menu(library);

    } while (choice != 0);
}