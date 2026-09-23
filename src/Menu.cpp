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
    cout << "13. Сравнить две книги" << endl;
    cout << "14. Удалить читателя" << endl;
    cout << "15. Сравнить двух читателей" << endl;
    cout << "0. Выход" << endl;
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
                cout << "\n--- РЕГИСТРАЦИЯ ЧИТАТЕЛЯ ---" << endl;

                Reader new_reader("", "");
                cin >> new_reader;

                cout << "\nСоздан: " << new_reader << endl;

                library += new_reader;
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
                Book* book = select_any_book(library, "Выберите книгу:");
                if (!book) break;
                library.display_book_info(book);
                break;
            }
            case 7: {
                Reader* reader = select_reader(library, "Выберите читателя:");
                if (!reader) break;
                library.display_reader_info(reader);
                break;
            }
            case 8: {
                Reader* reader = select_reader(library, "Выберите читателя:");
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

                Book new_book(0, "", "", 0, "");
                cin >> new_book;

                int new_id = library.get_book_count() + 1;
                Book final_book(new_id, new_book.get_title(), new_book.get_author(),
                    new_book.get_year(), new_book.get_type());

                library += final_book;
                break;
            }

            case 11: {
                Reader* reader = select_reader(library, "Выберите читателя:");
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

                if (book->is_borrowed()) {
                    cout << "[ОШИБКА] Нельзя удалить книгу \"" << book->get_title()
                        << "\" — она выдана читателю!" << endl;
                    break;
                }

                char confirm;
                cout << "Вы уверены? (y/n): ";
                cin >> confirm;
                clear_input();

                if (confirm == 'y' || confirm == 'Y') {
                    library -= *book;
                }
                else {
                    cout << "Удаление отменено." << endl;
                }
                break;
            }

            case 13:
                library.compare_two_books();
                break;

            case 14: {
                Reader* reader = select_reader(library, "Выберите читателя для удаления:");
                if (!reader) break;

                library -= *reader;
                break;
            }

            case 15:
                library.compare_two_readers();
                break;

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