#include "Menu.h"
#include "Utils.h"
#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

void show_menu(const Library& library) {
    cout << "\n===========================================" << endl;
    cout << "       УНИВЕРСИТЕТСКАЯ БИБЛИОТЕКА" << endl;
    cout << "===========================================" << endl;
    cout << "1. Зарегистрировать читателя" << endl;
    cout << "2. Выдать книгу" << endl;
    cout << "3. Вернуть книгу" << endl;
    cout << "4. Показать все книги" << endl;
    cout << "5. Показать всех читателей" << endl;
    cout << "6. Показать информацию о книге" << endl;
    cout << "7. Показать информацию о читателе" << endl;
    cout << "8. Изменить телефон читателя" << endl;
    cout << "9. Показать просроченные книги" << endl;
    cout << "10. Добавить книгу" << endl;
    cout << "11. Изменить ФИО читателя" << endl;
    cout << "12. Удалить книгу" << endl; 
    cout << "0. Выход" << endl;
    cout << "-------------------------------------------" << endl;
    cout << "Текущий день: " << library.get_day_counter() << endl;
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
            case 1: {
                string name, phone;
                do {
                    cout << "Введите ФИО читателя: ";
                    clear_input();
                    getline(cin, name);
                    if (name.empty() || is_blank(name)) {
                        cout << "[ОШИБКА] Имя не может быть пустым!" << endl;
                    }
                } while (name.empty() || is_blank(name));

                cout << "Введите номер телефона: ";
                getline(cin, phone);

                Reader reader(name, phone);
                library.add_reader(reader);
                break;
            }
            case 2: {
                vector<Book*> available = library.find_available_books();
                if (available.empty()) {
                    cout << "[ОШИБКА] Нет доступных книг для выдачи." << endl;
                    break;
                }
                Book* book = select_book(available, "Выберите книгу для выдачи:");
                if (!book) break;

                Reader* reader = select_reader(library, "Выберите читателя:");
                if (!reader) break;

                library.borrow_book(book, reader);
                break;
            }
            case 3: {
                vector<Book*> borrowed = library.find_borrowed_books();
                if (borrowed.empty()) {
                    cout << "[ОШИБКА] Нет выданных книг для возврата." << endl;
                    break;
                }
                Book* book = select_book(borrowed, "Выберите книгу для возврата:");
                if (!book) break;

                library.return_book(book);
                break;
            }
            case 4:
                library.display_all_books();
                break;
            case 5:
                library.display_all_readers();
                break;
            case 6: {
                Book* book = select_any_book(library, "Выберите книгу для просмотра информации:");
                if (!book) break;
                library.display_book_info(book);
                break;
            }
            case 7: {
                Reader* reader = select_reader(library, "Выберите читателя для просмотра информации:");
                if (!reader) break;
                library.display_reader_info(reader);
                break;
            }
            case 8: {
                Reader* reader = select_reader(library, "Выберите читателя для изменения телефона:");
                if (!reader) break;

                string phone;
                cout << "Введите новый номер телефона: ";
                clear_input();
                getline(cin, phone);
                library.change_reader_phone(reader, phone);
                break;
            }
            case 9:
                library.display_overdue_books();
                break;
            case 10: {
                cout << "\n--- ДОБАВЛЕНИЕ НОВОЙ КНИГИ ---" << endl;

                string title, author;
                int year;
                string type;
                int type_choice;

                do {
                    cout << "Введите название книги: ";
                    cin >> ws;
                    getline(cin, title);
                    if (title.empty() || is_blank(title)) {
                        cout << "[ОШИБКА] Название не может быть пустым!" << endl;
                    }
                } while (title.empty() || is_blank(title));

                do {
                    cout << "Введите автора книги: ";
                    cin >> ws;
                    getline(cin, author);
                    if (author.empty() || is_blank(author)) {
                        cout << "[ОШИБКА] Автор не может быть пустым!" << endl;
                    }
                } while (author.empty() || is_blank(author));

                do {
                    cout << "Введите год издания (0-2026): ";
                    cin >> year;
                    if (cin.fail()) {
                        clear_input();
                        cout << "[ОШИБКА] Введите число!" << endl;
                        continue;
                    }
                    if (year < 0 || year > 2026) {
                        cout << "[ОШИБКА] Год должен быть от 0 до 2026!" << endl;
                    }
                } while (year < 0 || year > 2026);
                clear_input();

                do {
                    cout << "Выберите тип книги:" << endl;
                    cout << "  1. учебник" << endl;
                    cout << "  2. методическое пособие" << endl;
                    cout << "  3. монография" << endl;
                    cout << "Введите номер (1-3): ";
                    cin >> type_choice;
                    if (cin.fail()) {
                        clear_input();
                        cout << "[ОШИБКА] Введите число!" << endl;
                        continue;
                    }
                    if (type_choice < 1 || type_choice > 3) {
                        cout << "[ОШИБКА] Введите 1, 2 или 3!" << endl;
                    }
                } while (type_choice < 1 || type_choice > 3);
                clear_input();

                if (type_choice == 1) {
                    type = "учебник";
                }
                else if (type_choice == 2) {
                    type = "методическое пособие";
                }
                else {
                    type = "монография";
                }

                Book new_book(title, author, year, type);
                library.add_book(new_book);
                break;
            }
            case 11: {
                Reader* reader = select_reader(library, "Выберите читателя для изменения ФИО:");
                if (!reader) break;

                string new_name;
                do {
                    cout << "Введите новое ФИО: ";
                    clear_input();
                    getline(cin, new_name);
                    if (new_name.empty() || is_blank(new_name)) {
                        cout << "[ОШИБКА] ФИО не может быть пустым!" << endl;
                    }
                } while (new_name.empty() || is_blank(new_name));

                library.change_reader_name(reader, new_name);
                break;
            }
            case 12: { 
                Book* book = select_any_book(library, "Выберите книгу для удаления:");
                if (!book) break;

                char confirm;
                cout << "Вы уверены, что хотите удалить книгу \""
                    << book->get_title() << "\"? (y/n): ";
                cin >> confirm;
                clear_input();

                if (confirm == 'y' || confirm == 'Y') {
                    library.remove_book(book);
                }
                else {
                    cout << "Удаление отменено." << endl;
                }
                break;
            }
            case 0:
                cout << "\nДо свидания!" << endl;
                break;
            default:
                cout << "[ОШИБКА] Неверный выбор. Попробуйте снова." << endl;
            }
        }
        catch (const exception& e) {
            cout << "[ОШИБКА] " << e.what() << endl;
            clear_input();
        }

    } while (choice != 0);
}