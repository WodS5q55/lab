#include "Menu.h"
#include "Utils.h"
#include "Book.h"
#include "Magazine.h"
#include "Newspaper.h"
#include <iostream>
#include <limits>

using namespace std;

void show_menu(const Library& library) {
    cout << "\n===========================================" << endl;
    cout << "       УНИВЕРСИТЕТСКАЯ БИБЛИОТЕКА" << endl;
    cout << "===========================================" << endl;
    cout << "1.  Показать все издания (полиморфизм)" << endl;
    cout << "2.  Выдать издание читателю" << endl;
    cout << "3.  Вернуть издание" << endl;
    cout << "4.  Показать всех читателей" << endl;
    cout << "5.  Показать информацию об издании" << endl;
    cout << "6.  Показать просроченные издания" << endl;
    cout << "7.  Сравнить два издания" << endl;
    cout << "8.  Зарегистрировать читателя (>>, +=)" << endl;
    cout << "9.  Добавить книгу (>>, +=)" << endl;
    cout << "10. Добавить журнал" << endl;
    cout << "11. Добавить газету" << endl;
    cout << "12. Удалить издание (-=)" << endl;
    cout << "13. Удалить читателя (-=)" << endl;
    cout << "14. Сравнить двух читателей" << endl;
    cout << "15. Демонстрация полиморфизма" << endl;
    cout << "0.  Выход" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Выберите действие: ";
}

