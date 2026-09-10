#include "Library.h"
#include "Utils.h"
#include <iostream>

using namespace std;


int main() {
    setlocale(LC_ALL, "Russian");

    Library library;
    int choice;

    cout << "\n===========================================" << endl;
    cout << "   ДОБРО ПОЖАЛОВАТЬ В УНИВЕРСИТЕТСКУЮ БИБЛИОТЕКУ!" << endl;
    cout << "===========================================" << endl;

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
                cout << "Введите ФИО читателя: ";
                clear_input();
                getline(cin, name);
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
                vector<string> authors = library.get_distinct_authors();
                if (authors.empty()) {
                    cout << "[ОШИБКА] Нет авторов в каталоге." << endl;
                    break;
                }
                int idx = select_from_list(authors, "Выберите автора:");
                if (idx < 0) break;
                library.print_books_by_author(authors[static_cast<size_t>(idx)]);
                break;
            }
            case 11: {
                vector<string> types = { "учебник", "методическое пособие", "монография" };
                int idx = select_from_list(types, "Выберите тип книги:");
                if (idx < 0) break;
                library.print_books_by_type(types[static_cast<size_t>(idx)]);
                break;
            }
            case 12:
                library.pass_day();
                break;

            case 13: {
                cout << "\n--- ДОБАВЛЕНИЕ НОВОЙ КНИГИ ---" << endl;

                string title, author;
                int year;
                string type;
                int type_choice;


                do {
                    cout << "Введите название книги: ";
                    clear_input();
                    getline(cin, title);
                    if (title.empty() || is_blank(title)) {
                        cout << "[ОШИБКА] Название не может быть пустым!" << endl;
                    }
                } while (title.empty() || is_blank(title));

                do {
                    cout << "Введите автора книги: ";
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

    return 0;
}