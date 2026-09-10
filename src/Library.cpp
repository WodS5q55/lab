#include "Library.h"
#include "Utils.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>

using namespace std;

Library::Library() {
    day_counter = 1;

    books.push_back(Book("Высшая математика", "Иванов А.А.", 2020, "учебник"));
    books.push_back(Book("Дискретная математика", "Иванов А.А.", 2021, "учебник"));
    books.push_back(Book("Физика для инженеров", "Петров Б.В.", 2019, "учебник"));
    books.push_back(Book("Программирование на C++", "Сидоров В.Г.", 2021, "учебник"));
    books.push_back(Book("Основы баз данных", "Козлова Е.М.", 2022, "учебник"));
    books.push_back(Book("Теория вероятностей", "Козлова Е.М.", 2021, "учебник"));
    books.push_back(Book("Методика решения задач по физике", "Смирнов Д.А.", 2020, "методическое пособие"));
    books.push_back(Book("Практикум по программированию", "Васильева О.И.", 2021, "методическое пособие"));
    books.push_back(Book("Современные алгоритмы машинного обучения", "Новиков С.П.", 2023, "монография"));
    books.push_back(Book("Искусственный интеллект и нейросети", "Михайлов А.Н.", 2022, "монография"));

    readers.push_back(Reader("Алексей Иванов", "+375292245423"));
    readers.push_back(Reader("Никита Драбудько", "+375684539212"));
    readers.push_back(Reader("Дмитрий Сидоров", "+375197652934"));
    readers.push_back(Reader("Елена Смирнова", "+375451783256"));
    readers.push_back(Reader("Ольга Кузнецова", "+375998563341"));
    readers.push_back(Reader("Сергей Новиков", "+375872114598"));
    readers.push_back(Reader("Анна Васильева", "+375759938782"));
    readers.push_back(Reader("Игорь Михайлов", "+375344436121"));
    readers.push_back(Reader("Наталья Морозова", "+375875596214"));
    readers.push_back(Reader("Павел Козлов", "+375859967546"));

    books[2].borrow_book(readers[0].get_id(), 14);
    books[6].borrow_book(readers[1].get_id(), 1);

    for (int i = 0; i < 2; i++) {
        for (auto& book : books) {
            if (book.get_status() == BORROWED && book.get_days_left() > 0) {
                book.decrease_days();
            }
        }
    }
}

void Library::add_book(const Book& book) {
    if (book.get_title().empty() || is_blank(book.get_title())) {
        throw invalid_argument("Название книги не может быть пустым");
    }
    if (book.get_author().empty() || is_blank(book.get_author())) {
        throw invalid_argument("Автор книги не может быть пустым");
    }
    if (book.get_year() < 0 || book.get_year() > 2026) {
        throw invalid_argument("Год издания должен быть от 0 до 2026");
    }
    string type = book.get_type();
    if (type != "учебник" && type != "методическое пособие" && type != "монография") {
        throw invalid_argument("Тип книги должен быть: учебник, методическое пособие или монография");
    }
    for (const auto& b : books) {
        if (b.get_title() == book.get_title() && b.get_author() == book.get_author()) {
            throw invalid_argument("Книга с таким названием и автором уже существует");
        }
    }
    books.push_back(book);
    cout << "[OK] Книга \"" << book.get_title() << "\" добавлена в библиотеку!" << endl;
}

void Library::add_reader(const Reader& reader) {
    for (const auto& r : readers) {
        if (r.get_name() == reader.get_name()) {
            throw invalid_argument("Читатель с таким именем уже зарегистрирован");
        }
    }
    readers.push_back(reader);
    cout << "[OK] Читатель \"" << reader.get_name() << "\" зарегистрирован (ID: " << reader.get_id() << ")" << endl;
}

void Library::change_reader_name(Reader* reader, string new_name) {
    for (const auto& r : readers) {
        if (r.get_id() != reader->get_id() && r.get_name() == new_name) {
            throw invalid_argument("Читатель с таким именем уже зарегистрирован");
        }
    }
    reader->set_name(new_name);
    cout << "[OK] ФИО читателя ID " << reader->get_id() << " изменено на: " << new_name << endl;
}


const vector<Book>& Library::get_books() const { return books; }
const vector<Reader>& Library::get_readers() const { return readers; }

Book* Library::find_book_by_title(const string& title) {
    for (auto& book : books) {
        if (book.get_title() == title) {
            return &book;
        }
    }
    return nullptr;
}

vector<Book*> Library::find_available_books() {
    vector<Book*> result;
    for (auto& book : books) {
        if (book.get_status() == AVAILABLE) {
            result.push_back(&book);
        }
    }
    return result;
}