void run_menu(Library& library) {
    int choice;

    do {
        show_menu(library);
        cin >> choice;

        if (cin.fail()) {
            clear_input();
            cout << "[ОШИБКА] Введите число!" << endl;
            continue;
        }

        try {
            switch (choice) {
            case 1:
                library.display_all_publications();
                break;

            case 2: {
                vector<Publication*> available = library.find_available_publications();
                if (available.empty()) {
                    cout << "[ОШИБКА] Нет доступных изданий." << endl;
                    break;
                }
                Publication* pub = select_publication(available, "Выберите издание:");
                if (!pub) break;

                Reader* reader = select_reader(library, "Выберите читателя:");
                if (!reader) break;

                library.borrow_publication(pub, reader);
                break;
            }

            case 3: {
                vector<Publication*> borrowed = library.find_borrowed_publications();
                if (borrowed.empty()) {
                    cout << "[ОШИБКА] Нет выданных изданий." << endl;
                    break;
                }
                Publication* pub = select_publication(borrowed, "Выберите издание:");
                if (!pub) break;

                library.return_publication(pub);
                break;
            }

            case 4:
                library.display_all_readers();
                break;

            case 5: {
                Publication* pub = select_any_publication(library, "Выберите издание:");
                if (!pub) break;
                library.display_publication_info(pub);
                break;
            }

            case 6:
                library.display_overdue_publications();
                break;

            case 7:
                library.compare_two_publications();
                break;

            case 8: {
                cout << "\n--- РЕГИСТРАЦИЯ ЧИТАТЕЛЯ ---" << endl;
                clear_input();
                Reader new_reader;
                cin >> new_reader;
                cout << "\nСоздан: " << new_reader << endl;
                library += new_reader;
                break;
            }

            case 9: {
                cout << "\n--- ДОБАВЛЕНИЕ КНИГИ ---" << endl;
                clear_input();

                string title, author, type;
                int year, pages, type_choice;

                do {
                    cout << "Название: ";
                    getline(cin, title);
                    if (title.empty() || is_blank(title))
                        cout << "[ОШИБКА] Название не может быть пустым!" << endl;
                } while (title.empty() || is_blank(title));

                do {
                    cout << "Автор: ";
                    getline(cin, author);
                    if (author.empty() || is_blank(author))
                        cout << "[ОШИБКА] Автор не может быть пустым!" << endl;
                } while (author.empty() || is_blank(author));

                do {
                    cout << "Год (1452-2026): ";
                    cin >> year;
                    if (cin.fail()) { clear_input(); continue; }
                } while (year < 1452 || year > 2026);

                do {
                    cout << "Страниц (1-10000): ";
                    cin >> pages;
                    if (cin.fail()) { clear_input(); continue; }
                } while (pages < 1 || pages > 10000);
                clear_input();

                do {
                    cout << "Тип:\n  1. учебник\n  2. методическое пособие\n  3. монография\n";
                    cout << "Выберите (1-3): ";
                    cin >> type_choice;
                    if (cin.fail()) { clear_input(); continue; }
                } while (type_choice < 1 || type_choice > 3);
                clear_input();

                if (type_choice == 1) type = "учебник";
                else if (type_choice == 2) type = "методическое пособие";
                else type = "монография";

                int new_id = library.get_publication_count() + 1;
                Book* new_book = new Book(new_id, title, author, year, pages, type);
                library += new_book;
                break;
            }

            case 10: {
                cout << "\n--- ДОБАВЛЕНИЕ ЖУРНАЛА ---" << endl;
                clear_input();

                string title, author;
                int year, pages, issue;

                cout << "Название: "; getline(cin, title);
                cout << "Издательство: "; getline(cin, author);
                cout << "Год: "; cin >> year;
                cout << "Страниц: "; cin >> pages;
                cout << "Номер выпуска: "; cin >> issue;
                clear_input();

                int new_id = library.get_publication_count() + 1;
                Magazine* new_mag = new Magazine(new_id, title, author, year, pages, issue);
                library += new_mag;
                break;
            }

            case 11: {
                cout << "\n--- ДОБАВЛЕНИЕ ГАЗЕТЫ ---" << endl;
                clear_input();

                string title, author, date;
                int pages;

                do {
                    cout << "Название: ";
                    getline(cin, title);
                    if (title.empty() || is_blank(title))
                        cout << "[ОШИБКА] Название не может быть пустым!" << endl;
                } while (title.empty() || is_blank(title));

                do {
                    cout << "Издательство: ";
                    getline(cin, author);
                    if (author.empty() || is_blank(author))
                        cout << "[ОШИБКА] Издательство не может быть пустым!" << endl;
                } while (author.empty() || is_blank(author));

                do {
                    cout << "Страниц (1-96): ";
                    cin >> pages;
                    if (cin.fail()) { clear_input(); continue; }
                    if (pages < 1 || pages > 96)
                        cout << "[ОШИБКА] Страниц должно быть от 1 до 96!" << endl;
                } while (pages < 1 || pages > 96);
                clear_input();

                do {
                    cout << "Дата выпуска (дд.мм.гггг): ";
                    getline(cin, date);
                    if (!is_valid_date(date))
                        cout << "[ОШИБКА] Некорректная дата! Формат: дд.мм.гггг (например, 15.09.2024)" << endl;
                } while (!is_valid_date(date));

                int new_id = library.get_publication_count() + 1;
                Newspaper* new_np = new Newspaper(new_id, title, author, pages, date);
                library += new_np;
                break;
            }

            case 12: {
                Publication* pub = select_any_publication(library, "Выберите издание для удаления:");
                if (!pub) break;

                if (pub->is_borrowed()) {
                    cout << "[ОШИБКА] Нельзя удалить выданное издание!" << endl;
                    break;
                }

                char confirm;
                cout << "Вы уверены? (y/n): ";
                cin >> confirm;
                clear_input();

                if (confirm == 'y' || confirm == 'Y') {
                    library -= pub;
                }
                else {
                    cout << "Отменено." << endl;
                }
                break;
            }

            case 13: {
                Reader* reader = select_reader(library, "Выберите читателя:");
                if (!reader) break;
                library -= *reader;
                break;
            }

            case 14:
                library.compare_two_readers();
                break;

            case 15:
                library.display_all_types_info();
                break;

            case 0:
                cout << "\nДо свидания!" << endl;
                break;

            default:
                cout << "[ОШИБКА] Неверный выбор." << endl;
            }
        }
        catch (const exception& e) {
            cout << "[ОШИБКА] " << e.what() << endl;
            clear_input();
        }

    } while (choice != 0);
}