vector<Book*> Library::find_borrowed_books() {
    vector<Book*> result;
    for (auto& book : books) {
        if (book.get_status() == BORROWED) {
            result.push_back(&book);
        }
    }
    return result;
}

Reader* Library::find_reader_by_id(int id) {
    for (auto& reader : readers) {
        if (reader.get_id() == id) {
            return &reader;
        }
    }
    return nullptr;
}

void Library::borrow_book(Book* book, Reader* reader) {
    try {
        book->borrow_book(reader->get_id());
        cout << "[OK] Книга \"" << book->get_title() << "\" выдана студенту "
            << reader->get_name() << " (ID: " << reader->get_id() << ")" << endl;
        cout << "     Срок возврата: через 14 дней" << endl;
    }
    catch (const exception& e) {
        throw runtime_error(string("Ошибка выдачи: ") + e.what());
    }
}

void Library::return_book(Book* book) {
    try {
        int reader_id = book->get_borrowed_by();
        book->return_book();
        cout << "[OK] Книга \"" << book->get_title() << "\" возвращена в библиотеку";
        if (reader_id != -1) {
            Reader* reader = find_reader_by_id(reader_id);
            if (reader) {
                cout << " (читатель " << reader->get_name() << ")";
            }
        }
        cout << endl;
    }
    catch (const exception& e) {
        throw runtime_error(string("Ошибка возврата: ") + e.what());
    }
}

void Library::pass_day() {
    day_counter++;
    cout << "\n[ДЕНЬ " << day_counter << "]" << endl;
    cout << "-------------------------------------------" << endl;

    bool has_changes = false;
    for (auto& book : books) {
        if (book.get_status() == BORROWED && book.get_days_left() > 0) {
            book.decrease_days();
            has_changes = true;
        }
    }
    if (has_changes) {
        cout << "Прошёл один день. Сроки возврата уменьшены." << endl;
    }
    else {
        cout << "Нет активных выдач." << endl;
    }
    cout << "-------------------------------------------" << endl;
}

void Library::display_all_books() const {
    cout << "\nБИБЛИОТЕЧНЫЙ КАТАЛОГ (" << books.size() << " книг)" << endl;
    cout << "-------------------------------------------" << endl;
    for (const auto& book : books) {
        cout << "* " << book.get_title() << " (" << book.get_author() << ", "
            << book.get_year() << " г.) [" << book.get_type() << "] - "
            << status_to_string(book.get_status(), book.get_days_left()) << endl;
    }
    cout << "-------------------------------------------" << endl;
}

void Library::display_all_readers() const {
    cout << "\nСПИСОК ЧИТАТЕЛЕЙ (" << readers.size() << " чел.)" << endl;
    cout << "-------------------------------------------" << endl;
    for (const auto& reader : readers) {
        cout << "ID " << reader.get_id() << ": " << reader.get_name()
            << " (тел.: " << reader.get_phone() << ")" << endl;
    }
    cout << "-------------------------------------------" << endl;
}

void Library::display_overdue_books() const {
    cout << "\nПРОСРОЧЕННЫЕ КНИГИ:" << endl;
    cout << "-------------------------------------------" << endl;
    bool has_overdue = false;
    for (const auto& book : books) {
        if (book.is_overdue()) {
            cout << "* " << book.get_title() << " (" << book.get_author() << ")" << endl;
            cout << "  Выдана читателю ID: " << book.get_borrowed_by() << endl;
            has_overdue = true;
        }
    }
    if (!has_overdue) {
        cout << "Просроченных книг нет" << endl;
    }
    cout << "-------------------------------------------" << endl;
}

void Library::display_book_info(Book* book) {
    book->display_info();
}

void Library::display_reader_info(Reader* reader) {
    reader->display_info();
}

void Library::change_reader_phone(Reader* reader, string new_phone) {
    reader->set_phone(new_phone);
    cout << "[OK] Телефон читателя ID " << reader->get_id() << " изменён на: " << new_phone << endl;
}

void Library::print_book_line(const Book& book, bool with_author) const {
    cout << "* " << book.get_title();
    if (with_author) {
        cout << " (" << book.get_author() << ", " << book.get_year() << " г.)";
    }
    else {
        cout << " (" << book.get_year() << " г.) [" << book.get_type() << "]";
    }
    cout << " - " << status_to_string(book.get_status(), book.get_days_left()) << endl;
}

int Library::get_book_count() const { return books.size(); }
int Library::get_reader_count() const { return readers.size(); }
int Library::get_day_counter() const { return day_counter; }